#include "game.hpp"
#include <iostream>
#include <raylib.h>
#include<fstream>
Game::Game()
{
    initGame();
    music = LoadMusicStream("sounds/music.ogg");
    PlayMusicStream(music);
    expSound = LoadSound("sounds/explosion.ogg");
    SShitSound = LoadSound("sounds/mixkit-falling-hit-757.wav");
    gameOverSound = LoadSound("sounds/mixkit-arcade-fast-game-over-233.wav");
    scoreInc = LoadSound("sounds/mixkit-winning-a-coin-video-game-2069.wav");
}

Game::~Game()
{
    Alien::unloadImages();
    UnloadMusicStream(music);
    UnloadSound(expSound);
    UnloadSound(SShitSound);
    UnloadSound(gameOverSound);
    UnloadSound(scoreInc);
}

void Game::update()
{
    if (run)
    {
        double currTime = GetTime();
        if (currTime - timeLastSpawn > mystryShipSpawnInterval)
        {
            mystryship.spawn();
            timeLastSpawn = GetTime();
            mystryShipSpawnInterval = GetRandomValue(10, 20);
        }

        for (auto &laser : spaceship.lasers)
        {
            laser.update();
        }

        deleteInactiveLasers();
        moveAliens();
        alienShootLaser();

        for (auto &laser : alienLasers)
        {
            laser.update();
        }

        mystryship.update();
        checkForCollision();

        // Check for win condition
        if (aliens.empty())
        {
            run = false;
        }
    }
    else
    {
        if (IsKeyDown(KEY_ENTER))
        {
            Reset();
            initGame();
        }
    }
}

void Game::Draw()
{
    spaceship.Draw();

    for (auto &laser : spaceship.lasers)
    {
        laser.Draw();
    }

    for (auto &obs : obstacles)
    {
        obs.Draw();
    }

    for (auto &it : aliens)
    {
        it.Draw();
    }

    for (auto &laser : alienLasers)
    {
        laser.Draw();
    }

    mystryship.Draw();

    // Display the win message
    if (!run && aliens.empty())
    {
        DrawText("YOU WON! GAME OVER", GetScreenWidth() / 2 - MeasureText("YOU WN! GAME OVER", 40) / 2, GetScreenHeight() / 2, 40, GREEN);
        DrawText("Press ENTER to Restart", GetScreenWidth() / 2 - MeasureText("Press ENTER to Restart", 20) / 2, GetScreenHeight() / 2 + 50, 20, WHITE);
    }

    // Display game over message if the player lost
    if (!run && !aliens.empty())
    {
        // aliens.clear();
        alienLasers.clear();
        DrawText("GAME OVER", GetScreenWidth() / 2 - MeasureText("GAME OVER", 40) / 2, GetScreenHeight() / 2, 40, RED);
        DrawText("Press ENTER to Restart", GetScreenWidth() / 2 - MeasureText("Press ENTER to Restart", 20) / 2, GetScreenHeight() / 2 + 50, 20, WHITE);
    }
}

void Game::handleInputs()
{
    if (run)
    {
        if (IsKeyDown(KEY_LEFT))
        {
            spaceship.moveLeft();
        }
        else if (IsKeyDown(KEY_RIGHT))
        {
            spaceship.moveRight();
        }
        else if (IsKeyDown(KEY_SPACE))
        {
            spaceship.fireLaser();
        }
    }
}

void Game::deleteInactiveLasers()
{
    for (auto it = spaceship.lasers.begin(); it != spaceship.lasers.end();)
    {
        if (it->active == false)
        {
            it = spaceship.lasers.erase(it);
        }
        else
        {
            ++it;
        }
    }
    for (auto it = alienLasers.begin(); it != alienLasers.end();)
    {
        if (it->active == false)
        {
            it = alienLasers.erase(it);
            // std::cout<<"Laser removed"<<std::endl;
        }
        else
        {
            ++it;
        }
    }
}

std::vector<Obstacle> Game::createObs()
{
    int obsWidth = Obstacle::grid[0].size();
    float gap = (GetScreenWidth() - (4 * obsWidth)) / 5;
    for (int i = 0; i < 4; i++)
    {
        float offset = (i + 1) * gap + i * obsWidth;
        obstacles.push_back(Obstacle({offset, float(GetScreenHeight() - 200)}));
    }
    return obstacles;
}

std::vector<Alien> Game::creatAliens()
{
    std::vector<Alien> alien;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 11; j++)
        {
            int alienType;
            if (i == 0)
                alienType = 3;
            else if (i == 1 || i == 2)
                alienType = 2;
            else
                alienType = 1;
            float x = 75 + j * 55;
            float y = 110 + i * 55;
            alien.push_back(Alien(alienType, {x, y}));
        }
    }
    return alien;
}

void Game::moveAliens()
{
    for (auto &it : aliens)
    {
        if (it.position.x + it.alienImages[it.type - 1].width > GetScreenWidth()-25)
        {
            aliensDirection = -1;
            moveDownAliens(4);
        }
        if (it.position.x < 25)
        {
            aliensDirection = 1;
            moveDownAliens(4);
        }
        it.update(aliensDirection);
    }
}

