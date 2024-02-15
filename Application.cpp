#include <iostream>
#include <raylib.h>

/* Screen dimensions */
int height = 583;
int width = 1400;

/* Main class of the space shooter game app */
int main()
{
	InitWindow(width, height, "Space Shooter");

	SetTargetFPS(60);

	/* Game loop */
	while (!WindowShouldClose())
	{
		BeginDrawing();

		/* Code */

		EndDrawing();
	}

	CloseWindow();

	return 0;
}

