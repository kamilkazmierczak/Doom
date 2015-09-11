#pragma once
#include "VertexBuffer.h"
#include "Vector3.h"
#include "IObject.h"
#include <vector>

class Entity
{
private:
	VertexBuffer *_vertexBuffer;
	IObject *_object;
	Vector3 _position;
	Vector3 _scale;
	Vector3 _rotation;

	Vector3 _velocity;
	Vector3 _scaleVelocity;
	Vector3 _rotationVelocity;

	Vector3 _eyeVector;
	Vector3 _upVector;

public:

	VertexBuffer *getVertexBuffer();
	void setVertexBuffer(VertexBuffer *newVertexBuffer);

	IObject *getObject();
	void setObject(IObject *newObject);

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

	Vector3 getEyeVector();
	void setEyeVector(Vector3 newEyeVector);

	Vector3 getUpVector();
	void setUpVector(Vector3 newUpVector);

	Entity(VertexBuffer *vertexBuffer, Vector3 position);
	Entity(IObject *object, Vector3 position);
	~Entity();
};

