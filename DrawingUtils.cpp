#include "DrawingUtils.h"

void DrawingUtils::drawAllLaserBullets(int& shootItr, std::vector<LaserBullet>& allShots)
{
    for (int i = 0; i < shootItr; i++)
    {
        allShots.at(i).drawBullet();
        if (allShots.at(i).getPosition().x > 1400)
        {
            allShots.erase(allShots.begin() + i);
            shootItr--;
        }
    }
}
