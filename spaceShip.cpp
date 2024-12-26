#include "spaceShip.hpp"
#include <raylib.h>

spaceShip::spaceShip()
{
    image = LoadTexture("/home/utkarsh/Desktop/c++ games/space invader/graphics/spaceship.png");
    position.x = (GetScreenWidth() - image.width) / 2;
    position.y = GetScreenHeight() - image.height -100;
    LastFireTime = 0.0;
    laserSound = LoadSound("sounds/mixkit-short-laser-gun-shot-1670.wav");
}
spaceShip::~spaceShip()
{
    UnloadSound(laserSound);
    UnloadTexture(image);
}

void spaceShip::Draw()
{
    DrawTextureV(image, position, WHITE);
}

void spaceShip::moveLeft()
{
    position.x -= 7;
    if (position.x <= 25)
    {
        position.x = 25;
    }
}
void spaceShip::moveRight()
{
    position.x += 7;
    if (position.x >= GetScreenWidth() - image.width-25)
    {
        position.x = GetScreenWidth() - image.width-25;
    }
}

void spaceShip::fireLaser()
{
    if (GetTime() - LastFireTime >= 0.35)
    {
        lasers.push_back(Laser({position.x + image.width / 2 - 2, position.y}, 6));
        LastFireTime = GetTime();
        PlaySound(laserSound);
    }
}

Rectangle spaceShip::getRect()
{
    return {position.x,position.y,float(image.width),float{image.height}};
}

void spaceShip::Reset()
{
    position.x = ((GetScreenWidth()- image.width)/2.0f);
    position.y = GetScreenHeight() - image.height-100;
    lasers.clear();
}
