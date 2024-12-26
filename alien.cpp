#include "alien.hpp"

Texture2D Alien::alienImages[3] = {};
Alien::Alien(int type, Vector2 posiition)
{
    this->type = type;
    this->position = posiition;

    if (alienImages[type - 1].id == 0)
    {
        switch (type)
        {
        case 1:
            alienImages[0] = LoadTexture("/home/utkarsh/Desktop/c++ games/space invader/graphics/alien_1.png");
            break;

        case 2:
            alienImages[1] = LoadTexture("/home/utkarsh/Desktop/c++ games/space invader/graphics/alien_2.png");
            break;
        case 3:
            alienImages[2] = LoadTexture("/home/utkarsh/Desktop/c++ games/space invader/graphics/alien_3.png");
            break;
        default:
            alienImages[0] = LoadTexture("/home/utkarsh/Desktop/c++ games/space invader/graphics/alien_1.png");
            break;
        }
    }
}

void Alien::Draw()
{
    DrawTextureV(alienImages[type-1], position, WHITE);
}

int Alien::getType()
{
    return type;
}

Rectangle Alien::getRect()
{
    return {position.x,position.y,float(alienImages[type-1].width),float(alienImages[type-1].height)};
}

void Alien::unloadImages()
{
    for(int i = 0 ; i <3 ;i++)
    {
        UnloadTexture(alienImages[i]);
    }
}

void Alien::update(int direction)
{
    position.x += direction;
}
