#pragma once
// »ï°¢Çü
class ObTriangle : public GameObject
{
private:
    static const int vertexCount = 3;
    static ID3D11Buffer* fillVertexBuffer;
    static ID3D11Buffer* vertexBuffer;

public:
    static void CreateStaticMember();
    static void DeleteStaticMember();
    void Render();


public:
    Vector2 a;
    Vector2 b;
    Vector2 c;

public:
    bool isBad = false;

public:
    ObTriangle();
    ObTriangle(const ObTriangle&) = default;
    ObTriangle(ObTriangle&&) = default;
    ObTriangle(const Vector2& v1, const Vector2& v2, const Vector2& v3);

    ObTriangle& operator=(const ObTriangle&) = default;
    ObTriangle& operator=(ObTriangle&&) = default;
    bool operator ==(const ObTriangle& t) const;

public:
    bool ContainsVertex(const Vector2& v) const;
    bool CircumCircleContains(const Vector2& v) const;

    bool almostEqualTriangle(const ObTriangle& t1, const ObTriangle& t2);
};

