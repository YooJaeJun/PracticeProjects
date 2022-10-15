#include "framework.h"

ObTileMap::ObTileMap()
{
    SafeRelease(vertexBuffer);
    SafeDeleteArray(vertices);
    for (int i = 0; i < imageCount; i++)
        SafeDelete(tileImages[i]);

    //타일 가로 세로 개수
    tileSize.x = 20;
    tileSize.y = 20;

    file = "EnterTheGungeon.txt";
    //하나의 타일 크기
    scale = Vector2(50.0f, 50.0f);

    tileImages[0] = new ObImage(L"Empty.png");
    tileImages[0]->maxFrame = Int2(10, 10);
    tileImages[1] = new ObImage(L"EnterTheGungeon/Level/Tileset.png");
    tileImages[1]->maxFrame = Int2(10, 10);
    tileImages[2] = new ObImage(L"Tile.png");
    tileImages[2]->maxFrame = Int2(8, 6);
    tileImages[3] = new ObImage(L"Tile2.png");
    tileImages[3]->maxFrame = Int2(11, 7);

    ResizeTile(tileSize);
}

ObTileMap::~ObTileMap()
{
    SafeRelease(vertexBuffer);
    SafeDeleteArray(vertices);

    for (int i = 0; i < imageCount; i++)
        SafeDelete(tileImages[i]);
}

void ObTileMap::CreateTileCost()
{
    for (int i = 0; i < Tiles.size(); i++)
    {
        Tiles[i].clear();
    }
    Tiles.clear();

    Tiles.resize(tileSize.x);
    for (int i = 0; i < Tiles.size(); i++)
    {
        Tiles[i].resize(tileSize.y);
    }

    Vector2 half = scale * 0.5f;
    Update();
    for (int i = 0; i < tileSize.x; i++)
    {
        for (int j = 0; j < tileSize.y; j++)
        {
            Tiles[i][j].idx = Int2(i, j);
            Tiles[i][j].state = GetTileState(Tiles[i][j].idx);
            Tiles[i][j].roomIdx = GetTileRoomIndex(Tiles[i][j].idx);
            Tiles[i][j].doorDir = GetTileDoorDir(Tiles[i][j].idx);

            Tiles[i][j].Pos.x = i * scale.x + GetWorldPos().x + half.x;
            Tiles[i][j].Pos.y = j * scale.y + GetWorldPos().y + half.y;
        }
    }
}

//사이즈 재조정, 정정 재조정
void ObTileMap::ResizeTile(Int2 TileSize)
{
    VertexTile* Vertices = new VertexTile[TileSize.x * TileSize.y * 6];

    //세로
    for (int i = 0; i < TileSize.y; i++)
    {
        //가로
        for (int j = 0; j < TileSize.x; j++)
        {
            int tileIdx = TileSize.x * i + j;
            //0
            Vertices[tileIdx * 6].position.x = 0.0f + j;
            Vertices[tileIdx * 6].position.y = 0.0f + i;
            Vertices[tileIdx * 6].uv = Vector2(0.0f, 1.0f);
            //1                             
            Vertices[tileIdx * 6 + 1].position.x = 0.0f + j;
            Vertices[tileIdx * 6 + 1].position.y = 1.0f + i;
            Vertices[tileIdx * 6 + 1].uv = Vector2(0.0f, 0.0f);
            //2                             
            Vertices[tileIdx * 6 + 2].position.x = 1.0f + j;
            Vertices[tileIdx * 6 + 2].position.y = 0.0f + i;
            Vertices[tileIdx * 6 + 2].uv = Vector2(1.0f, 1.0f);
            //3
            Vertices[tileIdx * 6 + 3].position.x = 1.0f + j;
            Vertices[tileIdx * 6 + 3].position.y = 1.0f + i;
            Vertices[tileIdx * 6 + 3].uv = Vector2(1.0f, 0.0f);
            //4
            Vertices[tileIdx * 6 + 4].position.x = 1.0f + j;
            Vertices[tileIdx * 6 + 4].position.y = 0.0f + i;
            Vertices[tileIdx * 6 + 4].uv = Vector2(1.0f, 1.0f);
            //5
            Vertices[tileIdx * 6 + 5].position.x = 0.0f + j;
            Vertices[tileIdx * 6 + 5].position.y = 1.0f + i;
            Vertices[tileIdx * 6 + 5].uv = Vector2(0.0f, 0.0f);
        }
    }

    //Copy
    if (vertices)
    {
        Int2 Min = Int2(min(TileSize.x, tileSize.x), min(TileSize.y, tileSize.y));
        for (int i = 0; i < Min.y; i++)
        {
            for (int j = 0; j < Min.x; j++)
            {
                int SrcIdx = tileSize.x * i + j;
                int DestIdx = TileSize.x * i + j;

                for (int k = 0; k < 6; k++)
                {
                    Vertices[DestIdx * 6 + k] = vertices[SrcIdx * 6 + k];
                }
            }
        }
    }

    SafeDeleteArray(vertices);
    vertices = Vertices;
    tileSize = TileSize;

    SafeRelease(vertexBuffer);
    //CreateVertexBuffer
    {
        D3D11_BUFFER_DESC desc;
        desc = { 0 };
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.ByteWidth = sizeof(VertexTile) * tileSize.x * tileSize.y * 6;
        desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        D3D11_SUBRESOURCE_DATA data = { 0 };
        data.pSysMem = vertices;
        HRESULT hr = D3D->GetDevice()->CreateBuffer(&desc, &data, &vertexBuffer);
        Check(hr);
    }
}

