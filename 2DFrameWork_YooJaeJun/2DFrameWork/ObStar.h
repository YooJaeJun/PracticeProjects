#pragma once
class ObStar : public GameObject
{
private:
    static const int VertexCountForFill = 31;
    static ID3D11Buffer* fillVertexBuffer;
    static ID3D11Buffer* vertexBuffer;

public:
    static void CreateStaticMember();
    static void DeleteStaticMember();

public:
    ObStar();
    void Render()override;
};

