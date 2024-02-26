#pragma once
#include <raylib.h>

class AbstractObject
{
protected:
	Vector2 position;
	Vector2 size;
	float velocity;

public:
	Vector2 getPosition();
	void setPosition(Vector2 position);
};