void ObTileMap::RenderGui(Int2& GuiPickingIdx, int& ImgIdx)
{
    if (ImGui::InputInt("ImgIdx", &ImgIdx))
    {
        if (ImgIdx > imageCount - 1)
        {
            ImgIdx = 0; //첫번째이미지로 돌리기
        }
        else if (ImgIdx < 0)
        {
            //마지막 이미지로 돌리기
            ImgIdx = imageCount - 1;
        }
    }

    Int2 MF = tileImages[ImgIdx]->maxFrame;
    ImVec2 size;
    size.x = 200.0f / (float)MF.x;
    size.y = 200.0f / (float)MF.y;

    //텍스쳐 좌표
    ImVec2 LT, RB;
    int index = 0;

    for (UINT i = 0; i < MF.y; i++)
    {
        for (UINT j = 0; j < MF.x; j++)
        {
            if (j != 0)
            {
                //같은줄에 배치
                ImGui::SameLine();
            }

            //텍스쳐 좌표
            LT.x = 1.0f / MF.x * j;
            LT.y = 1.0f / MF.y * i;
            RB.x = 1.0f / MF.x * (j + 1);
            RB.y = 1.0f / MF.y * (i + 1);

            ImGui::PushID(index);
            if (ImGui::ImageButton((void*)tileImages[ImgIdx]->SRV, size, LT, RB))
            {
                GuiPickingIdx.x = j;
                GuiPickingIdx.y = i;
            }
            index++;
            ImGui::PopID();
        }
    }
}

void ObTileMap::Render()
{
    if (!isVisible)return;
    GameObject::Render();

    for (int i = 0; i < imageCount; i++)
    {
        if (tileImages[i])
        {
            D3D->GetDC()->PSSetShaderResources(i, 1, &tileImages[i]->SRV);
            D3D->GetDC()->PSSetSamplers(i, 1, &tileImages[i]->sampler);
        }
    }

    tileMapShader->Set();

    UINT stride = sizeof(VertexTile);
    UINT offset = 0;

    //버텍스버퍼 바인딩
    D3D->GetDC()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
    D3D->GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    D3D->GetDC()->Draw(tileSize.x * tileSize.y * 6, 0);
}

