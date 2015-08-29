#pragma once
#include "Vector3.h"
#include "Vector2.h"

typedef struct {

	Vector3 positionCoordinates;

}VertexDataP;


typedef struct {
	Vector3 positionCoordinates;
	Vector3 normalCoordinates;

}VertexDataPN; //for normals

typedef struct {
	Vector3 positionCoordinates;
	Vector3 normalCoordinates;
	Vector2 textureCoordinates;

}VertexDataPNT; //for texture