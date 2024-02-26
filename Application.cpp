#include <iostream>
#include <raylib.h>
#include "UserShip.h"
#include "Global.h"
#include "DrawingUtils.h"

/* Screen dimensions */
int height = 583;
int width = 1400;

/* Ship's starting position */
Vector2 position = { GetScreenWidth() / 10.0f, GetScreenHeight() / 2.0f };

/* Ship's velocity */
int velocity = 10.0f;

/* LaserBullet iterator */
int shootItr = 0;

/* List with all LaserBullets */
std::vector<LaserBullet> allShots;

/* Main class of the space shooter game app */
int main()
{
	InitWindow(width, height, "Space Shooter");

	SetTargetFPS(60);

	Image image = LoadImage("C:/SpaceShooterProject/Graphics/player2.png");
	shipTexture = LoadTextureFromImage(image);
	UnloadImage(image);

	Image image_shoot = LoadImage("C:/SpaceShooterProject/Graphics/shoot1.png");
	laserTexture = LoadTextureFromImage(image_shoot);
	UnloadImage(image_shoot);

	UserShip *ship = new UserShip(velocity, position);

	DrawingUtils* drawing = new DrawingUtils();

	/* Game loop */
	while (!WindowShouldClose())
	{
		BeginDrawing();

		ClearBackground(GetColor(0x052c46ff));

		/* Code */

		ship->drawShip();

		ship->shoot(shootItr, allShots, ship->getPosition());

		drawing->drawAllLaserBullets(shootItr, allShots);

		EndDrawing();
	}

	delete(ship);
	delete(drawing);

	UnloadTexture(shipTexture);
	UnloadTexture(laserTexture);

	CloseWindow();

	return 0;
}

