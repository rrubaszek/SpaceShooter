#include "Collisions.h"

void Collisions::hitEnemy(Vector2 screen, int& shootItr, std::vector<EnemyShip>& allEnemies, std::vector<LaserBullet>& allShots)
{
    for (int i = 0; i < allShots.size(); i++)
    {
        for (int j = 0; j < allEnemies.size(); j++)
        {
            if (allShots.at(i).getPosition().x > allEnemies.at(j).getPosition().x - 20.0
                && allShots.at(i).getPosition().x < allEnemies.at(j).getPosition().x + 20.0
                && allShots.at(i).getPosition().y > allEnemies.at(j).getPosition().y - 20.0
                && allShots.at(i).getPosition().y < allEnemies.at(j).getPosition().y + 20.0)
            {
                allEnemies.at(j).setPosition(screen);

                allEnemies.at(j).setDrawable(false);

                allShots.erase(allShots.begin() + i);

                shootItr--;

                break;
            }
        }
    }
}