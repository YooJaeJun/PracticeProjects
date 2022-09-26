#pragma once
class ObRect: public GameObject, public StaticVertexCount<ObRect>
{
private:
    static ID3D11Buffer* fillVertexBuffer;
    static ID3D11Buffer* vertexBuffer;

public:
    static void CreateStaticMember();
    static void DeleteStaticMember();

public:
    ObRect();
    void Render()override;
    Vector2 lb();
    Vector2 rb();
    Vector2 lt();
    Vector2 rt();
};