void ObTileMap::SetTile(Int2 TileIdx, Int2 FrameIdx, int ImgIdx, int TileState, Color color, int roomIdx, DirState dir)
{
    int tileIdx = tileSize.x * TileIdx.y + TileIdx.x;

    vertices[tileIdx * 6 + 0].uv.x = FrameIdx.x / (float)tileImages[ImgIdx]->maxFrame.x;
    vertices[tileIdx * 6 + 1].uv.x = FrameIdx.x / (float)tileImages[ImgIdx]->maxFrame.x;
    vertices[tileIdx * 6 + 5].uv.x = FrameIdx.x / (float)tileImages[ImgIdx]->maxFrame.x;

    vertices[tileIdx * 6 + 2].uv.x = (FrameIdx.x + 1.0f) / (float)tileImages[ImgIdx]->maxFrame.x;
    vertices[tileIdx * 6 + 3].uv.x = (FrameIdx.x + 1.0f) / (float)tileImages[ImgIdx]->maxFrame.x;
    vertices[tileIdx * 6 + 4].uv.x = (FrameIdx.x + 1.0f) / (float)tileImages[ImgIdx]->maxFrame.x;

    vertices[tileIdx * 6 + 3].uv.y = FrameIdx.y / (float)tileImages[ImgIdx]->maxFrame.y;
    vertices[tileIdx * 6 + 1].uv.y = FrameIdx.y / (float)tileImages[ImgIdx]->maxFrame.y;
    vertices[tileIdx * 6 + 5].uv.y = FrameIdx.y / (float)tileImages[ImgIdx]->maxFrame.y;

    vertices[tileIdx * 6 + 2].uv.y = (FrameIdx.y + 1.0f) / (float)tileImages[ImgIdx]->maxFrame.y;
    vertices[tileIdx * 6 + 0].uv.y = (FrameIdx.y + 1.0f) / (float)tileImages[ImgIdx]->maxFrame.y;
    vertices[tileIdx * 6 + 4].uv.y = (FrameIdx.y + 1.0f) / (float)tileImages[ImgIdx]->maxFrame.y;

    for (int i = 0; i < 6; i++)
    {
        vertices[tileIdx * 6 + i].tileMapIdx = ImgIdx;
        vertices[tileIdx * 6 + i].color = color;
        vertices[tileIdx * 6 + i].tileState = TileState;
        vertices[tileIdx * 6 + i].tileRoomIdx = roomIdx;
        vertices[tileIdx * 6 + i].tileDir = dir;
    }

    // SubResource - CPU와 GPU의 중간다리 역할
    D3D->GetDC()->UpdateSubresource(vertexBuffer, 0, NULL, vertices, 0, 0);
}

bool ObTileMap::WorldPosToTileIdx(Vector2 Wpos, Int2& TileIdx)
{
    Wpos -= GetWorldPos();

    Vector2 tileCoord;

    tileCoord.x = Wpos.x / scale.x;
    tileCoord.y = Wpos.y / scale.y;

    if ((tileCoord.x < 0) or (tileCoord.y < 0) or
        (tileCoord.x >= tileSize.x) or (tileCoord.y >= tileSize.y))
    {
        return false;
    }

    TileIdx.x = tileCoord.x;
    TileIdx.y = tileCoord.y;

    return true;
}

Vector2 ObTileMap::TileIdxToWorldPos(Int2 TileIdx)
{
    Vector2 Wpos;
    Wpos.x = TileIdx.x * scale.x;
    Wpos.y = TileIdx.y * scale.y;
    Wpos += GetWorldPos();
    return Wpos;
}

TileState ObTileMap::GetTileState(Int2 TileIdx)
{
    int tileIdx = tileSize.x * TileIdx.y + TileIdx.x;

    return static_cast<TileState>(vertices[tileIdx * 6].tileState);
}

void ObTileMap::SetTileState(Int2 TileIdx, TileState tileState)
{
    int tileIdx = tileSize.x * TileIdx.y + TileIdx.x;

    vertices[tileIdx * 6].tileState = static_cast<int>(tileState);
}

Vector2 ObTileMap::GetTilePosition(Int2 TileIdx)
{
    int tileIdx = tileSize.x * TileIdx.y + TileIdx.x;

    return Vector2(vertices[tileIdx * 6].position.x, vertices[tileIdx * 6].position.y);
}

