#pragma once
#include "VertexData.h"


VertexDataPNT floorVertices[] = {
	// Positions          // Normals         // Texture Coords
		10.0f, -0.5f, 15.0f,		0.0f, 1.0f, 0.0f,	6.2f, 0.0f,
		-10.0f, -0.5f, 15.0f,		0.0f, 1.0f, 0.0f,	0.0f, 0.0f,
		-10.0f, -0.5f, -10.0f,		0.0f, 1.0f, 0.0f,	0.0f, 7.0f,

		10.0f, -0.5f, 15.0f,		0.0f, 1.0f, 0.0f,	6.2f, 0.0f, //#1
		-10.0f, -0.5f, -10.0f,		0.0f, 1.0f, 0.0f,	0.0f, 7.0f, //#3
		10.0f, -0.5f, -10.0f,		0.0f, 1.0f, 0.0f,	6.2f, 7.0f
};

//VertexDataPNT floorVertices[] = {
//	// Positions          // Normals         // Texture Coords
//	8.0f, -0.5f, 8.0f, 0.0f, 1.0f, 0.0f, 5.0f, 0.0f,
//	-8.0f, -0.5f, 8.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
//	-8.0f, -0.5f, -8.0f, 0.0f, 1.0f, 0.0f, 0.0f, 5.0f,
//
//	8.0f, -0.5f, 8.0f, 0.0f, 1.0f, 0.0f, 5.0f, 0.0f,
//	-8.0f, -0.5f, -8.0f, 0.0f, 1.0f, 0.0f, 0.0f, 5.0f,
//	8.0f, -0.5f, -8.0f, 0.0f, 1.0f, 0.0f, 5.0f, 5.0f
//};

//info
//pierwsze +2 (8+2) nie robilo zadnego problemu