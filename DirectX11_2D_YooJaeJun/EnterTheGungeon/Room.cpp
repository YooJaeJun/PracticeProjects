#include "stdafx.h"

namespace Gungeon
{
    Room::Room()
    {
        Init();
    }

    void Room::Init()
    {
        col = new ObRect();
    }

    void Room::Release()
    {
        Character::Release();
    }

    void Room::Update()
    {
        Character::Update();
    }

    void Room::LateUpdate()
    {
    }

    void Room::Render()
    {
        Character::Render();
    }

    Int2 Room::TileLB() const
    {
        ObRect* r = dynamic_cast<ObRect*>(col);
        Int2 on;
        MAP->tilemap->WorldPosToTileIdx(r->lb(), on);
        return on;
    }

    Int2 Room::TileLT() const
    {
        ObRect* r = dynamic_cast<ObRect*>(col);
        Int2 on;
        MAP->tilemap->WorldPosToTileIdx(r->lt(), on);
        return on;
    }

    Int2 Room::TileRB() const
    {
        ObRect* r = dynamic_cast<ObRect*>(col);
        Int2 on;
        MAP->tilemap->WorldPosToTileIdx(r->rb(), on);
        return on;
    }

    Int2 Room::TileRT() const
    {
        ObRect* r = dynamic_cast<ObRect*>(col);
        Int2 on;
        MAP->tilemap->WorldPosToTileIdx(r->rt(), on);
        return on;
    }

    int Room::TileWidth() const
    {
        return TileRB().x - TileLB().x;
    }

    int Room::TileHeight() const
    {
        return TileLT().y - TileLB().y;
    }
}