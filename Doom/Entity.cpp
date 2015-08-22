#include "Entity.h"


VertexBuffer* Entity::getVertexBuffer()
{
	return _vertexBuffer;
}

void Entity::setVertexBuffer(VertexBuffer *newVertexBuffer)
{
	_vertexBuffer = newVertexBuffer;
}

Vector3 Entity::getPosition()
{
	return _position;
}

void Entity::setPosition(Vector3 newPosition)
{
	_position = newPosition;
}


Vector3 Entity::getScale()
{
	return _scale;
}

void Entity::setScale(Vector3 newScale)
{
	_scale = newScale;
}

Vector3 Entity::getRotation()
{
	return _rotation;
}

void Entity::setRotation(Vector3 newRotation)
{
	_rotation = newRotation;
}


Entity::Entity(VertexBuffer *vertexBuffer, Vector3 position)
	:_vertexBuffer(vertexBuffer), _position(position), _scale(makeVector3(1.0f, 1.0f, 1.0f)),
	_rotation(makeVector3(0.0f, 0.0f, 0.0f))
{
}


Entity::~Entity()
{
}
