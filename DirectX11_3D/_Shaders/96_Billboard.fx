#include "00_Global.fx"
#include "00_Light.fx"
#include "00_Render.fx"

float4 PS(MeshOutput input) : SV_Target
{
    return PS_AllLight(input);
}

///////////////////////////////////////////////////////////////////////////////

struct VertexBillboard
{
    float4 Position : Position;
    float2 Scale : Scale;
    uint MapIndex : MapIndex;
    //uint VertexIndex : SV_VertexID;
};

struct VertexOutput
{
    float4 Position : Position;
    float2 Scale : Scale;
    uint MapIndex : MapIndex;
};

VertexOutput VS(VertexBillboard input)
{
    VertexOutput output;
    
    output.Position = WorldPosition(input.Position);
    output.Scale = input.Scale;
    output.MapIndex = input.MapIndex;
    
    return output;
}

struct GeometryOutput
{
    float4 Position : SV_Position;
    float2 Uv : Uv;
    uint MapIndex : MapIndex;
};

[maxvertexcount(4)]
void GS_Billboard(point VertexOutput input[1], inout TriangleStream<GeometryOutput> stream)
{
    float3 up = float3(0, 1, 0);
    //float3 forward = float3(0, 0, 1);
    float3 forward = input[0].Position.xyz - ViewPosition();
    float3 right = normalize(cross(up, forward));
    
    float2 size = input[0].Scale * 0.5f;
    
    
    float4 position[4];
    position[0] = float4(input[0].Position.xyz - size.x * right - size.y * up, 1);
    position[1] = float4(input[0].Position.xyz - size.x * right + size.y * up, 1);
    position[2] = float4(input[0].Position.xyz + size.x * right - size.y * up, 1);
    position[3] = float4(input[0].Position.xyz + size.x * right + size.y * up, 1);
    
    float2 uv[4] =
    {
        float2(0, 1), float2(0, 0), float2(1, 1), float2(1, 0)
    };
    
    
    GeometryOutput output;
    
    [unroll(4)]
    for (int i = 0; i < 4; i++)
    {
        output.Position = ViewProjection(position[i]);
        output.Uv = uv[i];
        output.MapIndex = input[0].MapIndex;
        
        stream.Append(output);
    }
}

[maxvertexcount(8)]
void GS_Cross(point VertexOutput input[1], inout TriangleStream<GeometryOutput> stream)
{
    float3 up = float3(0, 1, 0);
    float3 forward = float3(0, 0, 1);
    float3 right = normalize(cross(up, forward));
    
    float2 size = input[0].Scale * 0.5f;
    
    
    float4 position[8];
    position[0] = float4(input[0].Position.xyz - size.x * right - size.y * up, 1);
    position[1] = float4(input[0].Position.xyz - size.x * right + size.y * up, 1);
    position[2] = float4(input[0].Position.xyz + size.x * right - size.y * up, 1);
    position[3] = float4(input[0].Position.xyz + size.x * right + size.y * up, 1);
    
    position[4] = float4(input[0].Position.xyz - size.x * forward - size.y * up, 1);
    position[5] = float4(input[0].Position.xyz - size.x * forward + size.y * up, 1);
    position[6] = float4(input[0].Position.xyz + size.x * forward - size.y * up, 1);
    position[7] = float4(input[0].Position.xyz + size.x * forward + size.y * up, 1);
    
    float2 uv[4] =
    {
        float2(0, 1), float2(0, 0), float2(1, 1), float2(1, 0)
    };
    
    
    GeometryOutput output;
    
    [unroll(8)]
    for (int i = 0; i < 8; i++)
    {
        output.Position = ViewProjection(position[i]);
        output.Uv = uv[i % 4];
        output.MapIndex = input[0].MapIndex;
        
        stream.Append(output);
        
        [flatten]
        if(i == 3)
            stream.RestartStrip();
    }
}


Texture2DArray BillboardMap;
float4 PS_Billboard(GeometryOutput input) : SV_Target
{
    return BillboardMap.Sample(LinearSampler, float3(input.Uv, input.MapIndex)) * 1.75f;
}

technique11 T0
{
    P_VP(P0, VS_Mesh, PS)
    P_VP(P1, VS_Model, PS)
    P_VP(P2, VS_Animation, PS)

    P_BS_VGP(P3, AlphaBlend, VS, GS_Billboard, PS_Billboard)
    P_RS_BS_VGP(P4, CullMode_None, AlphaBlend_AlphaToCoverageEnable, VS, GS_Cross, PS_Billboard)
}