#include <assert.h>
#include "Game.h"
#include "raylib.h"
// #include <iostream>
// std::cout << pField->TileAt(mouseGridpos).IsFlag() << std::endl;

Game::Game(int width, int height, int fps, std::string title)
    :
    menu({settings::screenW / 2, 100})
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
    if(state == State::Game)
    {
        if(!IsGameOver && !IsWin)
        {
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                Vec2 mouseGridpos = pField->ScreenToGrid( {GetMouseX(), GetMouseY()} );
                pField->DoRevealedClick( mouseGridpos );
                if(pField->FuckUp())
                {
                    IsGameOver = true;
                }
            }
            else if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
            {
                Vec2 mouseGridpos = pField->ScreenToGrid( {GetMouseX(), GetMouseY()} );
                pField->DoFlagClick( mouseGridpos );
            }
            
            if(pField->Done())
            {
                IsWin = true;
            }
        }
        else
        {
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                DestroyFeild();
                state = State::Menu;
                IsGameOver = false;
                IsWin = false;
            }
        }
    }
    else
    {
        Vec2 mousePos = { GetMouseX(), GetMouseY() };
        bool clickLeft = false;
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            clickLeft = true;
        }
        SelectMenu::Size type = menu.ProcessSelect(mousePos, clickLeft);
        switch (type)
        {
        case SelectMenu::Size::Small:
            CreateFeild( 6, 6, 6 );
            state = State::Game;
            break;
        case SelectMenu::Size::Medium:
            CreateFeild( 10, 10, 10 );
            state = State::Game;
            break;
        case SelectMenu::Size::Large:
            CreateFeild( 15, 15, 15 );
            state = State::Game;
            break;
        default:
            break;
        }
    }
}
void Game::CreateFeild(const int width, const int height, const int nBooms)
{
    assert( pField == nullptr );
    pField = new MineField{ width, height, nBooms };
}
void Game::DestroyFeild()
{
    pField->FreeResource();
    delete pField;
    pField = nullptr;
}
void Game::Draw()
{
    ClearBackground(BLACK);
    if(state == State::Game)
    {
        pField->Draw();
        if(IsGameOver)
        {
            DrawTextCenter("Game Over", 50);
        }
        else if(IsWin)
        {
            DrawTextCenter("Win", 50);
        }
    }
    else
    {
        menu.Draw();
    }
}
void Game::DrawTextCenter(const char* title, int fontSize)
{
    const int widthText = MeasureText(title, fontSize);
    DrawText(title, int(settings::screenW / 2 - widthText / 2), int(settings::screenH / 2 - fontSize / 2), fontSize, ORANGE);
}
