#pragma once

enum TileState
{
    TILE_NONE,
    TILE_WALL,
    TILE_DOOR,
    TILE_TRAP,
    TILE_WATER,
    //TILE_SAND,
    TILE_SIZE
};

class ObTileMap : public GameObject
{
protected:
    VertexTile*             vertices;
    ID3D11Buffer*           vertexBuffer;
    Int2                    tileSize;   //10x10 , 4x4

public:
    ObImage*                tileImages[4];
    string                  file;

public:
    ObTileMap();

    virtual ~ObTileMap();
    virtual void        ResizeTile(Int2 TileSize);
    virtual bool        WorldPosToTileIdx(Vector2 WPos, Int2& TileIdx);

    void                RenderGui(Int2& GuiPickingIdx, int& ImgIdx);
    void                Render() override;
    void                SetTile(Int2 TileIdx, Int2 FrameIdx, int ImgIdx = 0,
        int TileState = TILE_NONE, Color color = Color(0.5f, 0.5f, 0.5f, 0.5f));
};

