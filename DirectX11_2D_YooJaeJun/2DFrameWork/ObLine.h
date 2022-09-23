#pragma once
// 선
class ObLine : public GameObject, public StaticVertexCount<ObLine>
{
private:
    static ID3D11Buffer* vertexBuffer;

public:
    static void CreateStaticMember();
    static void DeleteStaticMember();
    void Render();


public:
    Vector2 v;
    Vector2 w;
    bool isBad = false;

public:
    ObLine();
    ObLine(const ObLine& l) = default;
    ObLine(ObLine&&) = default;
    ObLine(const Vector2& v1, const Vector2& v2);

    bool operator<(const ObLine& other) const; // visited 판별용
    bool operator>(const ObLine& other) const;  // priority_queue 정렬용
    ObLine& operator=(const ObLine& e);
    ObLine& operator=(ObLine&&) = default;
    bool operator ==(const ObLine & e) const;

public:
    bool almostEqualLine(const ObLine& e1, const ObLine& e2);
};


