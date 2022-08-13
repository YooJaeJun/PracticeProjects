#include "framework.h"

Shader::Shader(wstring file)
{
    ID3D10Blob*					VsBlob;
    ID3D10Blob*					PsBlob;

    wstring path = L"../Shaders/" + file + L".hlsl";

    DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

    D3DCompileFromFile(path.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
        "VS", "vs_5_0", flags, 0, &VsBlob, nullptr);

    D3D->GetDevice()->CreateVertexShader(VsBlob->GetBufferPointer(), VsBlob->GetBufferSize(),
        nullptr, &vertexShader);

    D3D11_INPUT_ELEMENT_DESC LayoutDesc[2];

    LayoutDesc[0] = { "POSITION",//�ø�ƽ���� ������ �ڷ���
    0,//�ø�ƽ���� ������ �ε��� 0���� �����߱⿡ 0 ���
    DXGI_FORMAT_R32G32B32_FLOAT,//3���� 32��Ʈ float����
    0,//0~15������ �ε��� ����, ���ÿ� 15������ ���۰� �Է½����� �������ִ�.
    0,//�� ��Ұ� �޸𸮵�� ������������ �󸶳� ������ ��ġ�� �ִ°��� �˷��ش�.ó������0
    D3D11_INPUT_PER_VERTEX_DATA,//�Ѿ��
    0 };

    if (file == L"1.Basic")
    {
        LayoutDesc[1] = 
        { "COLOR",//�ø�ƽ���� ������ �ڷ���
        0,//�ø�ƽ���� ������ �ε��� 0���� �����߱⿡ 0 ���
        DXGI_FORMAT_R32G32B32_FLOAT,//3���� 32��Ʈ float����
        0,//0~15������ �ε��� ����, ���ÿ� 15������ ���۰� �Է½����� �������ִ�.
        12,//������ R32G32B32 4 ,4,4 ->12 ���� 
        D3D11_INPUT_PER_VERTEX_DATA,//�Ѿ��
        0 };
    }

    else if (file == L"2.Image")
    {
        LayoutDesc[1] = 
        { "UV",//�ø�ƽ���� ������ �ڷ���
        0,//�ø�ƽ���� ������ �ε��� 0���� �����߱⿡ 0 ���
        DXGI_FORMAT_R32G32_FLOAT,//2���� 32��Ʈ float����
        0,//0~15������ �ε��� ����, ���ÿ� 15������ ���۰� �Է½����� �������ִ�.
        12,//������ R32G32B32 4 ,4,4 ->12 ���� 
        D3D11_INPUT_PER_VERTEX_DATA,//�Ѿ��
        0 };
    }

    D3D->GetDevice()->CreateInputLayout
    (
        LayoutDesc,//��������ü�迭
        2,//�迭���Ұ���
        VsBlob->GetBufferPointer(),//�������̴� ������
        VsBlob->GetBufferSize(),//���̴�ũ��
        &vertexLayout//�Է¹�ġ�� �����͸� ���� ������
    );

    VsBlob->Release();

    D3DCompileFromFile(path.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
        "PS", "ps_5_0", flags, 0, &PsBlob, nullptr);

    D3D->GetDevice()->CreatePixelShader(PsBlob->GetBufferPointer(), PsBlob->GetBufferSize(),
        nullptr, &pixelShader);

    PsBlob->Release();
}

Shader::~Shader()
{
    vertexShader->Release();
    pixelShader->Release();
    vertexLayout->Release();
}

void Shader::Set()
{
    //���������ο� ���ε�
    D3D->GetDC()->VSSetShader(vertexShader, 0,  0);
    D3D->GetDC()->PSSetShader(pixelShader, 0, 0);
    D3D->GetDC()->IASetInputLayout(vertexLayout);
}
