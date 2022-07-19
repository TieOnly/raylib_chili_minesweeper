#include <assert.h>
#include "DrawSprites.h"

void DrawSprites::DrawHidden(const Vec2& screenPos, const int& wTile)
{
    assert(screenPos.x >= 0 && screenPos.x < GetScreenWidth() && screenPos.y >= 0 && screenPos.y < GetScreenHeight());
    DrawRectangle(screenPos.x + 2, screenPos.y + 2, wTile - 2, wTile - 2, WHITE);
}
void DrawSprites::DrawFlag(const Vec2& screenPos, const int& wTile)
{
    assert(screenPos.x >= 0 && screenPos.x < GetScreenWidth() && screenPos.y >= 0 && screenPos.y < GetScreenHeight());
    DrawRectangle(screenPos.x + 2, screenPos.y + 2, wTile - 2, wTile - 2, GREEN);
}
void DrawSprites::DrawRevealed(const Vec2& screenPos, const int& wTile)
{
    assert(screenPos.x >= 0 && screenPos.x < GetScreenWidth() && screenPos.y >= 0 && screenPos.y < GetScreenHeight());
    DrawRectangle(screenPos.x + 2, screenPos.y + 2, wTile - 2, wTile - 2, GRAY);
}
void DrawSprites::DrawRevealedWithNum(const Vec2& screenPos, const int& count, const int& wTile)
{
    assert(screenPos.x >= 0 && screenPos.x < GetScreenWidth() && screenPos.y >= 0 && screenPos.y < GetScreenHeight());
    DrawRectangle(screenPos.x + 2, screenPos.y + 2, wTile - 2, wTile - 2, GRAY);
    std::string num = std::to_string(count);
    DrawText(num.c_str(), screenPos.x + 4, screenPos.y + 2, wTile, SKYBLUE);
}
void DrawSprites::DrawBoom(const Vec2& screenPos, const int& wTile)
{
    assert(screenPos.x >= 0 && screenPos.x < GetScreenWidth() && screenPos.y >= 0 && screenPos.y < GetScreenHeight());
    const int radius = int(wTile / 2);
    DrawCircle(screenPos.x + radius + 1, screenPos.y + radius + 1, radius - 2, RED);
}