#include "mystry.hpp"

MystryShip::MystryShip()
{
    image = LoadTexture("graphics/mystery.png");
    alive = false;
}

MystryShip::~MystryShip()
{
    UnloadTexture(image);
}

void MystryShip::spawn()
{
    position.y = 90;
    int side = GetRandomValue(0,1);

    if(side == 0)
    {
        position.x = 25;
        speed = 3;
    }
    else
    {
        position.x = GetScreenWidth() -image.width-25;
        speed = -3;
    }
    alive = true;
}

Rectangle MystryShip::getRect()
{
    if(alive)
    {
        return {position.x,position.y ,float(image.width),float(image.height)};
    }
    else
    {
        return {position.x,position.y,0,0};
    }
}

void MystryShip::update()
{
    if(alive)
    {
        position.x += speed;
        if(position.x > GetScreenWidth() - image.width -25|| position.x < 25)
        {
            alive = false;
        }
    }
}
void MystryShip::Draw()
{
    if(alive )
    {
        DrawTextureV(image,position,WHITE);
    }
}