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

public:

	VertexBuffer *getVertexBuffer();
	void setVertexBuffer(VertexBuffer *newVertexBuffer);

	Vector3 getPosition();
	void setPosition(Vector3 newPosition);

	Vector3 getScale();
	void setScale(Vector3 newScale);

	Vector3 getRotation();
	void setRotation(Vector3 newRotation);

	Entity(VertexBuffer *vertexBuffer, Vector3 position);
	~Entity();
};

