#pragma once
#include "AbstractObject.h"

class LaserBullet : public AbstractObject
{
public:
    LaserBullet(Vector2 ship_pos);
    void drawBullet();
    void drawEnemyBullet();

};

