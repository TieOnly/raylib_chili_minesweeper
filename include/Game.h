#pragma once
#include <string>
#include "raylib.h"
#include "MineFeild.h"
#include "Settings.h"
#include "SelectMenu.h"

class Game
{
private:
    enum class State
    {
        Menu,
        Game
    };
public:
    Game(int width, int height, int fps, std::string title);
    ~Game() noexcept;
    Game (const Game& another) = delete;
    Game& operator = (const Game& another) = delete;
    bool GameShouldClose() const;
    void Tick();
private:
    void Update();
    void Draw();
    void DrawTextCenter(const char* title, int fontSize);

    void CreateFeild(const int width, const int height, const int nBooms);
    void DestroyFeild();

    bool IsGameOver = false;
    bool IsWin = false;

    State state = State::Menu;

    MineField* pField = nullptr;
    SelectMenu menu;
};
