#pragma once
#include "AbstractObject.h"

class LaserBullet : AbstractObject
{
public:
    LaserBullet(Vector2 ship_pos);

    void drawEnemyBullet();

    Vector2 AbstractObject::getPosition();

    void AbstractObject::setPosition(Vector2 position);

    void AbstractObject::drawObject();
};