void Game::moveDownAliens(int distance)
{
    for (auto &it : aliens)
    {
        it.position.y += distance;
    }
}

void Game::alienShootLaser()
{
    double currentTime = GetTime();
    if (currentTime - timeLastAlienFired >= alienShootInterval)
    {
        int rndmIdx = GetRandomValue(0, aliens.size() - 1);
        Alien &alien = aliens[rndmIdx];
        alienLasers.push_back(Laser({alien.position.x + alien.alienImages[alien.type - 1].width / 2, alien.position.y + alien.alienImages[alien.type - 1].height}, -6));
        timeLastAlienFired = GetTime();
    }
}

void Game::checkForCollision()
{
    // spaceship lasers

    for (auto &lasr : spaceship.lasers)
    {
        auto it = aliens.begin();
        while (it != aliens.end())
        {
            if (CheckCollisionRecs(it->getRect(), lasr.getRect()))
            {
                PlaySound(expSound);
                if(it->type == 1)
                {
                    score += 100;
                }
                else if(it->type == 2)
                {
                    score += 200;
                }
                else if(it->type == 3)
                {
                    score += 300;
                }
                checkForHighScore();
                it = aliens.erase(it);
                lasr.active = false;
            }
            else
            {
                it++;
            }
        }

        for (auto &obstacle : obstacles)
        {
            auto it = obstacle.blocks.begin();
            while (it != obstacle.blocks.end())
            {
                if (CheckCollisionRecs(it->getRect(), lasr.getRect()))
                {
                    it = obstacle.blocks.erase(it);
                    lasr.active = false;
                }
                else
                {
                    it++;
                }
            }
        }
        if (CheckCollisionRecs(mystryship.getRect(), lasr.getRect()))
        {
            mystryship.alive = false;
            lasr.active = false;
            score += 500;
            PlaySound(expSound);
            checkForHighScore();
        }
    }

    // Alien lasers

    for (auto &laser : alienLasers)
    {
        if (CheckCollisionRecs(laser.getRect(), spaceship.getRect()))
        {
            laser.active = false;
            PlaySound(SShitSound);
            lives--;
            if (lives == 0)
            {
                GameOver();
            }
            // std::cout<<"HIT !"<<std::endl;
        }

        for (auto &obs : obstacles)
        {
            auto it = obs.blocks.begin();
            while (it != obs.blocks.end())
            {
                if (CheckCollisionRecs(it->getRect(), laser.getRect()))
                {
                    it = obs.blocks.erase(it);
                    laser.active = false;
                }
                else
                {
                    it++;
                }
            }
        }
    }

    // Aliens collision with obstacles

    for (auto &alien : aliens)
    {
        for (auto &obs : obstacles)
        {
            auto it = obs.blocks.begin();
            while (it != obs.blocks.end())
            {
                if (CheckCollisionRecs(it->getRect(), alien.getRect()))
                {
                    it = obs.blocks.erase(it);
                }
                else
                {
                    it++;
                }
            }
        }
        if (CheckCollisionRecs(alien.getRect(), spaceship.getRect()))
        {
            // std::cout<<"Collision !"<<std::endl;
            GameOver();
        }
    }
}

void Game::GameOver()
{
    PlaySound(gameOverSound);
    run = false;
}

void Game::Reset()
{
    spaceship.Reset();
    aliens.clear();
    alienLasers.clear();
    obstacles.clear();
    timeLastSpawn = 0.0;
    mystryShipSpawnInterval = GetRandomValue(10, 20);
    run = true;
    score = 0;
    lives = 3;
}

void Game::initGame()
{
    obstacles = createObs();
    aliens = creatAliens();
    aliensDirection = 1;
    timeLastAlienFired = 0.0;
    lives = 3;
    timeLastSpawn = 0.0;
    mystryShipSpawnInterval = GetRandomValue(10, 20);
    run = true;
    score = 0;
    highScore = loadHighScoreFromFile();
}

void Game::checkForHighScore()
{
    if(score > highScore)
    {
         PlaySound(scoreInc);
        highScore = score;
        saveHighScoreToFile(highScore);
    }
}

void Game::saveHighScoreToFile(int highscore)
{
    std::ofstream highscoreFile("highscore.txt");
    if(highscoreFile.is_open())
    {
        highscoreFile << highScore;
        highscoreFile.close();
    }
    else
    {
        std::cerr<<"Failed to save highscore to file"<<std::endl;
    }
}

int Game::loadHighScoreFromFile()
{
    int loadedHighScore = 0;
    std::ifstream highscoreFile("highscore.txt");
    if(highscoreFile.is_open())
    {
        highscoreFile >> loadedHighScore;
        highscoreFile.close();
    }
    else
    {
        std::cerr<<"Failed to load highscore from file."<<std::endl;
    }
    return loadedHighScore;
}
