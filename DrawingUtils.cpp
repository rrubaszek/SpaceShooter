#include "DrawingUtils.h"
#include "Global.h"

void DrawingUtils::drawAllLaserBullets(int& shootItr, std::vector<LaserBullet>& allShots)
{
    for (int i = 0; i < shootItr; i++)
    {
        allShots.at(i).drawObject();
        if (allShots.at(i).getPosition().x > width)
        {
            allShots.erase(allShots.begin() + i);
            shootItr--;
        }
    }
}

void DrawingUtils::drawEnemyLaserBullets(std::vector<LaserBullet>& allEnemyBullets)
{
    for (int i = 0; i < allEnemyBullets.size(); i++)
    {
        allEnemyBullets.at(i).drawEnemyBullet();

        if (allEnemyBullets.at(i).getPosition().x < 0)
        {
            allEnemyBullets.erase(allEnemyBullets.begin() + i);
        }
    }
}

void DrawingUtils::drawAllEnemies(std::vector<EnemyShip>& allEnemies, Vector2 getScreen)
{
    for (int i = 0; i < allEnemies.size(); i++)
    {
        if (allEnemies.at(i).isDrawable() == true)
        {
            allEnemies.at(i).drawObject();
        }
        if (allEnemies.at(i).getPosition().x < 0)
        {
            allEnemies.at(i).setPosition(getScreen);

            allEnemies.at(i).setDrawable(false);
        }
    }
}