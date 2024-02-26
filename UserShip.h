#pragma once
#include "AbstractObject.h"
#include <vector>
#include "LaserBullet.h"

class UserShip : public AbstractObject
{
public:
	UserShip(int velocity, Vector2 position, Texture2D shipTexture);
	void shoot(int& shootItr, std::vector<LaserBullet>& allShots, Vector2 shipPosition);
	void drawShip();

private:
	Texture2D shipTexture;
};

