#include <iostream>
#include <raylib.h>
#include <chrono>
#include "UserShip.h"
#include "Global.h"
#include "DrawingUtils.h"

/* Ship's velocity */
float velocity = 10.0f;

/* LaserBullet iterator */
int shootItr = 0;

/* Enemy iterator */
int enemyItr = 0;

/* Enemy shoot iterator */
int enemyShootItr = 0;

/* List with all LaserBullets */
static std::vector<LaserBullet> allShots;

/* List with all EnemyShips */
static std::vector<EnemyShip> allEnemies;

/* List with all enemy lasers */
static std::vector<LaserBullet> allEnemyShots;

/* Duration of an enemy's spawn cycle */
std::chrono::duration<float> enemyDuration;

/* Duration of an enemys' shot cycle */
std::chrono::duration<float> enemyLaserDuration;

/* Main class of the space shooter game app */
int main()
{
	InitWindow(width, height, "Space Shooter");

	/* Ship's starting position */
	Vector2 position = { GetScreenWidth() / 10.0f, GetScreenHeight() / 2.0f };

	/* Screen float dimensions in a vector */
	Vector2 screen = { GetScreenWidth() * 1.0f, GetScreenHeight() * 1.0f };

	SetTargetFPS(60);

	Image image = LoadImage("C:/SpaceShooterProject/SpaceShooter/Graphics/player2.png");
	shipTexture = LoadTextureFromImage(image);
	UnloadImage(image);

	Image image_shoot = LoadImage("C:/SpaceShooterProject/SpaceShooter/Graphics/shoot1.png");
	laserTexture = LoadTextureFromImage(image_shoot);
	UnloadImage(image_shoot);

	Texture2D background = LoadTexture("C:/SpaceShooterProject/SpaceShooter/Graphics/MainBG_zloty.png");

	for (int i = 0; i < 4; i++)
	{
		EnemyShip enemy;

		enemy.setPosition(screen);

		allEnemies.push_back(enemy);
	}

	UserShip *ship = new UserShip(velocity, position);

	DrawingUtils* drawing = new DrawingUtils();

	/* Time when the game starts */
	auto laserStartTime = std::chrono::high_resolution_clock::now();

	/* Time when the game starts */
	auto enemyStartTime = std::chrono::high_resolution_clock::now();

	/* Game loop */
	while (!WindowShouldClose())
	{
		BeginDrawing();

		ClearBackground(GetColor(0x052c46ff));

		DrawTexture(background, 0.0, 0.0, WHITE);

		/* Code */

		/* Time after one cycle for shot */
		auto laserEndTime = std::chrono::high_resolution_clock::now();

		/* Time after one cycle for spawn */
		auto enemyEndTime = std::chrono::high_resolution_clock::now();

		enemyDuration = enemyEndTime - enemyStartTime;

		/* Spawning enemies */
		if (enemyDuration.count() > 1.5f)
		{
			allEnemies.at(enemyItr).setDrawable(true);
			enemyItr++;

			enemyItr = (enemyItr == allEnemies.size()) ? 0 : enemyItr;

			enemyStartTime = enemyEndTime;
		}

		enemyLaserDuration = laserEndTime - laserStartTime;

		/* Enemies shot */
		if (enemyLaserDuration.count() > 0.5f && allEnemies.at(enemyShootItr).isDrawable() == true)
		{
			LaserBullet shoot(allEnemies.at(enemyShootItr).getPosition());

			allEnemyShots.push_back(shoot);

			enemyShootItr++;

			enemyShootItr = (enemyShootItr == allEnemies.size()) ? 0 : enemyShootItr;

			laserStartTime = laserEndTime;
		}

		drawing->drawAllEnemies(allEnemies, screen);

		drawing->drawEnemyLaserBullets(allEnemyShots);

		ship->drawObject();

		ship->shoot(shootItr, allShots, ship->getPosition());

		drawing->drawAllLaserBullets(shootItr, allShots);

		EndDrawing();
	}

	delete(ship);
	delete(drawing);

	UnloadTexture(shipTexture);
	UnloadTexture(laserTexture);
	UnloadTexture(background);

	CloseWindow();

	return 0;
}