int ObTileMap::GetTileRoomIndex(Int2 TileIdx)
{
    int tileIdx = tileSize.x * TileIdx.y + TileIdx.x;

    return vertices[tileIdx * 6].tileRoomIdx;
}

void ObTileMap::SetTileRoomIndex(Int2 TileIdx, const int tileRoomIndex)
{
    int tileIdx = tileSize.x * TileIdx.y + TileIdx.x;

    vertices[tileIdx * 6].tileRoomIdx = tileRoomIndex;
}

DirState ObTileMap::GetTileDoorDir(Int2 TileIdx)
{
    int tileIdx = tileSize.x * TileIdx.y + TileIdx.x;

    return vertices[tileIdx * 6].tileDir;
}

void ObTileMap::SetTileDoorDir(Int2 TileIdx, const DirState doorDir)
{
    int tileIdx = tileSize.x * TileIdx.y + TileIdx.x;

    vertices[tileIdx * 6].tileDir = doorDir;
}

void ObTileMap::Save()
{
    ofstream fout;
    string path = "../Contents/TileMap/" + file;

    //ios::out 쓰기 용으로 열겟다
    fout.open(path.c_str(), ios::out);

    //파일 열렷니?
    if (fout.is_open())
    {
        for (int i = 0; i < imageCount; i++)
        {
            fout << i << " ";

            if (tileImages[i])
            {
                string imgFile = "";
                imgFile.assign(tileImages[i]->file.begin(), tileImages[i]->file.end());

                fout << imgFile << " ";
                fout << tileImages[i]->maxFrame.x << " " << tileImages[i]->maxFrame.y << endl;
            }
            else
            {
                fout << "N" << endl;
            }
        }
    }

    fout << "TileSize " << tileSize.x << " " << tileSize.y << endl;
    fout << "TileScale " << scale.x << " " << scale.y << endl;
    fout << "TilePosition " << GetWorldPos().x << " " << GetWorldPos().y << endl;

    for (int i = 0; i < tileSize.y; i++)
    {
        //가로
        for (int j = 0; j < tileSize.x; j++)
        {
            int tileIdx = tileSize.x * i + j;
            fout << j << " " << i << " "
                << vertices[tileIdx * 6 + 1].uv.x << " " << vertices[tileIdx * 6 + 1].uv.y << " "
                << vertices[tileIdx * 6 + 2].uv.x << " " << vertices[tileIdx * 6 + 2].uv.y << " "
                << vertices[tileIdx * 6].color.x << " " << vertices[tileIdx * 6].color.y << " "
                << vertices[tileIdx * 6].color.z << " " << vertices[tileIdx * 6].color.w << " "
                << vertices[tileIdx * 6].tileMapIdx << " " << vertices[tileIdx * 6].tileState << endl;
        }
    }

    //열엇으면 닫아라
    fout.close();
}

