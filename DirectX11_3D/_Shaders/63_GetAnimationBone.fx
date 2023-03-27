#include "00_Global.fx"
#include "00_Render.fx"

struct InputDesc
{
    matrix Bone;
};
StructuredBuffer<InputDesc> Input;

struct OutputDesc
{
    matrix Result;
};
RWStructuredBuffer<OutputDesc> Output;


cbuffer CB_AttachBone
{
    uint AttachBoneIndex;
};

matrix TweenMode(uint index)
{
    uint boneIndex[2];
    matrix result = 0;
    
    boneIndex[0] = (TweenFrames[index].Curr.Clip * MAX_MODEL_KEYFRAMES * MAX_MODEL_TRANSFORMS);
    boneIndex[0] += (TweenFrames[index].Curr.CurrFrame * MAX_MODEL_TRANSFORMS);
    boneIndex[0] += AttachBoneIndex;
    
    boneIndex[1] = (TweenFrames[index].Curr.Clip * MAX_MODEL_KEYFRAMES * MAX_MODEL_TRANSFORMS);
    boneIndex[1] += (TweenFrames[index].Curr.NextFrame* MAX_MODEL_TRANSFORMS);
    boneIndex[1] += AttachBoneIndex;

    
    matrix currFrame = Input[boneIndex[0]].Bone;
    matrix nextFrame = Input[boneIndex[1]].Bone;
    
    result = lerp(currFrame, nextFrame, TweenFrames[index].Curr.Time);
    
    [flatten]
    if(TweenFrames[index].Next.Clip > -1)
    {
        boneIndex[0] = (TweenFrames[index].Next.Clip * MAX_MODEL_KEYFRAMES * MAX_MODEL_TRANSFORMS);
        boneIndex[0] += (TweenFrames[index].Next.CurrFrame * MAX_MODEL_TRANSFORMS);
        boneIndex[0] += AttachBoneIndex;
    
        boneIndex[1] = (TweenFrames[index].Next.Clip * MAX_MODEL_KEYFRAMES * MAX_MODEL_TRANSFORMS);
        boneIndex[1] += (TweenFrames[index].Next.NextFrame * MAX_MODEL_TRANSFORMS);
        boneIndex[1] += AttachBoneIndex;
        
        matrix currFrame = Input[boneIndex[0]].Bone;
        matrix nextFrame = Input[boneIndex[1]].Bone;
    
        matrix nextAnim = lerp(currFrame, nextFrame, TweenFrames[index].Next.Time);
        
        result = lerp(result, nextAnim, TweenFrames[index].TweenTime);
    }
    
    return result;
}

matrix BlendMode(uint index)
{
    uint boneIndex[2];
    matrix animation[3];
    
    
    BlendFrame frame = BlendFrames[index];
    
    [unroll(3)]
    for (int i = 0; i < 3; i++)
    {
        boneIndex[0] = (frame.Clip[i].Clip * MAX_MODEL_KEYFRAMES * MAX_MODEL_TRANSFORMS);
        boneIndex[0] += (frame.Clip[i].CurrFrame * MAX_MODEL_TRANSFORMS);
        boneIndex[0] += AttachBoneIndex;
    
        boneIndex[1] = (frame.Clip[i].Clip * MAX_MODEL_KEYFRAMES * MAX_MODEL_TRANSFORMS);
        boneIndex[1] += (frame.Clip[i].NextFrame * MAX_MODEL_TRANSFORMS);
        boneIndex[1] += AttachBoneIndex;
    
        matrix currFrame = Input[boneIndex[0]].Bone;
        matrix nextFrame = Input[boneIndex[1]].Bone;
    
        animation[i] = lerp(currFrame, nextFrame, TweenFrames[index].Curr.Time);
    }
    
    int clipA = (int) frame.Alpha;
    int clipB = clipA + 1;
        
    float alpha = frame.Alpha;
    if (alpha >= 1.0f)
    {
        alpha = frame.Alpha - 1.0f;
            
        if (frame.Alpha >= 2.0f)
        {
            clipA = 1;
            clipB = 2;
        }
    }
        
    return lerp(animation[clipA], animation[clipB], alpha);
}

[numthreads(MAX_MODEL_INSTANCE, 1, 1)]
void CS(uint GroupIndex : SV_GroupIndex)
{
    matrix result = 0;
    if(BlendFrames[GroupIndex].Mode == 0)
        result = TweenMode(GroupIndex);
    else
        result = BlendMode(GroupIndex);
    
    Output[GroupIndex].Result = result;
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