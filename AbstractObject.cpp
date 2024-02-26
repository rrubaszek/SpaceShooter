#include "AbstractObject.h"

Vector2 AbstractObject::getPosition()
{
	return position;
}

void AbstractObject::setPosition(Vector2 position)
{
	this->position = position;
}
