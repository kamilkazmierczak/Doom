#include "Entity.h"


VertexBuffer* Entity::getVertexBuffer()
{
	return _vertexBuffer;
}

void Entity::setVertexBuffer(VertexBuffer *newVertexBuffer)
{
	_vertexBuffer = newVertexBuffer;
}


IObject* Entity::getObject()
{
	return _object;
}

void Entity::setObject(IObject *newObject)
{
	_object = newObject;
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

Vector3 Entity::getVelocity()
{
	return _velocity;
}

void Entity::setVelocity(Vector3 newVelocity)
{
	_velocity = newVelocity;
}

Vector3 Entity::getScaleVelocity()
{
	return _scaleVelocity;
}

void Entity::setScaleVelocity(Vector3 newVelocity)
{
	_scaleVelocity = newVelocity;
}

Vector3 Entity::getRotationVelocity()
{
	return _rotationVelocity;
}

void Entity::setRotationVelocity(Vector3 newRotationVelocity)
{
	_rotationVelocity = newRotationVelocity;
}

Vector3 Entity::getEyeVector()
{
	return _eyeVector;
}

void Entity::setEyeVector(Vector3 newEyeVector)
{
	_eyeVector = newEyeVector;
}

Vector3 Entity::getUpVector()
{
	return _upVector;
}

void Entity::setUpVector(Vector3 newUpVector)
{
	_upVector = newUpVector;
}

Entity::Entity(VertexBuffer *vertexBuffer, Vector3 position)
	:_vertexBuffer(vertexBuffer), _position(position), _scale(makeVector3(1.0f, 1.0f, 1.0f)),
	_rotation(makeVector3(0.0f, 0.0f, 0.0f)), _velocity(makeVector3(0.0f, 0.0f, 0.0f)),
	_scaleVelocity(makeVector3(0.0f, 0.0f, 0.0f)), _rotationVelocity(makeVector3(0.0f, 0.0f, 0.0f)),
	_eyeVector(makeVector3(0.0f, 0.0f, 0.0f)), _upVector(makeVector3(0.0f, 0.0f, 0.0f))
{
}

Entity::Entity(IObject *object, Vector3 position)
	:_object(object), _position(position), _scale(makeVector3(1.0f, 1.0f, 1.0f)),
	_rotation(makeVector3(0.0f, 0.0f, 0.0f)), _velocity(makeVector3(0.0f, 0.0f, 0.0f)),
	_scaleVelocity(makeVector3(0.0f, 0.0f, 0.0f)), _rotationVelocity(makeVector3(0.0f, 0.0f, 0.0f)),
	_eyeVector(makeVector3(0.0f, 0.0f, 0.0f)), _upVector(makeVector3(0.0f, 0.0f, 0.0f))
{
}

Entity::~Entity()
{
}
