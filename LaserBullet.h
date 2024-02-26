#pragma once
#include "AbstractObject.h"

class LaserBullet : AbstractObject
{
public:
    LaserBullet(Vector2 ship_pos);
    void drawBullet();
    void drawEnemyBullet();
    Vector2 getPosition();
};

