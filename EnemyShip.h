#pragma once
#include "AbstractObject.h"
class EnemyShip : public AbstractObject
{
public:
	EnemyShip();

	void AbstractObject::drawObject();

	Vector2 AbstractObject::getPosition();

	void AbstractObject::setPosition(Vector2 position);

	void setDrawable(bool);

	bool isDrawable();

private:
	float y;

	bool draw;
};

