#pragma once
#include <vector>
#include "UserShip.h"
#include "EnemyShip.h"

class Collisions
{
public:
	void hitEnemy(Vector2 screen, int& shootItr, std::vector<EnemyShip>& allEnemies, std::vector<LaserBullet>& allShots);
	void hitUserShip(UserShip& userShip, std::vector<EnemyShip>& allEnemies);
};

