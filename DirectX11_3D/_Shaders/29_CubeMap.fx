#include "00_Global.fx"

TextureCube CubeMap;

struct VertexOutput
{
    float4 Position : SV_Position;
    float3 oPosition : Position1;
    float3 Normal : Normal;
};

VertexOutput VS(VertexTextureNormal input)
{
    VertexOutput output;
    
    output.oPosition = input.Position.xyz;
    
    input.Position.x += cos(Time) * 3.0f;
    output.Position = WorldPosition(input.Position);
    output.Position = ViewProjection(output.Position);
    output.Normal = WorldNormal(input.Normal);
    
    return output;
}

float4 PS(VertexOutput input) : SV_Target
{
    float4 color = float4(sin(Time * 3), 1, 1, 1);
    
    return CubeMap.Sample(LinearSampler, input.oPosition) * color;
}

technique11 T0
{
    P_VP(P0, VS, PS)
    P_RS_VP(P1, FillMode_WireFrame, VS, PS)
}