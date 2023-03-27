#include "00_Global.fx"
#include "00_Light.fx"

float2 PixelSize;

struct VertexOutput
{
    float4 Position : SV_Position;
    float2 Uv : Uv;
};

VertexOutput VS(float4 Position : Position)
{
    VertexOutput output;
    
    output.Position = Position;
    output.Uv.x = Position.x * 0.5f + 0.5f;
    output.Uv.y = -Position.y * 0.5f + 0.5f;
    
    return output;
}


struct PixelOutput
{
    float4 Color0 : SV_Target0;
    float4 Color1 : SV_Target1;
    float4 Color2 : SV_Target2;
};

PixelOutput PS_Mrt(VertexOutput input)
{
    PixelOutput output;
    
    output.Color0 = DiffuseMap.Sample(LinearSampler, input.Uv);
    output.Color1 = 1 - DiffuseMap.Sample(LinearSampler, input.Uv);
    
    float3 color = DiffuseMap.Sample(LinearSampler, input.Uv).rgb;
    float average = (color.r + color.g + color.b) / 3.0f;
    output.Color2 = float4(average, average, average, 1.0f);
    
    return output;
}

float4 PS(VertexOutput input) : SV_Target
{
    return DiffuseMap.Sample(LinearSampler, input.Uv);;
}

technique11 T0
{
    P_VP(P0, VS, PS_Mrt)
    P_VP(P1, VS, PS)
}