matrix World;
matrix View;
matrix Projection;
Texture2D Map;

struct VertexInput
{
    float4 Position : Position;
    float2 Uv : Uv;
};

struct VertexOutput
{
    float4 Position : SV_Position;
    float2 Uv : Uv;
};

VertexOutput VS(VertexInput input)
{
    VertexOutput output;
    output.Position = mul(input.Position, World);
    output.Position = mul(output.Position, View);
    output.Position = mul(output.Position, Projection);
    
    output.Uv = input.Uv;
    
    return output;
}

SamplerState Samp;
float4 PS(VertexOutput input) : SV_Target
{
    if(input.Uv.x < 0.5f)
        return float4(1, 0, 0, 1);
    
    return Map.Sample(Samp, input.Uv);
}


uint Filter;

SamplerState Sampler_Filter_Point
{
    Filter = MIN_MAG_MIP_POINT;
};

SamplerState Sampler_Filter_Linear
{
    Filter = MIN_MAG_MIP_LINEAR;
};

float4 PS_Filter(VertexOutput input) : SV_Target
{
    if (Filter == 0)
        return Map.Sample(Sampler_Filter_Point, input.Uv);
    
    if (Filter == 1)
        return Map.Sample(Sampler_Filter_Linear, input.Uv);
    
    return Map.Sample(Samp, input.Uv);
}


uint Address;

SamplerState Sampler_Address_Wrap
{
    AddressU = Wrap;
    AddressV = Wrap;
};

SamplerState Sampler_Address_Mirror
{
    AddressU = Mirror;
    AddressV = Mirror;
};

SamplerState Sampler_Address_Clamp
{
    AddressU = Clamp;
    AddressV = Clamp;
};

SamplerState Sampler_Address_Border
{
    AddressU = Border;
    AddressV = Border;

    BorderColor = float4(0, 0, 1, 1);
};

float4 PS_Address(VertexOutput input) : SV_Target
{
    if (Address == 0)
        return Map.Sample(Sampler_Address_Wrap, input.Uv);
    
    if (Address == 1)
        return Map.Sample(Sampler_Address_Mirror, input.Uv);
    
    if (Address == 2)
        return Map.Sample(Sampler_Address_Clamp, input.Uv);
    
    if (Address == 3)
        return Map.Sample(Sampler_Address_Border, input.Uv);
    
    return Map.Sample(Samp, input.Uv);
}

technique11 T0
{
    pass P0
    {
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS()));
    }

    pass P1
    {
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS_Filter()));
    }

    pass P2
    {
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS_Address()));
    }
}