void ObTileMap::Load()
{
    ifstream fin;
    string path = "../Contents/TileMap/" + file;
    fin.open(path.c_str(), ios::in);

    string temp;

    if (fin.is_open())
    {
        for (int i = 0; i < imageCount; i++)
        {
            SafeDelete(tileImages[i]);

            int idx; string Imgfile;
            fin >> idx;
            fin >> Imgfile;

            if (Imgfile != "N")
            {
                wstring wImgFile = L"";
                wImgFile.assign(Imgfile.begin(), Imgfile.end());

                tileImages[i] = new ObImage(wImgFile);
                fin >> tileImages[i]->maxFrame.x >> tileImages[i]->maxFrame.y;
            }
        }
    }

    Int2 TileSize;
    fin >> temp >> TileSize.x >> TileSize.y;

    ResizeTile(TileSize);

    fin >> temp >> scale.x >> scale.y;

    Vector2 pos;
    fin >> temp >> pos.x >> pos.y;
    SetWorldPos(pos);

    for (int i = 0; i < tileSize.y; i++)
    {
        //가로
        for (int j = 0; j < tileSize.x; j++)
        {
            int temp; Vector2 MinUV, MaxUV; Color color; float tileMapIdx, tileMapState;

            fin >> temp >> temp >> MinUV.x >> MinUV.y >> MaxUV.x >> MaxUV.y
                >> color.x >> color.y >> color.z >> color.w >> tileMapIdx >> tileMapState;

            int tileIdx = tileSize.x * i + j;

            vertices[tileIdx * 6].uv = Vector2(MinUV.x, MaxUV.y);
            vertices[tileIdx * 6 + 1].uv = Vector2(MinUV.x, MinUV.y);
            vertices[tileIdx * 6 + 2].uv = Vector2(MaxUV.x, MaxUV.y);
            vertices[tileIdx * 6 + 3].uv = Vector2(MaxUV.x, MinUV.y);
            vertices[tileIdx * 6 + 4].uv = Vector2(MaxUV.x, MaxUV.y);
            vertices[tileIdx * 6 + 5].uv = Vector2(MinUV.x, MinUV.y);

            for (int k = 0; k < 6; k++)
            {
                vertices[tileIdx * 6 + k].color = color;
                vertices[tileIdx * 6 + k].tileMapIdx = tileMapIdx;
                vertices[tileIdx * 6 + k].tileState = tileMapState;
            }
        }
    }

    D3D->GetDC()->UpdateSubresource(vertexBuffer, 0, NULL, vertices, 0, 0);

    fin.close();
}

bool ObTileMap::IntersectTilePos(Vector2 wpos)
{
    Int2 on;
    if (WorldPosToTileIdx(wpos, on))
    {
        return GetTileState(on) == TileState::wall;
    }
    return false;
}

bool ObTileMap::IntersectTileObj(ObRect* colTile)
{
    Vector2 pos;
    bool flag = false;

    pos = colTile->lt();
    flag |= IntersectTilePos(pos);
    pos = colTile->lb();
    flag |= IntersectTilePos(pos);
    pos = colTile->rt();
    flag |= IntersectTilePos(pos);
    pos = colTile->rb();
    flag |= IntersectTilePos(pos);

    return flag;
}

