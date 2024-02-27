#pragma once
#include <raylib.h>

class AbstractObject
{
protected:
	Vector2 position;

	Vector2 size;

	float velocity;

public:
	virtual void drawObject() = 0;

	virtual Vector2 getPosition() = 0;

	virtual void setPosition(Vector2 position) = 0;
};

