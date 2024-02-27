#pragma once
#include <vector>
#include "LaserBullet.h"
#include "EnemyShip.h"

class DrawingUtils
{
public:
	void drawAllLaserBullets(int& shootItr, std::vector<LaserBullet>& allShots);

	void drawEnemyLaserBullets(std::vector<LaserBullet>& allEnemyBullets);

	void drawAllEnemies(std::vector<EnemyShip>& allEnemies, Vector2 getScreen);
};

