#pragma once
enum class TileState
{
    none,
    floor,
    wall,
    door,
    max
};

const int imageCount = 4;

class Tile
{
public:
    int         F, G, H; //타일 비용
    Int2        idx;    //타일 인덱스
    Tile*       P;      //나를 갱신시킨 타일
    bool        isFind; //검사한적이 있는가?
    Vector2     Pos; //타일의 중점
    TileState   state;
    int         roomIdx;
    int         doorDir;

    void ClearCost();
    void ClacH(Int2 DestIdx);
    void ClacF();
};

using PTile = pair<Tile*, int>;

struct Compare
{
    bool operator()(PTile& a, PTile& b)
    {
        return a.second > b.second;
    }
};

class ObTileMap : public GameObject
{
public:
    ObTileMap();

    virtual         ~ObTileMap();
    virtual void    CreateTileCost();
    virtual void    ResizeTile(Int2 TileSize);

    void            RenderGui(Int2& GuiPickingIdx, int& ImgIdx);
    void            Render() override;
    void            SetTile(Int2 TileIdx, Int2 FrameIdx, int ImgIdx = 0,
        int TileState = (int)TileState::none, Color color = Color(0.5f, 0.5f, 0.5f, 0.5f), 
        int roomIndex = -1, DirState dir = DirState::dirNone);

    void            Save();
    virtual void    Load();

    bool            WorldPosToTileIdx(Vector2 Wpos, Int2& TileIdx);
    Vector2         TileIdxToWorldPos(Int2 TileIdx);
    TileState       GetTileState(Int2 TileIdx);
    void            SetTileState(Int2 TileIdx, TileState tileState);
    Int2            GetTileSize() { return tileSize; };
    Vector2         GetTilePosition(Int2 TileIdx);
    int             GetTileRoomIndex(Int2 TileIdx);
    void            SetTileRoomIndex(Int2 TileIdx, const int tileRoomIndex);
    DirState        GetTileDoorDir(Int2 TileIdx);
    void            SetTileDoorDir(Int2 TileIdx, const DirState doorDir);

    bool            IntersectTilePos(Vector2 wpos);
    bool            IntersectTileObj(ObRect* colTile);
    bool            PathFinding(Int2 sour, Int2 dest, OUT vector<Tile*>& way, bool checkDiagnoal = true);

protected:
    VertexTile*             vertices;
    ID3D11Buffer*           vertexBuffer;
    Int2                    tileSize;   //10x10 , 4x4

public:
    vector<vector<Tile>>    Tiles;

public:
    ObImage*                tileImages[imageCount];
    string                  file;
};

