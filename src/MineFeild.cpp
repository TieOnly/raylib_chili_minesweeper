#include "MineFeild.h"
#include <assert.h>
#include <random>
#include <iostream>
MineField::MineField()
{
    std::random_device rd;
    std::mt19937 rng( rd() );
    std::uniform_int_distribution<int> xDist( 0, width - 1 );
    std::uniform_int_distribution<int> yDist( 0, height - 1 );

    Vec2 gridPos;
    for(int i = 0; i < nBooms; i++)
    {
        do {
            gridPos = { xDist( rng ), yDist( rng ) };
        } while ( TileAt( gridPos ).HasBoom() );

        TileAt( gridPos ).SetIsBoom();
    }
}
void MineField::Sweeper(const Vec2& gridPos) 
{
    const int xStart = std::max( 0, gridPos.x - 1 );
    const int yStart = std::max( 0, gridPos.y - 1 );
    const int xEnd = std::min( width - 1, gridPos.x + 1 );
    const int yEnd = std::min( height - 1, gridPos.y + 1 );

    Tile& tile = TileAt( gridPos );

    for(Vec2 gridPos{xStart, yStart}; gridPos.y <= yEnd; gridPos.y++)
    {
        for(gridPos.x = xStart; gridPos.x <= xEnd; gridPos.x++)
        {
            if(TileAt( gridPos ).HasBoom())
            {
                tile.CountNeightborBoom();
            }
        }
    }
}
void MineField::DoRevealedClick( const Vec2& gridPos )
{
    // assert(gridPos.x >= 0 && gridPos.x < width && gridPos.y >= 0 && gridPos.y < height);
    if(gridPos.x >= 0 && gridPos.x < width && gridPos.y >= 0 && gridPos.y < height)
    {
        Tile& tile = TileAt( gridPos );
        if( !tile.IsRevealed() &&  !tile.IsFlag())
        {
            if(tile.HasBoom())
            {
                isFuckUp = true;
            }
            else
            {
                tile.SetIsRevealed();
                nRevealed++;
                Sweeper( gridPos );
            }
        }
    }
}
void MineField::DoFlagClick( const Vec2& gridPos )
{
    // assert(gridPos.x >= 0 && gridPos.x < width && gridPos.y >= 0 && gridPos.y < height);
    Tile& tile = TileAt( gridPos );
    if(!tile.IsRevealed())
    {
        tile.FlagToggle();
        if(tile.IsFlag())
        {
            nFlagUsed++;
        }
        else 
        {
            nFlagUsed--;
        }
    }
}
Vec2 MineField::ScreenToGrid( const Vec2& screenPos )
{
    Vec2 posConvert = Vec2{ screenPos - pos };
    if(posConvert >= Vec2{0, 0} && posConvert < Vec2{ widthFeild, heightFeild})
    {
        return posConvert / wTile;
    }
    else
    {
        return Vec2{ -1, -1 };
    }
}
bool MineField::FuckUp()
{
    if(isFuckUp)
    {
        for(Vec2 gridPos{0, 0}; gridPos.y < height; gridPos.y++)
        {
            for(gridPos.x = 0; gridPos.x < width; gridPos.x++)
            {
                TileAt( gridPos ).SetIsRevealed();
            }
        }
        return true;
    }
    else
    {
        return false;
    }
}
bool MineField::Done()
{
    if(nFlagUsed + nRevealed == (width * height) && nFlagUsed == nBooms)
    {
        
        return true;
    }
    else
    {
        return false;
    }
}
void MineField::Draw()
{
    for(Vec2 gridPos{0, 0}; gridPos.y < height; gridPos.y++)
    {
        for(gridPos.x = 0; gridPos.x < width; gridPos.x++)
        {
            TileAt( gridPos ).Draw( pos + (gridPos * wTile) );
        }
    }
    DrawRectangle(pos.x - wallThick, pos.y - wallThick, widthFeild + 2*wallThick + 2, wallThick, SKYBLUE);
    DrawRectangle(pos.x - wallThick, pos.y, wallThick, heightFeild + 2, SKYBLUE);
    DrawRectangle(pos.x + widthFeild + 2, pos.y, wallThick, heightFeild + 2, SKYBLUE);
    DrawRectangle(pos.x - wallThick, pos.y + heightFeild + 2, widthFeild + 2*wallThick + 2, wallThick, SKYBLUE);
}
MineField::Tile& MineField::TileAt( const Vec2& gridPos )
{
    return tiles[gridPos.y * width + gridPos.x];
}

void MineField::Tile::SetIsBoom()
{
    hasBoom = true;
}
void MineField::Tile::SetIsRevealed()
{
    state = State::Revealed;
}
void MineField::Tile::FlagToggle()
{
    if(state == State::Hidden)
    {
        state = State::Flag;
    }
    else
    {
        state = State::Hidden;
    }
}
bool MineField::Tile::IsRevealed() const
{
    return state == State::Revealed;
}
bool MineField::Tile::IsFlag() const
{
    return state == State::Flag;
}
bool MineField::Tile::HasBoom() const
{
    return hasBoom;
}
void MineField::Tile::CountNeightborBoom()
{
    ++count;
}
bool MineField::Tile::IsNoNeightborBoom() const
{
    return count == 0;
}
void MineField::Tile::Draw(const Vec2& screenPos) const
{
    switch (state)
    {
    case State::Hidden:
        DrawSprites::DrawHidden(screenPos, wTile);
        break;    
    case State::Flag:
        DrawSprites::DrawFlag(screenPos, wTile);
        break;
    case State::Revealed:
        if(!HasBoom())
        {
            if(count > 0)
            {
                DrawSprites::DrawRevealedWithNum(screenPos, count, wTile);
            }
            else
            {
                DrawSprites::DrawRevealed(screenPos, wTile);
            }
        } 
        else
        {
            DrawSprites::DrawBoom(screenPos, wTile);
        }
        break;
    default:
        break;
    }
}
