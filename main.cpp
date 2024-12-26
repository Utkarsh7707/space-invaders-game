#include <raylib.h>
#include <iostream>
#include "game.hpp"
#include <string>
using namespace std;

std::string formatWithLeadingZeros(int num, int width)
{
    std::string numText = std::to_string(num);
    int leadingZeros = width - numText.length();
    return numText = std::string(leadingZeros, '0') + numText;
}
int main()
{
    Color grey = {29, 29, 27, 255};
    Color yellow = {243, 216, 63, 255};
    int offset = 50;
    int winWidth = 750;
    int winHeight = 700;
    InitWindow(winWidth + offset, winHeight + 2 * offset, "Spac Invaders");
    Font font = LoadFontEx("/home/utkarsh/Desktop/c++ games/space invader/Font/monogram.ttf", 64, 0, 0);
    Texture2D spaceShipImg = LoadTexture("/home/utkarsh/Desktop/c++ games/space invader/graphics/spaceship.png");
    InitAudioDevice();
    SetTargetFPS(60);

    Game game = Game();
    while (WindowShouldClose() != true)
    {
        UpdateMusicStream(game.music);
        game.handleInputs();
        BeginDrawing();
        game.update();
        ClearBackground(grey);
        DrawRectangleRoundedLinesEx({10, 10, 780, 780}, 0.18f, 20, 2, yellow);
        DrawLineEx({25, 730}, {775, 730}, 3, yellow);
        if (game.run)
        {
            DrawTextEx(font, "LEVEL 01", {570, 740}, 34, 2, yellow);
        }
        else
        {
            DrawTextEx(font, "GAME OVER", {570, 740}, 34, 2, yellow);
        }
        float x = 50.0;
        for (int i = 0; i < game.lives; i++)
        {
            DrawTextureV(spaceShipImg, {x, 745}, WHITE);
            x += 50;
        }
        DrawTextEx(font, "SCORE", {50, 15}, 34, 2, yellow);
        std::string scoreText = formatWithLeadingZeros(game.score,5);
        DrawTextEx(font,scoreText.c_str(),{50,40},34,2,yellow);

        DrawTextEx(font,"HIGH_SCORE",{570,15},34,2,yellow);

        std::string highscoreText = formatWithLeadingZeros(game.highScore,5);
        DrawTextEx(font,highscoreText.c_str(),{655,40},34,2,yellow);
        game.Draw();
        EndDrawing();
    }
    CloseWindow();
    CloseAudioDevice();
    return 0;
}