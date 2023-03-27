ByteAddressBuffer Input; //SRV
RWByteAddressBuffer Output; //UAV

struct Group
{
    uint3 GroupID;
    uint3 GroupThreadID;
    uint3 DispatchThreadID;
    uint GroupIndex;
    float RetValue;
};

struct ComputeInput
{
    uint3 GroupID : SV_GroupID;
    uint3 GroupThreadID : SV_GroupThreadID;
    uint3 DispatchThreadID : SV_DispatchThreadID;
    uint GroupIndex : SV_GroupIndex;
};

[numthreads(10, 8, 3)]
void CS(ComputeInput input)
{
    Group group;
    group.GroupID = asuint(input.GroupID);
    group.GroupThreadID = asuint(input.GroupThreadID);
    group.DispatchThreadID = asuint(input.DispatchThreadID);
    group.GroupIndex = asuint(input.GroupIndex);
    
    uint index = input.GroupID.x * 10 * 8 * 3 + input.GroupIndex;
    uint outAddress = index * 11 * 4;
    
    uint inAddress = index * 4;
    group.RetValue = asfloat(Input.Load(inAddress));
    
    Output.Store3(outAddress + 0, asuint(group.GroupID)); //12
    Output.Store3(outAddress + 12, asuint(group.GroupThreadID)); //24
    Output.Store3(outAddress + 24, asuint(group.DispatchThreadID)); //36
    Output.Store(outAddress + 36, asuint(group.GroupIndex)); //40
    Output.Store(outAddress + 40, asuint(group.RetValue));

}

technique11 T0
{
    pass P0
    {
        SetVertexShader(NULL);
        SetPixelShader(NULL);

        SetComputeShader(CompileShader(cs_5_0, CS()));
    }
}