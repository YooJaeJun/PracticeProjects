#include "framework.h"

ID3D11Buffer* ObStar::fillVertexBuffer = nullptr;
ID3D11Buffer* ObStar::vertexBuffer = nullptr;

void ObStar::CreateStaticMember()
{
    StaticVertexCount::Trianglestrip() = 15;
    StaticVertexCount::Linestrip() = 6;

    VertexPC* Vertex;

    /*vertex[0] = Vector2(0.5f * cosf(0), 0.5f * sinf(0));
    vertex[1] = Vector2(0.5f * cosf(72 * ToRadian), 0.5f * sinf(72 * ToRadian));
    vertex[2] = Vector2(0.5f * cosf(144 * ToRadian), 0.5f * sinf(144 * ToRadian));
    vertex[3] = Vector2(0.5f * cosf(216 * ToRadian), 0.5f * sinf(216 * ToRadian));
    vertex[4] = Vector2(0.5f * cosf(288 * ToRadian), 0.5f * sinf(288 * ToRadian));*/

    Vertex = new VertexPC[StaticVertexCount::Trianglestrip()];

    for (UINT i = 0; i < 5; i++)
    {
        Vertex[i * 3].position.x = 0.0f;
        Vertex[i * 3].position.y = 0.0f;
        Vertex[i * 3].color = Color(1.0f, 1.0f, 1.0f, 1.0f);

        Vertex[i * 3 + 1].position.x = cosf(i * 144 * ToRadian) * 0.5f;
        Vertex[i * 3 + 1].position.y = sinf(i * 144 * ToRadian) * 0.5f;
        Vertex[i * 3 + 1].color = Color(0.0f, 0.0f, 0.0f, 1.0f);

        Vertex[i * 3 + 2].position.x = cosf((i + 1) * 144 * ToRadian) * 0.5f;
        Vertex[i * 3 + 2].position.y = sinf((i + 1) * 144 * ToRadian) * 0.5f;
        Vertex[i * 3 + 2].color = Color(1.0f, 1.0f, 1.0f, 1.0f);
    }

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

    Vertex[0].position.x = -0.5f;
    Vertex[0].position.y = 0.2f;
    Vertex[0].color = Color(0.0f, 0.0f, 0.0f, 1.0f);

    Vertex[1].position.x = 0.5f;
    Vertex[1].position.y = 0.2f;
    Vertex[1].color = Color(0.0f, 0.0f, 0.0f, 1.0f);

    Vertex[2].position.x = -0.3f;
    Vertex[2].position.y = -0.4f;
    Vertex[2].color = Color(0.0f, 0.0f, 0.0f, 1.0f);

    Vertex[3].position.x = 0.0f;
    Vertex[3].position.y = 0.6f;
    Vertex[3].color = Color(0.0f, 0.0f, 0.0f, 1.0f);

    Vertex[4].position.x = 0.3f;
    Vertex[4].position.y = -0.4f;
    Vertex[4].color = Color(0.0f, 0.0f, 0.0f, 1.0f);

    Vertex[5].position.x = -0.5f;
    Vertex[5].position.y = 0.2f;
    Vertex[5].color = Color(0.0f, 0.0f, 0.0f, 1.0f);

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

void ObStar::DeleteStaticMember()
{
    vertexBuffer->Release();
    fillVertexBuffer->Release();
}

ObStar::ObStar()
{
    collider = Collider::star;
}

void ObStar::Render()
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

