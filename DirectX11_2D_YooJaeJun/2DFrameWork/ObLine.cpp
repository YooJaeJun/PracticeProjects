#include "framework.h"

ID3D11Buffer* ObLine::vertexBuffer = nullptr;

void ObLine::CreateStaticMember()
{
    VertexPC* Vertex = new VertexPC[2];

    Vertex[0].position.x = -0.5f;
    Vertex[0].position.y = 0.0f;
    Vertex[0].color = Color(0.0f, 0.0f, 0.0f, 1.0f);

    Vertex[1].position.x = 0.5f;
    Vertex[1].position.y = 0.0f;
    Vertex[1].color = Color(1.0f, 1.0f, 1.0f, 1.0f);

    //CreateVertexBuffer
    {
        D3D11_BUFFER_DESC desc;
        desc = { 0 };
        desc.Usage = D3D11_USAGE_DEFAULT;//���۸� �а� ���� ���
        desc.ByteWidth = sizeof(VertexPC) * 2; //���� ũ�� (����Ʈ)�Դϴ�.
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

void ObLine::DeleteStaticMember()
{
    vertexBuffer->Release();
}


void ObLine::Render()
{
    if (!isVisible)return;
    GameObject::Render();

    basicShader->Set();

    UINT stride = sizeof(VertexPC);
    UINT offset = 0;
    //������ ��������
    D3D->GetDC()->IASetPrimitiveTopology
        //(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        (D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

    D3D->GetDC()->IASetVertexBuffers(0,//�Է½���(16~32������ ��������)
        1,//�Է½��Կ� ���̰��� �ϴ� ������ ����
        &vertexBuffer,
        &stride,//���������� �� ������ ����Ʈ���� ũ��
        &offset);

    D3D->GetDC()->Draw(2, 0);
}


ObLine::ObLine()
    : v(Vector2(0.0f, 0.0f)), w(Vector2(0.0f, 0.0f))
{
    pivot = OFFSET_L;
}

ObLine::ObLine(const Vector2& v1, const Vector2& v2)
    : v(v1), w(v2)
{
    pivot = OFFSET_L;
}

ObLine& ObLine::operator=(const ObLine& e)
{
    v.x = e.v.x;
    v.y = e.v.y;
    w.x = e.w.x;
    w.y = e.w.y;
    return *this;
}

bool ObLine::operator==(const ObLine& e) const
{
    return ((this->v) == e.v && (this->w) == e.w) ||
        ((this->v) == e.w && (this->w) == e.v);
}

bool ObLine::almost_equal_line(const ObLine& e1, const ObLine& e2)
{
    return	(almost_equal_vector(e1.v, e2.v) && almost_equal_vector(e1.w, e2.w)) ||
        (almost_equal_vector(e1.v, e2.w) && almost_equal_vector(e1.w, e2.v));
}