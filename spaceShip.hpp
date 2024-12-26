#pragma once
#include<raylib.h>
#include"laser.hpp"
#include<vector>
class spaceShip
{
    public:
    spaceShip();
    ~spaceShip();
    void Draw();
    void moveLeft();
    void moveRight();
    void fireLaser();
    void Reset();
    Rectangle getRect();
    std::vector<Laser> lasers;
    private:
    Texture2D image;
    Vector2 position;
    double LastFireTime;
    Sound laserSound;
};