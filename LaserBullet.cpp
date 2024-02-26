#include "LaserBullet.h"
#include "Global.h"

Texture2D laserTexture;

LaserBullet::LaserBullet(Vector2 shipPosition)
{
	position = shipPosition;
	position.y += shipTexture.height / 2.0f;
	size = { 20.0f, 8.0f };
	velocity = 16.0f;
}

void LaserBullet::drawBullet()
{
	position.x += velocity;

	DrawTextureV(laserTexture, position, WHITE);

	DrawFPS(10, 10);
}


void LaserBullet::drawEnemyBullet()
{
	position.x -= velocity;

	DrawTextureV(laserTexture, position, WHITE);

	DrawFPS(10, 10);
}

Vector2 LaserBullet::getPosition()
{
	return position;
}