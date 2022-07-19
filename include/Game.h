#pragma once
#include <string>
#include "raylib.h"
#include "MineFeild.h"
#include "Settings.h"

class Game
{
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

    bool IsGameOver = false;
    bool IsWin = false;

    MineField mineFeild;
};
