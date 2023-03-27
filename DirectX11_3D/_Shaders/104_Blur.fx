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

uint BlurCount = 8;
float4 PS_Blur(VertexOutput input) : SV_Target
{
    float2 arr[9] =
    {
        float2(-1, -1), float2(+0, -1), float2(+1, -1),
        float2(-1, +0), float2(+0, +0), float2(+1, +0),
        float2(-1, +1), float2(+0, +1), float2(+1, +1),
    };
    
    
    float3 color = 0;
    for (uint blur = 1; blur < BlurCount; blur++)
    {
        for (int i = 0; i < 9; i++)
        {
            float x = arr[i].x * (float) blur * PixelSize.x;
            float y = arr[i].y * (float) blur * PixelSize.y;
            
            float2 uv = input.Uv + float2(x, y);
            color += DiffuseMap.Sample(LinearSampler, uv).rgb;
        }

    }
    
    color /= BlurCount * 9;
    
    return float4(color.rgb, 1);
}


uint RadialBlurCount = 8;
float RadialBlurRadius = 0.0f;
float RadialBlurAmount = 0.04f; //4%
float2 RadialCenter = float2(0.5f, 0.5f);

float4 PS_RadialBlur(VertexOutput input) : SV_Target
{
    float2 radius = input.Uv - RadialCenter;
    float r = length(radius) + 1e-6f;
    radius /= r;
    
    r = 2 * r / RadialBlurRadius;
    r = saturate(r);
    
    float2 delta = radius * r * r * RadialBlurAmount / RadialBlurCount;
    delta = -delta;
    
    float4 color = 0;
    for (uint i = 0; i < RadialBlurCount; i++)
    {
        color += DiffuseMap.Sample(LinearSampler, input.Uv);
        input.Uv += delta;
    }
    color /= RadialBlurCount;
    
    return float4(color.rgb, 1);
}

technique11 T0
{
    P_VP(P0, VS, PS_Diffuse)
    P_VP(P1, VS, PS_Blur)
    P_VP(P2, VS, PS_RadialBlur)
}