#pragma once
class ObStarPointed : public GameObject
{
private:
    static const int VertexCountForFill = 31;
    static ID3D11Buffer* fillVertexBuffer;
    static ID3D11Buffer* vertexBuffer;

public:
    static void CreateStaticMember();
    static void DeleteStaticMember();

public:
    ObStarPointed();
    void Render()override;
};

