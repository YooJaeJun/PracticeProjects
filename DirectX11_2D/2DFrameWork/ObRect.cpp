#include "framework.h"

ID3D11Buffer* ObRect::fillVertexBuffer = nullptr;
ID3D11Buffer* ObRect::vertexBuffer = nullptr;

void ObRect::CreateStaticMember()
{
    StaticVertexCount::Trianglestrip() = 4;
    StaticVertexCount::Linestrip() = 5;

    VertexPC* Vertex;

    Vertex = new VertexPC[StaticVertexCount::Trianglestrip()];
    //VertexCount = 4;
    //�ð�������� �������
    Vertex[0].position.x = -0.5f;
    Vertex[0].position.y = -0.5f;
    // ������ ä��, ��Į�� ��(�󸶳� ������)
    Vertex[0].color = Color(0.0f, 0.0f, 0.0f, 1.0f);

    Vertex[1].position.x = -0.5f;
    Vertex[1].position.y = 0.5f;
    Vertex[1].color = Color(0.0f, 0.0f, 0.0f, 1.0f);

    Vertex[2].position.x = 0.5f;
    Vertex[2].position.y = -0.5f;
    Vertex[2].color = Color(0.0f, 0.0f, 0.0f, 1.0f);

    Vertex[3].position.x = 0.5f;
    Vertex[3].position.y = 0.5f;
    Vertex[3].color = Color(0.0f, 0.0f, 0.0f, 1.0f);


    //CreateVertexBuffer
    {
        D3D11_BUFFER_DESC desc;
        desc = { 0 };
        desc.Usage = D3D11_USAGE_DEFAULT;//���۸� �а� ���� ���
        desc.ByteWidth = sizeof(VertexPC) * StaticVertexCount::Trianglestrip(); //���� ũ�� (����Ʈ)�Դϴ�.
        desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;//���۰� ������ ���ο� ���ε��Ǵ� ����� �ĺ��Ͻʽÿ�

        D3D11_SUBRESOURCE_DATA data = { 0 };
        //���� ���ҽ��� �ʱ�ȭ�ϱ����� �����͸� �����մϴ�.
        data.pSysMem = Vertex;
        //�ʱ�ȭ �������� ������.

        //���� �����
        HRESULT hr = D3D->GetDevice()->CreateBuffer(&desc, &data, &fillVertexBuffer);
        assert(SUCCEEDED(hr));
    }

    delete[] Vertex;

    Vertex = new VertexPC[StaticVertexCount::Linestrip()];
    //VertexCount = 5;
    Vertex[0].position.x = -0.5f;
    Vertex[0].position.y = -0.5f;
    Vertex[0].color = Color(0.0f, 0.0f, 0.0f, 1.0f);

    Vertex[1].position.x = -0.5f;
    Vertex[1].position.y = 0.5f;
    Vertex[1].color = Color(0.0f, 0.0f, 0.0f, 1.0f);

    Vertex[2].position.x = 0.5f;
    Vertex[2].position.y = 0.5f;
    Vertex[2].color = Color(0.0f, 0.0f, 0.0f, 1.0f);

    Vertex[3].position.x = 0.5f;
    Vertex[3].position.y = -0.5f;
    Vertex[3].color = Color(0.0f, 0.0f, 0.0f, 1.0f);

    Vertex[4].position.x = -0.5f;
    Vertex[4].position.y = -0.5f;
    Vertex[4].color = Color(0.0f, 0.0f, 0.0f, 1.0f);

    //CreateVertexBuffer
    {
        D3D11_BUFFER_DESC desc;
        desc = { 0 };
        desc.Usage = D3D11_USAGE_DEFAULT;//���۸� �а� ���� ���
        desc.ByteWidth = sizeof(VertexPC) * StaticVertexCount::Linestrip(); //���� ũ�� (����Ʈ)�Դϴ�.
        desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;//���۰� ������ ���ο� ���ε��Ǵ� ����� �ĺ��Ͻʽÿ�

        D3D11_SUBRESOURCE_DATA data = { 0 };
        //���� ���ҽ��� �ʱ�ȭ�ϱ����� �����͸� �����մϴ�.
        data.pSysMem = Vertex;
        //�ʱ�ȭ �������� ������.

        //���� �����
        HRESULT hr = D3D->GetDevice()->CreateBuffer(&desc, &data, &vertexBuffer);
        assert(SUCCEEDED(hr));
    }
    delete[] Vertex;
}

void ObRect::DeleteStaticMember()
{
    vertexBuffer->Release();
    fillVertexBuffer->Release();
}

ObRect::ObRect()
{
    collider = Collider::rect;
}

void ObRect::Render()
{
    if (!isVisible)return;
    GameObject::Render();

    basicShader->Set();

    UINT stride = sizeof(VertexPC);
    UINT offset = 0;

    if (isFilled)
    {
        D3D->GetDC()->IASetVertexBuffers(0,
            1,
            &fillVertexBuffer,
            &stride,
            &offset);
        D3D->GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);   // �׸� ���
        D3D->GetDC()->Draw(StaticVertexCount::Trianglestrip(), 0);
    }
    else
    {
        D3D->GetDC()->IASetVertexBuffers(0,//�Է½���(16~32������ ��������)
            1,//�Է½��Կ� ���̰��� �ϴ� ������ ����
            &vertexBuffer,
            &stride,//���������� �� ������ ����Ʈ���� ũ��
            &offset);
        D3D->GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
        D3D->GetDC()->Draw(StaticVertexCount::Linestrip(), 0);
    }
}

const Vector2 ObRect::lb() const
{
    return Vector2(GetWorldPos().x - scale.x / 2.0f, GetWorldPos().y - scale.y / 2.0f);
}

const Vector2 ObRect::rb() const
{
    return Vector2(GetWorldPos().x + scale.x / 2.0f, GetWorldPos().y - scale.y / 2.0f);
}

const Vector2 ObRect::lt() const
{
    return Vector2(GetWorldPos().x - scale.x / 2.0f, GetWorldPos().y + scale.y / 2.0f);
}

const Vector2 ObRect::rt() const
{
    return Vector2(GetWorldPos().x + scale.x / 2.0f, GetWorldPos().y + scale.y / 2.0f);
}



