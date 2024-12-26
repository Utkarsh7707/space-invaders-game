#pragma once

#include<raylib.h>
#include"spaceShip.hpp"
#include"obstacle.hpp"
#include"alien.hpp"
#include"mystry.hpp"
class Game
{
    public:
    Game();
    ~Game();
    void Draw();
    void update();
    void handleInputs();
    int lives;
    bool run;
    int score;
    int highScore;
    Music music;
    private:
    void deleteInactiveLasers();
    std::vector<Obstacle> createObs();
    std::vector<Alien> creatAliens();
    spaceShip spaceship = spaceShip();
    void moveAliens();
    void moveDownAliens(int distance);
    void alienShootLaser();
    void checkForCollision();
    void GameOver();
    void Reset();
    void initGame();
    void checkForHighScore();
    void saveHighScoreToFile(int highscore);
    int loadHighScoreFromFile();
    std::vector<Obstacle> obstacles;
    std::vector<Alien> aliens;
    std::vector<Laser> alienLasers;
    MystryShip mystryship;
    Sound expSound;
    Sound SShitSound;
    Sound gameOverSound;
    Sound scoreInc;
    constexpr static float alienShootInterval = 0.35;
    float timeLastAlienFired;
    int aliensDirection;
    float mystryShipSpawnInterval;
    float timeLastSpawn;
};