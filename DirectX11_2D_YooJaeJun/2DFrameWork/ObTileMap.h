#pragma once
class Tile
{
public:
    int         F, G, H; //Ÿ�� ���
    Int2        idx;    //Ÿ�� �ε���
    Tile* P;      //���� ���Ž�Ų Ÿ��
    bool        isFind; //�˻������� �ִ°�?
    int         state;
    Vector2     Pos; //Ÿ���� ����

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

enum TileState
{
    TILE_NONE,
    TILE_WALL,
    TILE_DOOR,
    TILE_TRAP,
    TILE_WATER,
    TILE_SIZE
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

    virtual ~ObTileMap();
    virtual void        ResizeTile(Int2 TileSize);
    virtual void        Load();
    virtual void        CreateTileCost();

    void                Save();
    void                Render() override;
    void                SetTile(Int2 TileIdx, Int2 FrameIdx, int ImgIdx = 0,
        int TileState = TILE_NONE, Color color = Color(0.5f, 0.5f, 0.5f, 0.5f));

    void                RenderGui(Int2& GuiPickingIdx, int& ImgIdx);
    bool                WorldPosToTileIdx(Vector2 Wpos, Int2& TileIdx);
    int                 GetTileState(Int2 TileIdx);
    Int2                GetTileSize() { return tileSize; };


    Vector2             GetTilePosition(Int2 TileIdx);
    bool                PathFinding(Int2 sour, Int2 dest, OUT vector<Tile*>& way);
};

