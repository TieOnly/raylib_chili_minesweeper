#include <assert.h>
#include "RectF.h"

RectF::RectF(int left_in, int top_in, int right_in, int bottom_in)
    :
    left(left_in),
    top(top_in),
    right(right_in),
    bottom(bottom_in)
{

}
RectF::RectF(const Vec2& topLeft, const Vec2& bottomRight)
    :
    RectF(topLeft.x, topLeft.y, bottomRight.x, bottomRight.y)
{

}
RectF::RectF(const Vec2& topLeft, const int& width, const int& height)
    :
    RectF(topLeft, topLeft + Vec2{width, height})
{

}
RectF RectF::FromCenter(const Vec2& center, const int& halfWidth, const int& halfHeight)
{
    const Vec2 toAngle( halfWidth, halfHeight );
    return RectF{ center - toAngle, center + toAngle};
}
bool RectF::IsOverLapping(const RectF& other) const
{
    return right > other.left && bottom > other.top 
        && left < other.right && top < other.bottom;
}
void RectF::DrawRectF(const Color& color) const
{
    assert(left >= 0 && right <= GetScreenWidth() && top >= 0 && bottom <= GetScreenHeight());
    DrawRectangle(left, top, (right - left), (bottom - top), color);
}