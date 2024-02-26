#include "LaserBullet.h"
#include "Global.h"

Texture2D laserTexture;

LaserBullet::LaserBullet(Vector2 shipPosition)
{
	this->position.x = shipPosition.x;
	this->position.y += shipTexture.height / 2.0f;
	this->size = { 20.0f, 8.0f };
	this->velocity = 16.0f;
}

void LaserBullet::drawBullet()
{
	position.x += velocity;

	//DrawTextureV(laserTexture, position, WHITE);
	DrawCircleV(position, 20.0f, MAROON);

	DrawFPS(10, 10);
}


void LaserBullet::drawEnemyBullet()
{
	position.x -= velocity;

	DrawTextureV(laserTexture, position, WHITE);

	DrawFPS(10, 10);
}