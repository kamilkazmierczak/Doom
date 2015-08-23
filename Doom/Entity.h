#pragma once
#include "VertexBuffer.h"
#include "Vector3.h"
#include <vector>

class Entity
{
private:
	VertexBuffer *_vertexBuffer;
	Vector3 _position;
	Vector3 _scale;
	Vector3 _rotation;

	Vector3 _velocity;
	Vector3 _scaleVelocity;
	Vector3 _rotationVelocity;

public:

	VertexBuffer *getVertexBuffer();
	void setVertexBuffer(VertexBuffer *newVertexBuffer);

	Vector3 getPosition();
	void setPosition(Vector3 newPosition);

	Vector3 getScale();
	void setScale(Vector3 newScale);

	Vector3 getRotation();
	void setRotation(Vector3 newRotation);

	Vector3 getVelocity();
	void setVelocity(Vector3 newVelocity);

	Vector3 getScaleVelocity();
	void setScaleVelocity(Vector3 newVelocity);

	Vector3 getRotationVelocity();
	void setRotationVelocity(Vector3 newRotationVelocity);

	Entity(VertexBuffer *vertexBuffer, Vector3 position);
	~Entity();
};
