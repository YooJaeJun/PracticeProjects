#pragma once
enum class TileState
{
    none,
    wall,
    door,
    trap,
    water,
    tileSize
};

class Tile
{
public:
    int         F, G, H; //타일 비용
    Int2        idx;    //타일 인덱스
    Tile*       P;      //나를 갱신시킨 타일
    bool        isFind; //검사한적이 있는가?
    TileState   state;
    Vector2     Pos; //타일의 중점

    void ClearCost();
    void ClacH(Int2 DestIdx);
    void ClacF();
};

//typedef int a;
//a b;

//map<key, value>

//typedef
using PTile = pair<Tile*, int>;

struct compare
{
    bool operator()(PTile& a, PTile& b)
    {
        return a.second > b.second;
    }
};

class ObTileMap : public GameObject
{
protected:
    VertexTile*             vertices;
    ID3D11Buffer*           vertexBuffer;
    Int2                    tileSize;   //10x10 , 4x4
    vector<vector<Tile>>    Tiles;

public:
    ObImage*                tileImages[4];
    string                  file;

public:
    ObTileMap();

    virtual         ~ObTileMap();
    virtual void    ResizeTile(Int2 TileSize);
    virtual void    Load();
    virtual void    CreateTileCost();

    void            Save();
    void            Render() override;
    void            SetTile(Int2 TileIdx, Int2 FrameIdx, int ImgIdx = 0,
        int TileState = none, Color color = Color(0.5f, 0.5f, 0.5f, 0.5f));

    void            RenderGui(Int2& GuiPickingIdx, int& ImgIdx);
    bool            WorldPosToTileIdx(Vector2 Wpos, Int2& TileIdx);
    Vector2         TileIdxToWorldPos(Int2 TileIdx);
    TileState       GetTileState(Int2 TileIdx);
    void            SetTileState(Int2 TileIdx, TileState tileState);
    Int2            GetTileSize() { return tileSize; };


    Vector2         GetTilePosition(Int2 TileIdx);
    bool            PathFinding(Int2 sour, Int2 dest, OUT vector<Tile*>& way);
};

