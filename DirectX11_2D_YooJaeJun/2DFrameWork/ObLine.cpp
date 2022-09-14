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
        desc.Usage = D3D11_USAGE_DEFAULT;//버퍼를 읽고 쓰는 방법
        desc.ByteWidth = sizeof(VertexPC) * 2; //버퍼 크기 (바이트)입니다.
        desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;//버퍼가 파이프 라인에 바인딩되는 방법을 식별하십시오

        D3D11_SUBRESOURCE_DATA data = { 0 };
        //하위 리소스를 초기화하기위한 데이터를 지정합니다.
        data.pSysMem = Vertex;
        //초기화 데이터의 포인터.

        //버퍼 만들기
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
    //정점의 도형서술
    D3D->GetDC()->IASetPrimitiveTopology
        //(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        (D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

    D3D->GetDC()->IASetVertexBuffers(0,//입력슬롯(16~32개까지 설정가능)
        1,//입력슬롯에 붙이고자 하는 버퍼의 갯수
        &vertexBuffer,
        &stride,//정점버퍼의 한 원소의 바이트단위 크기
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