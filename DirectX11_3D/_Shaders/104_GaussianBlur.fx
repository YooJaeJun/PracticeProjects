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

float4 PS_Diffuse(VertexOutput input) : SV_Target
{
    return DiffuseMap.Sample(LinearSampler, input.Uv);
}

const int GaussBlurCount = 6;
static const float Weights[13] =
{
    0.0561f, 0.1353f, 0.2780f, 0.4868f, 0.7261f, 0.9231f,
    1.0f,
    0.9231f, 0.7261f, 0.4868f, 0.2780f, 0.1353f, 0.0561f
};

float4 PS_GaussianBlurX(VertexOutput input) : SV_Target
{
    float2 uv = input.Uv;
    float u = PixelSize.x;
    
    float sum = 0;
    float4 color = 0;
    for (int i = -GaussBlurCount; i <= GaussBlurCount; i++)
    {
        float2 temp = uv + float2(u * (float) i, 0.0f);
        color += Weights[6 + i] * DiffuseMap.Sample(LinearSampler, temp);
        
        sum += Weights[6 + i];
    }
    color /= sum;
    
    return float4(color.rgb, 1.0f);
}

float4 PS_GaussianBlurY(VertexOutput input) : SV_Target
{
    float2 uv = input.Uv;
    float v = PixelSize.y;
    
    float sum = 0;
    float4 color = 0;
    for (int i = -GaussBlurCount; i <= +GaussBlurCount; i++)
    {
        float2 temp = uv + float2(0.0f, v * (float) i);
        color += Weights[6 + i] * DiffuseMap.Sample(LinearSampler, temp);
        
        sum += Weights[6 + i];
    }
    color /= sum;
    
    return float4(color.rgb, 1);
}


struct PixelOutput_GaussianBlur2
{
    float4 Color0 : SV_Target0;
    float4 Color1 : SV_Target1;
};

PixelOutput_GaussianBlur2 PS_GaussianBlurMrt(VertexOutput input)
{
    PixelOutput_GaussianBlur2 output;
    
    
    float2 uv = input.Uv;
    float u = PixelSize.x;
    
    float sum = 0;
    float4 color = 0;
    for (int i = -GaussBlurCount; i <= GaussBlurCount; i++)
    {
        float2 temp = uv + float2(u * (float) i, 0.0f);
        color += Weights[6 + i] * DiffuseMap.Sample(LinearSampler, temp);
        
        sum += Weights[6 + i];
    }
    color /= sum;
    
    output.Color0 = float4(color.rgb, 1.0f);
    
    
    float v = PixelSize.y;
    
    sum = 0;
    color = 0;
    for (i = -GaussBlurCount; i <= +GaussBlurCount; i++)
    {
        float2 temp = uv + float2(0.0f, v * (float) i);
        color += Weights[6 + i] * DiffuseMap.Sample(LinearSampler, temp);
        
        sum += Weights[6 + i];
    }
    color /= sum;
    
    output.Color1 = float4(color.rgb, 1);
    
    
    return output;
}


Texture2D GaussianMrt[2];
float4 PS_PS_GaussianCombined(VertexOutput input) : SV_Target
{
    float4 color = GaussianMrt[0].Sample(LinearSampler, input.Uv);
    float4 color2 = GaussianMrt[1].Sample(LinearSampler, input.Uv);
    
    return float4((color.rgb + color2.rgb) * 0.5f, 1.0f);

}

technique11 T0
{
    P_VP(P0, VS, PS_Diffuse)
    P_VP(P1, VS, PS_GaussianBlurX)
    P_VP(P2, VS, PS_GaussianBlurY)
    P_VP(P3, VS, PS_GaussianBlurMrt)
    P_VP(P4, VS, PS_PS_GaussianCombined)
}