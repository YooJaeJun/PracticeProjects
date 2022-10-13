#pragma once
enum class AnimState
{
    stop, //����
    loop, //�ݺ����
    once, //�ѹ��� ���
    reverseLoop, //������ �ݺ����
    reverseOnce
};

class ObImage : public GameObject, public StaticVertexCount<ObImage>
{
    friend class ObTileMap;

private:
    static ID3D11Buffer*        vertexBuffer;
    static ID3D11Buffer*        uvBuffer;

public:
    static void CreateStaticMember();
    static void DeleteStaticMember();

private:
    ID3D11ShaderResourceView*   SRV;
    ID3D11SamplerState*         sampler;
    D3D11_SAMPLER_DESC	        samplerDesc;

    AnimState                   animState;
    float                       animTime; //�����ų �� �ʿ��� ����
    float                       animInterval; //�������
    bool                        animXAxis; //�������?

public:
    Vector4                     uv;
    Int2                        maxFrame;
    Int2                        frame;
    bool                        reverseLR;
    wstring                     file;

private:
    void PlayAnim();

public:
    ObImage(wstring file);
    ~ObImage();

    void Render()override;
    void ChangeAnim(AnimState anim, float interval, bool xAxis = true); //set�Լ� ���
    void ChangeSampler(D3D11_FILTER filter = D3D11_FILTER_MIN_MAG_MIP_POINT,
        D3D11_TEXTURE_ADDRESS_MODE addressU = D3D11_TEXTURE_ADDRESS_WRAP,
        D3D11_TEXTURE_ADDRESS_MODE addressV = D3D11_TEXTURE_ADDRESS_WRAP);
};

