#pragma once
#include "VertexBuffer.h"
#include "Vector3.h"
#include "IObject.h"
#include <vector>

enum Entity_type {
	ENTITY_BULLET,
	ENTITY_ENEMY,
	ENTITY_MAP,
	ENTITY_R2R2,
	ENTITY_TEST
};


class Entity
{
private:
	VertexBuffer *_vertexBuffer = nullptr;
	IObject *_object = nullptr;
	Vector3 _position;
	Vector3 _scale;
	Vector3 _rotation;

	Vector3 _movementDirection;

	Vector3 _velocity;
	Vector3 _scaleVelocity;
	Vector3 _rotationVelocity;

	Vector3 _eyeVector;
	Vector3 _upVector;

	vector <ThreeVertices> *_realVertices;
	Entity_type _type;

public:

	void loadRealVertices();
	vector <ThreeVertices> *getRealVertices();
	Entity_type getType();


	VertexBuffer *getVertexBuffer();
	void setVertexBuffer(VertexBuffer *newVertexBuffer);

	IObject *getObject();
	void setObject(IObject *newObject);

	Vector3 getMovementDirection();
	void setMovementDirection(Vector3 newDirection);

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

	Entity(VertexBuffer *vertexBuffer, Vector3 position, Entity_type type);
	Entity(IObject *object, Vector3 position, Entity_type type);
	~Entity();
};

