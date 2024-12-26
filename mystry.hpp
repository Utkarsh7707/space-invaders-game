#pragma once
#include<raylib.h>

class MystryShip
{
    public:
    MystryShip();
    ~MystryShip();
    void update();
    void Draw();
    void spawn();
    bool alive;
    Rectangle getRect();
    private:
    Vector2 position;
    Texture2D image;
    int speed;
};