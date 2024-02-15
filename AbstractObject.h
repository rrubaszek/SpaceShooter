#pragma once
#include <raylib.h>

class AbstractObject
{
private:
	Vector2 position;
	Vector2 size;
	int velocity;

public:
	Vector2 getPosition();
	void setPosition(Vector2 position);
	void move();
	void draw();

};

