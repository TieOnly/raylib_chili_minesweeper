#pragma once
#include <cmath>

class Vec2
{
public:
    Vec2() = default;
    constexpr Vec2(int x_in, int y_in)
        :
        x(x_in),
        y(y_in)
    {

    }

    constexpr int GetX() const {return x;}
    constexpr int GetY() const {return y;}
    constexpr void SetX(int x_in) {x = x_in;}
    constexpr void SetY(int y_in) {y = y_in;}
    
public:
    int x;
    int y;

public:
    constexpr bool operator == (const Vec2& rhs) const
    {
        return (x == rhs.x && y == rhs.y);
    }
    constexpr bool operator != (const Vec2& rhs) const
    {
        return !(*this == rhs);
    }
    constexpr bool operator >= (const Vec2& rhs) const
    {
        return ( x >= rhs.x && y >= rhs.y );
    }
    constexpr bool operator < (const Vec2& rhs) const
    {
        return ( x < rhs.x && y < rhs.y );
    }
    constexpr Vec2 operator + (const Vec2& rhs) const
    {
        return {x + rhs.x, y + rhs.y};
    }
    constexpr Vec2 operator + (const int& rhs) const
    {
        return {x + rhs, y + rhs};
    }
    constexpr Vec2& operator += (const Vec2& rhs) 
    {
        return (*this = *this + rhs);
    }
    constexpr Vec2 operator - (const Vec2& rhs) const
    {
        return {x - rhs.x, y - rhs.y};
    }
    constexpr Vec2 operator - (const int& rhs) const
    {
        return {x - rhs, y - rhs};
    }
    constexpr Vec2& operator -= (const Vec2& rhs) 
    {
        return (*this = *this - rhs);
    }
    constexpr Vec2 operator * (const Vec2& rhs) const
    {
        return {x * rhs.x, y * rhs.y};
    }
    constexpr Vec2 operator * (const int& rhs) const
    {
        return {x * rhs, y * rhs};
    }
    constexpr Vec2& operator *= (const Vec2& rhs) 
    {
        return (*this = *this * rhs);
    }
    constexpr Vec2 operator / (const Vec2& rhs) const
    {
        return {x / rhs.x, y / rhs.y};
    }
    constexpr Vec2 operator / (const int& rhs) const
    {
        return {x / rhs, y / rhs};
    }
    constexpr Vec2& operator /= (const Vec2& rhs) 
    {
        return (*this = *this / rhs);
    }
    constexpr int GetLengthSq() const
    {
        return (x * x + y * y);
    }
    constexpr int GetLength() const
    {
        return std::sqrt( GetLengthSq() );
    }
};
