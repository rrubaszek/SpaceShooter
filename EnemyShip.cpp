#include "EnemyShip.h"
#include <random>

auto generator = std::mt19937(std::random_device()());

EnemyShip::EnemyShip()
{
	velocity = 8.0f;
	position = { 0.0f, 0.0f };
}

void EnemyShip::drawObject()
{
	position.x = position.x - velocity;

	DrawCircleV(position, 20.0f, MAROON);

	DrawFPS(10, 10);
}

void EnemyShip::setPosition(Vector2 screen)
{
	auto distributionY = std::uniform_real_distribution<float>(0, screen.y);
	y = distributionY(generator);

	position = { screen.x, y };
}

Vector2 EnemyShip::getPosition()
{
	return position;
}

void EnemyShip::setDrawable(bool draw)
{
	this->draw = draw;
}

bool EnemyShip::isDrawable()
{
	return draw;
}