bool ObTileMap::PathFinding(Int2 sour, Int2 dest, OUT vector<Tile*>& way, bool checkDiagnoal)
{
    //둘중에 하나가 벽이면 갈 수 있는길이 없다.
    //if (Tiles[dest.x][dest.y].state == TileState::wall)
    //{
    //    return false;
    //}

    //기존에 있던 길은 전부 비운다.
    way.clear();

    //출발지 목적지 같으면
    if (sour == dest)
    {
        return false;
    }

    //타일 비용 초기화
    for (int i = 0; i < tileSize.x; i++)
    {
        for (int j = 0; j < tileSize.y; j++)
        {
            Tiles[i][j].ClearCost();
        }
    }

    //우선순위 큐
    //            원소타입, 컨테이너타입, 비교함수
    priority_queue<PTile, vector<PTile>, Compare> List;

    //리스트에 출발지를 추가
    Tile* pTemp = &Tiles[sour.x][sour.y];
    pTemp->G = 0;//출발지 현재비용은 0
    pTemp->ClacH(dest);//목적지까지 예상비용 만들기
    pTemp->ClacF(); //총예상비용 만들기

    //          주소,  예상비용
    List.push({ pTemp, pTemp->F });

    //인접 타일 비용검사
    vector<Int2> LoopIdx;

    while (1)
    {
        //꺼낼 F값이 없다는 
        if (List.empty())
        {
            return false;
        }

        //탐색노드 받아오기
        PTile Temp = List.top();

        //탐색목록에서 제외
        Temp.first->isFind = true;

        //맨윗값 빼버리기
        List.pop();

        //맨윗값이 도착점이면 종료
        if (Temp.first->idx == dest)
        {
            break;
        }

        //왼쪽타일이 존재할때
        if (Temp.first->idx.x > 0)
        {
            LoopIdx.push_back(Int2(Temp.first->idx.x - 1,
                Temp.first->idx.y));
        }

        //위쪽타일이 존재할때
        if (Temp.first->idx.y > 0)
        {
            LoopIdx.push_back(Int2(Temp.first->idx.x,
                Temp.first->idx.y - 1));
        }

        //오른쪽타일이 존재할때
        if (Temp.first->idx.x < tileSize.x - 1)
        {
            LoopIdx.push_back(Int2(Temp.first->idx.x + 1,
                Temp.first->idx.y));
        }

        //아래쪽타일이 존재할때
        if (Temp.first->idx.y < tileSize.y - 1)
        {
            LoopIdx.push_back(Int2(Temp.first->idx.x,
                Temp.first->idx.y + 1));
        }

        if (checkDiagnoal)
        {
            //LB
            if (Temp.first->idx.x > 0 &&
                Temp.first->idx.y < tileSize.y - 1)
            {
                Int2 on = Int2(Temp.first->idx.x - 1,
                    Temp.first->idx.y + 1);

                // 주위 벽이 있을 땐 대각선으로 가지 않기
                if (Tiles[on.x - 1][on.y].state != TileState::wall && 
                    Tiles[on.x][on.y - 1].state != TileState::wall)
                {
                    LoopIdx.push_back(on);
                }
            }

            //LT
            if (Temp.first->idx.x > 0 &&
                Temp.first->idx.y > 0)
            {
                Int2 on = Int2(Temp.first->idx.x - 1,
                    Temp.first->idx.y - 1);

                if (Tiles[on.x - 1][on.y].state != TileState::wall &&
                    Tiles[on.x][on.y + 1].state != TileState::wall)
                {
                    LoopIdx.push_back(on);
                }
            }

            //RB
            if (Temp.first->idx.x < tileSize.x - 1 &&
                Temp.first->idx.y < tileSize.y - 1)
            {
                Int2 on = Int2(Temp.first->idx.x + 1,
                    Temp.first->idx.y + 1);

                if (Tiles[on.x + 1][on.y].state != TileState::wall &&
                    Tiles[on.x][on.y - 1].state != TileState::wall)
                {
                    LoopIdx.push_back(on);
                }
            }

            //RT
            if (Temp.first->idx.x < tileSize.x - 1 &&
                Temp.first->idx.y > 0)
            {
                Int2 on = Int2(Temp.first->idx.x + 1,
                    Temp.first->idx.y - 1);

                if (Tiles[on.x + 1][on.y].state != TileState::wall &&
                    Tiles[on.x][on.y + 1].state != TileState::wall)
                {
                    LoopIdx.push_back(on);
                }
            }
        }

        //상하좌우(대각선)타일 비용검사
        for (int i = 0; i < LoopIdx.size(); i++)
        {
            Tile* loop = &Tiles[LoopIdx[i].x][LoopIdx[i].y];

            //벽이 아닐때
            if (loop->state != TileState::wall && 
                loop->state != TileState::door)
            {
                //예상비용 만들기
                loop->ClacH(dest);

                //현재 가지고있는 비용이 클때
                if (loop->G > Temp.first->G + 10)
                {
                    //비용갱신
                    loop->G = Temp.first->G + 10;
                    loop->ClacF();

                    //누구로부터 갱신인지 표시
                    loop->P = Temp.first;

                    //이 타일이 찾은적 없던 타일이면 리스트에 추가
                    if (!loop->isFind)
                    {
                        List.push({ loop,loop->F });
                    }
                }
            }
        }
        LoopIdx.clear();
    }

    //도착지가 설정이 되었을때
    Tile* p = &Tiles[dest.x][dest.y];
    //dest 4,1 -> 4,2 -> 4,3 -> 3,3 ->2,3-> 1,3 ->
    while (1)
    {
        way.emplace_back(p);

        p = p->P;

        if (p == nullptr)
        {
            break;
        }
    }
    return true;
}

void Tile::ClearCost()
{
    F = G = H = INT_MAX;
    P = nullptr;
    isFind = false;
}

void Tile::ClacH(Int2 DestIdx)
{
    int tempX = abs(idx.x - DestIdx.x) * 10;
    int tempY = abs(idx.y - DestIdx.y) * 10;

    H = tempX + tempY;
}

void Tile::ClacF()
{
    F = G + H;
}