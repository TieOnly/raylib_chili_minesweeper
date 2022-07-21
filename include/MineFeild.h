#pragma once
#include "raylib.h"
#include "Vec2.h"
#include "Settings.h"
#include "DrawSprites.h"

class MineField
{
private:
    class Tile
    {
    public:
        enum class State
        {
            Hidden,
            Flag,
            Revealed
        };
    public:
        void SetIsBoom();
        void SetIsRevealed();
        void FlagToggle();
        bool HasBoom() const;
        bool IsRevealed() const;
        bool IsFlag() const;
        void CountNeightborBoom();
        bool IsNoBoomNeightbor() const;
        void Draw(const Vec2& screenPos) const;
    private:
        State state = State::Hidden;
        int count = 0;
        bool hasBoom = false;
    };

public:
    MineField(const int width, const int height, const int nBooms);
    ~MineField();
    void DoRevealedClick( const Vec2& gridPos );
    void DoFlagClick( const Vec2& gridPos );
    Vec2 ScreenToGrid( const Vec2& screenPos );
    bool FuckUp();
    bool Done();
    void Draw();
private:
    void Sweeper(const Vec2& gridPos_in);
    bool NoNeightborBoom(const Vec2& gridPos);
    Tile& TileAt( const Vec2& gridPos );
private:
    int width;
    int height;
    int nBooms = 6;
    static constexpr int wTile = 20;
    int widthFeild = width*wTile;
    int heightFeild = height*wTile;
    static constexpr int wallThick = 4;
    Vec2 pos = {settings::screenW / 2 - (widthFeild/2), settings::screenH / 2 - (heightFeild/2)};
    int nFlagUsed = 0;
    int nRevealed = 0;
    bool isFuckUp = false;
    Tile* pTile = nullptr;
};