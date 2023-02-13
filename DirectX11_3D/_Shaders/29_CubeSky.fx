#include "00_Global.fx"

struct VertexOutput
{
    float4 Position : SV_Position;
    float3 oPosition : Position1;
};

VertexOutput VS(Vertex input)
{
    VertexOutput output;
    
    output.oPosition = input.Position.xyz;
    
    output.Position = WorldPosition(input.Position);
    output.Position = ViewProjection(output.Position);
    
    return output;
}


float4 PS(VertexOutput input) : SV_Target
{
    return SkyCubeMap.Sample(LinearSampler, input.oPosition);
}

technique11 T0
{
    P_RS_DSS_VP(P0, FrontCounterClockwise_True, DepthEnable_False, VS, PS)

    //pass P0
    //{
    //    SetRasterizerState(FrontCounterClockWise_True);
    //    SetDepthStencilState(DepthEnable_False, 0);

    //    SetVertexShader(CompileShader(vs_5_0, VS()));
    //    SetPixelShader(CompileShader(ps_5_0, PS()));
    //}
}