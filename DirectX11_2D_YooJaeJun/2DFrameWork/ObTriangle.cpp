#include "framework.h"

ID3D11Buffer* ObTriangle::fillVertexBuffer = nullptr;
ID3D11Buffer* ObTriangle::vertexBuffer = nullptr;

void ObTriangle::CreateStaticMember()
{
    VertexPC* Vertex;

    Vertex = new VertexPC[vertexCount];
    Vertex[0].position.x = 0.0f;
    Vertex[0].position.y = 0.5f;
    Vertex[0].color = Color(1.0f, 1.0f, 1.0f, 1.0f);

    Vertex[1].position.x = -0.5f;
    Vertex[1].position.y = -0.4f;
    Vertex[1].color = Color(0.3f, 0.3f, 0.3f, 1.0f);

    Vertex[2].position.x = 0.5f;
    Vertex[2].position.y = -0.4f;
    Vertex[2].color = Color(0.6f, 0.6f, 0.6f, 1.0f);


    //CreateVertexBuffer
    {
        D3D11_BUFFER_DESC desc;
        desc = { 0 };
        desc.Usage = D3D11_USAGE_DEFAULT;//버퍼를 읽고 쓰는 방법
        desc.ByteWidth = sizeof(VertexPC) * vertexCount; //버퍼 크기 (바이트)입니다.
        desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;//버퍼가 파이프 라인에 바인딩되는 방법을 식별하십시오

        D3D11_SUBRESOURCE_DATA data = { 0 };
        //하위 리소스를 초기화하기위한 데이터를 지정합니다.
        data.pSysMem = Vertex;
        //초기화 데이터의 포인터.

        //버퍼 만들기
        HRESULT hr = D3D->GetDevice()->CreateBuffer(&desc, &data, &fillVertexBuffer);
        assert(SUCCEEDED(hr));
    }

    delete[] Vertex;

    Vertex = new VertexPC[vertexCount];
    Vertex[0].position.x = 0.0f;
    Vertex[0].position.y = 0.5f;
    Vertex[0].color = Color(1.0f, 1.0f, 1.0f, 1.0f);

    Vertex[1].position.x = -0.5f;
    Vertex[1].position.y = -0.4f;
    Vertex[1].color = Color(0.3f, 0.3f, 0.3f, 1.0f);

    Vertex[2].position.x = 0.5f;
    Vertex[2].position.y = -0.4f;
    Vertex[2].color = Color(0.6f, 0.6f, 0.6f, 1.0f);

    //CreateVertexBuffer
    {
        D3D11_BUFFER_DESC desc;
        desc = { 0 };
        desc.Usage = D3D11_USAGE_DEFAULT;//버퍼를 읽고 쓰는 방법
        desc.ByteWidth = sizeof(VertexPC) * vertexCount; //버퍼 크기 (바이트)입니다.
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

void ObTriangle::DeleteStaticMember()
{
    vertexBuffer->Release();
    fillVertexBuffer->Release();
}

ObTriangle::ObTriangle()
{
    collider = COLLIDER::TRIANGLE;
}

void ObTriangle::Render()
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
        D3D->GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);   // 그릴 모양
        D3D->GetDC()->Draw(vertexCount, 0);
    }
    else
    {
        D3D->GetDC()->IASetVertexBuffers(0,//입력슬롯(16~32개까지 설정가능)
            1,//입력슬롯에 붙이고자 하는 버퍼의 갯수
            &vertexBuffer,
            &stride,//정점버퍼의 한 원소의 바이트단위 크기
            &offset);
        D3D->GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
        D3D->GetDC()->Draw(vertexCount, 0);
    }
}


ObTriangle::ObTriangle(const Vector2& v1, const Vector2& v2, const Vector2& v3)
    : a(v1), b(v2), c(v3), isBad(false)
{}

bool ObTriangle::operator==(const ObTriangle& t) const
{
    return	(this->a == t.a || this->a == t.b || this->a == t.c) &&
        (this->b == t.a || this->b == t.b || this->b == t.c) &&
        (this->c == t.a || this->c == t.b || this->c == t.c);
}

bool ObTriangle::ContainsVertex(const Vector2& v) const
{
    return almost_equal_vector(a, v) || almost_equal_vector(b, v) || almost_equal_vector(c, v);
}

bool ObTriangle::CircumCircleContains(const Vector2& v) const
{
    long double dA = a.LengthSquared();
    long double dB = b.LengthSquared();
    long double dC = c.LengthSquared();

    long double ax = a.x;
    long double ay = a.y;
    long double bx = b.x;
    long double by = b.y;
    long double cx = c.x;
    long double cy = c.y;

    long double circum_x = (dA * (cy - by) + dB * (ay - cy) + dC * (by - ay)) / (ax * (cy - by) + bx * (ay - cy) + cx * (by - ay));
    long double circum_y = (dA * (cx - bx) + dB * (ax - cx) + dC * (bx - ax)) / (ay * (cx - bx) + by * (ax - cx) + cy * (bx - ax));

    Vector2 circum(circum_x / 2, circum_y / 2);
    float circum_radius = Vector2::Distance(a, circum);
    float dist = Vector2::Distance(v, circum);
    return dist <= circum_radius;
}

bool ObTriangle::almost_equal_triangle(const ObTriangle& t1, const ObTriangle& t2)
{
    return	(almost_equal_vector(t1.a, t2.a) || almost_equal_vector(t1.a, t2.b) || almost_equal_vector(t1.a, t2.c)) &&
        (almost_equal_vector(t1.b, t2.a) || almost_equal_vector(t1.b, t2.b) || almost_equal_vector(t1.b, t2.c)) &&
        (almost_equal_vector(t1.c, t2.a) || almost_equal_vector(t1.c, t2.b) || almost_equal_vector(t1.c, t2.c));
}
