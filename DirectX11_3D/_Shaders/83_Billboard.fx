#include "00_Global.fx"
#include "00_Light.fx"

struct VertexInput
{
    float4 Position : Position;
    float2 Uv : Uv;
    float2 Scale : Scale;
};

struct VertexOutput
{
    float4 Position : SV_Position;
    float2 Uv : Uv;
};

VertexOutput VS(VertexInput input)
{
    VertexOutput output;
    
    float4 position = WorldPosition(input.Position);
    
    float3 up = float3(0, 1, 0);
    //float3 forward = float3(0, 0, 1);
    float3 forward = position.xyz - ViewPosition();
    float3 right = normalize(cross(up, forward)); //(1, 0, 0)
    
    position.xyz += (input.Uv.x - 0.5f) * right * input.Scale.x;
    position.xyz += (1.0f - input.Uv.y - 0.5f) * up * input.Scale.y;
    position.w = 1.0f;
    
    output.Position = ViewProjection(position);
    output.Uv = input.Uv;

    return output;
}

float4 PS(VertexOutput input) : SV_Target
{
    float4 diffuse = DiffuseMap.Sample(LinearSampler, input.Uv);
    
    //clip(diffuse.a - 0.3f);
    if (diffuse.a < 0.3)
        discard;
    
    return diffuse;
}

technique11 T0
{
    P_VP(P0, VS, PS)
}