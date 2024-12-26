#pragma once

#include<raylib.h>

class Alien
{
    public:
    Alien(int type,Vector2 posiition);
    void update(int direction);
    void Draw();
    int getType();
    Rectangle getRect();
    Vector2 position;
    int type;
    static Texture2D alienImages[3];
    static void unloadImages();

};