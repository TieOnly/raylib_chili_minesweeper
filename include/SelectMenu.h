#pragma once
#include "Settings.h"
#include "Vec2.h"
#include "RectF.h"

class SelectMenu
{
public: 
    enum class Size
    {
        Small,
        Medium,
        Large,
        Count,
        Invalid
    };
private:
    class Entry
    {
    public:
        Entry() = default;
        Entry(const Vec2& center_in, Size type_in)
            :
            center(center_in),
            type(type_in)
        {}
        bool IsContain(const Vec2& pos) const
        {
            if(pos.x >= center.x - fixHalfWidth && pos.x <= center.x + fixHalfWidth
             && pos.y >= center.y && pos.y <= center.y + fontSize)
            {
                return true;
            }
            return false;
        }
        Size GetType() const {return type;}
        void SetIsHighLight( const bool flag )
        {
            highlight = flag;
        }
        void SetIsHit(const bool flag)
        {
            hit = flag;
        }
        void HighLight() const
        {
            DrawRectangleLinesEx( Rectangle{float(center.x - fixHalfWidth), (float)center.y, (float)fixWidth, (float)fontSize}, 2, ORANGE);
        }
        void Draw() const
        {
            switch (type)
            {
            case Size::Small:
                DrawText("Small", center.x - MeasureText("Small", fontSize) / 2 , center.y, fontSize, WHITE);
                break;
            case Size::Medium:
                DrawText("Medium", center.x - MeasureText("Medium", fontSize) / 2, center.y, fontSize, WHITE);
                break;
            case Size::Large:
                DrawText("Large", center.x - MeasureText("Large", fontSize) / 2, center.y, fontSize, WHITE);
                break;
            default:
                break;
            }
            if(highlight)
            {
                DrawRectangleLinesEx( Rectangle{float(center.x - fixHalfWidth), (float)center.y, (float)fixWidth, float(fontSize + 2)}, 2, WHITE);
            }
        }
    private:
        static constexpr int fixWidth = settings::screenW / 3;
        static constexpr int fixHalfWidth = fixWidth / 2;
        bool highlight = false;
        bool hit = false;
        Vec2 center;
        Size type;
    };
public:
    SelectMenu(const Vec2& pos)
    {
        Vec2 center = pos;
        for(int i = 0; i < (int)Size::Count; i++)
        {
            entrys[i] = { center, Size( i ) };
            center.y += fontSize + verticalSpacing;
        }
    }   
    Size ProcessSelect(const Vec2& posMouse, const bool isHit)
    {
        ReSet();
        for(Entry& entry : entrys)
        {
            if(entry.IsContain(posMouse))
            {
                entry.SetIsHighLight(true);
                if(isHit)
                {
                    entry.SetIsHit(true);
                    return entry.GetType();
                }
            }
        }
        return Size::Invalid;
    }
    void Draw() const
    {
        for(const Entry& entry : entrys)
        {
            entry.Draw();
        }
    };
private:
    void ReSet()
    {
        for(Entry& entry: entrys)
        {
            entry.SetIsHighLight(false);
            entry.SetIsHit(false);
        }
    }
private:
    static constexpr int fontSize = 50;
    static constexpr int verticalSpacing = 10;
    Entry entrys[int(Size::Count)];
};