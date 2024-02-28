#include "Collisions.h"
#include "Global.h"

void Collisions::hitEnemy(Vector2 screen, int& shootItr, std::vector<EnemyShip>& allEnemies, std::vector<LaserBullet>& allShots)
{
    for (int i = 0; i < allShots.size(); i++)
    {
        for (int j = 0; j < allEnemies.size(); j++)
        {
            if (allShots.at(i).getPosition().x > allEnemies.at(j).getPosition().x - 20.0f
                && allShots.at(i).getPosition().x < allEnemies.at(j).getPosition().x + 20.0f
                && allShots.at(i).getPosition().y > allEnemies.at(j).getPosition().y - (float)enemyTexture.height
                && allShots.at(i).getPosition().y < allEnemies.at(j).getPosition().y + (float)enemyTexture.height)
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

bool Collisions::hitUserShip(UserShip& userShip, std::vector<EnemyShip>& allEnemies, std::vector<LaserBullet>& allEnemyBullets)
{
    for (int i = 0; i < allEnemies.size(); i++)
    {
        if (userShip.getPosition().x < allEnemies.at(i).getPosition().x + 20.0f
            && userShip.getPosition().x > allEnemies.at(i).getPosition().x - 20.0f
            && userShip.getPosition().y < allEnemies.at(i).getPosition().y + 20.0f
            && userShip.getPosition().y > allEnemies.at(i).getPosition().y - 20.0f)
        {
            return true;
        }
    }

    for (int i = 0; i < allEnemyBullets.size(); i++)
    {
        if (userShip.getPosition().x < allEnemyBullets.at(i).getPosition().x + 20.0f
            && userShip.getPosition().x > allEnemyBullets.at(i).getPosition().x - 20.0f
            && userShip.getPosition().y < allEnemyBullets.at(i).getPosition().y + 20.0f
            && userShip.getPosition().y > allEnemyBullets.at(i).getPosition().y - 20.0f)
        {
            return true;
        }
    }

    return false;
}