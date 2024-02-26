#include "UserShip.h"
#include "Global.h"
#include <iostream>

UserShip::UserShip(int velocity, Vector2 position, Texture2D shipTexture)
{
    this->velocity = velocity;
    this->position = position;
    this->shipTexture = shipTexture;
}

void UserShip::drawShip()
{
    if (IsKeyDown(KEY_S) && position.y < 583 - shipTexture.height)
    {
        position.y += velocity;
    }
    if (IsKeyDown(KEY_W) && position.y > 0)
    {
        position.y -= velocity;
    }
    if (IsKeyDown(KEY_D) && position.x < 1400)
    {
        position.x += velocity;
    }
    if (IsKeyDown(KEY_A) && position.x > 0)
    {
        position.x -= velocity;
    }

    DrawTextureV(shipTexture, position, WHITE);
    //DrawCircleV(ship_position, 20.0f, MAROON);

    DrawFPS(10, 10);
}

void UserShip::shoot(int& shootItr, std::vector<LaserBullet>& allShots, Vector2 shipPosition)
{
    if (IsKeyPressed(KEY_SPACE) && shootItr < 4)
    {
        LaserBullet user_shoot(shipPosition);

        allShots.push_back(user_shoot);

        shootItr++;

        std::cout << shootItr << "\n";
    }
}

