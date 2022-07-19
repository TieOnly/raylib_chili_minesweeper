#pragma once
#include "raylib.h"
#include "Vec2.h"

class RectF
{
public:
    RectF() = default;
    RectF(int left_in, int top_in, int right_in, int bottom_in);
    RectF(const Vec2& topLeft, const Vec2& bottomRight);
    RectF(const Vec2& topLeft, const int& width, const int& height);
    static RectF FromCenter(const Vec2& center, const int& halfWidth, const int& halfHeight);
    bool IsOverLapping(const RectF& other) const;
    void DrawRectF(const Color& color) const;
public:
    int left;
    int top;
    int right;
    int bottom;
};