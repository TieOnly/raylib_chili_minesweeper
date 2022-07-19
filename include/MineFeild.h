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
        bool IsNoNeightborBoom() const;
        void Draw(const Vec2& screenPos) const;
    private:
        State state = State::Hidden;
        int count = 0;
        bool hasBoom = false;
    };

public:
    MineField();
    Tile& TileAt( const Vec2& gridPos );
    void DoRevealedClick( const Vec2& gridPos );
    void DoFlagClick( const Vec2& gridPos );
    Vec2 ScreenToGrid( const Vec2& screenPos );
    void Sweeper(const Vec2& gridPos);
    bool FuckUp();
    bool Done();
    void Draw();
private:
    static constexpr int width = 6;
    static constexpr int height = 6;
    static constexpr int wTile = 40;
    static constexpr int widthFeild = width*wTile;
    static constexpr int heightFeild = height*wTile;
    static constexpr int wallThick = 10;
    static constexpr int nBooms = 6;
    static constexpr Vec2 pos = {settings::screenW / 2 - (widthFeild/2), settings::screenH / 2 - (heightFeild/2)};
    int nFlagUsed = 0;
    int nRevealed = 0;
    bool isFuckUp = false;
    Tile tiles[width * height];
};