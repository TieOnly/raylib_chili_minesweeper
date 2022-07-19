#pragma once
#include <string>
#include "raylib.h"
#include "Vec2.h"

namespace DrawSprites
{
    void DrawHidden(const Vec2& screenPos, const int& wTile);
    void DrawFlag(const Vec2& screenPos, const int& wTile);
    void DrawRevealed(const Vec2& screenPos, const int& wTile);
    void DrawRevealedWithNum(const Vec2& screenPos, const int& count, const int& wTile);
    void DrawBoom(const Vec2& screenPos, const int& wTile);
}