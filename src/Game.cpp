#include <assert.h>
#include "Game.h"
#include "raylib.h"
// #include <iostream>
// std::cout << mineFeild.TileAt(mouseGridpos).IsFlag() << std::endl;

Game::Game(int width, int height, int fps, std::string title)
    :
    mineFeild()
{
    assert(!GetWindowHandle());
    InitWindow(width, height, title.c_str());
    SetTargetFPS(fps);
}
Game::~Game() noexcept
{
    assert(GetWindowHandle());
    CloseWindow();
}
bool Game::GameShouldClose() const
{
    return WindowShouldClose();
}
void Game::Tick() 
{
    BeginDrawing();
    Update();
    Draw();
    EndDrawing();
}
void Game::Update()
{
    if(!IsGameOver && !IsWin)
    {
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            Vec2 mouseGridpos = mineFeild.ScreenToGrid( {GetMouseX(), GetMouseY()} );
            mineFeild.DoRevealedClick( mouseGridpos );
            if(mineFeild.FuckUp())
            {
                IsGameOver = true;
            }
        }
        else if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        {
            Vec2 mouseGridpos = mineFeild.ScreenToGrid( {GetMouseX(), GetMouseY()} );
            mineFeild.DoFlagClick( mouseGridpos );
        }
        
        if(mineFeild.Done())
        {
            IsWin = true;
        }
    }
}
void Game::Draw()
{
    ClearBackground(BLACK);
    mineFeild.Draw();
    if(IsGameOver)
    {
        DrawTextCenter("Game Over", 50);
    }
    else if(IsWin)
    {
        DrawTextCenter("Win", 50);
    }
}
void Game::DrawTextCenter(const char* title, int fontSize)
{
    const int widthText = MeasureText(title, fontSize);
    DrawText(title, int(settings::screenW / 2 - widthText / 2), int(settings::screenH / 2 - fontSize / 2), fontSize, ORANGE);
}
