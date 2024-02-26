#pragma once
#include "AbstractObject.h"
#include <vector>
#include "LaserBullet.h"

class UserShip : public AbstractObject
{
public:
	UserShip(float velocity, Vector2 position);
	void shoot(int& shootItr, std::vector<LaserBullet>& allShots, Vector2 shipPosition);
	void drawShip();
};

