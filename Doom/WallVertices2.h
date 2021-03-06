#pragma once
#include "VertexData.h"



VertexDataPNT wallVerticesSide[] = {
	// Positions           // Normals           // Texture Coords
	-10.0f, -1.5f, -0.25f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,				//TY�
	15.0f, -1.5f, -0.25f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
	15.0f, 1.5f, -0.25f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
	15.0f, 1.5f, -0.25f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f, //#3
	-10.0f, 1.5f, -0.25f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
	-10.0f, -1.5f, -0.25f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, //#1

	-10.0f, -1.5f, 0.25f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,				//PRZOD
	15.0f, -1.5f, 0.25f, 0.0f, 0.0f, 1.0f, 7.5f, 0.0f,
	15.0f, 1.5f, 0.25f, 0.0f, 0.0f, 1.0f, 7.5f, 3.0f,
	15.0f, 1.5f, 0.25f, 0.0f, 0.0f, 1.0f, 7.5f, 3.0f, //#3
	-10.0f, 1.5f, 0.25f, 0.0f, 0.0f, 1.0f, 0.0f, 3.0f,
	-10.0f, -1.5f, 0.25f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, //#1

	-10.0f, 1.5f, 0.25f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,				//LEWA
	-10.0f, 1.5f, -0.25f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
	-10.0f, -1.5f, -0.25f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	-10.0f, -1.5f, -0.25f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	-10.0f, -1.5f, 0.25f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	-10.0f, 1.5f, 0.25f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

	15.0f, 1.5f, 0.25f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,				//PRAWA
	15.0f, 1.5f, -0.25f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
	15.0f, -1.5f, -0.25f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	15.0f, -1.5f, -0.25f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	15.0f, -1.5f, 0.25f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	15.0f, 1.5f, 0.25f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

	-10.0f, -1.5f, -0.25f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,				//Dӣ
	15.0f, -1.5f, -0.25f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
	15.0f, -1.5f, 0.25f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
	15.0f, -1.5f, 0.25f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
	-10.0f, -1.5f, 0.25f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
	-10.0f, -1.5f, -0.25f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,

	-10.0f, 1.5f, -0.25f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,				//G�RA
	15.0f, 1.5f, -0.25f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
	15.0f, 1.5f, 0.25f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	15.0f, 1.5f, 0.25f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	-10.0f, 1.5f, 0.25f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
	-10.0f, 1.5f, -0.25f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
};



VertexDataPNT wallVerticesfront[] = {
	// Positions           // Normals           // Texture Coords
	-10.0f, -1.5f, -0.25f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,				//TY�
	10.0f, -1.5f, -0.25f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
	10.0f, 1.5f, -0.25f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
	10.0f, 1.5f, -0.25f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f, //#3
	-10.0f, 1.5f, -0.25f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
	-10.0f, -1.5f, -0.25f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, //#1

	-10.0f, -1.5f, 0.25f,		0.0f, 0.0f, 1.0f,		0.0f, 0.0f,				//PRZOD
	10.0f, -1.5f, 0.25f,			0.0f, 0.0f, 1.0f,		7.5f, 0.0f,
	10.0f, 1.5f, 0.25f,			0.0f, 0.0f, 1.0f,		7.5f, 3.0f,
	10.0f, 1.5f, 0.25f,			0.0f, 0.0f, 1.0f,		7.5f, 3.0f, //#3
	-10.0f, 1.5f, 0.25f,			0.0f, 0.0f, 1.0f,		0.0f, 3.0f,
	-10.0f, -1.5f, 0.25f,		0.0f, 0.0f, 1.0f,		0.0f, 0.0f, //#1

	-10.0f, 1.5f, 0.25f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,				//LEWA
	-10.0f, 1.5f, -0.25f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
	-10.0f, -1.5f, -0.25f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	-10.0f, -1.5f, -0.25f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	-10.0f, -1.5f, 0.25f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	-10.0f, 1.5f, 0.25f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

	10.0f, 1.5f, 0.25f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,				//PRAWA
	10.0f, 1.5f, -0.25f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
	10.0f, -1.5f, -0.25f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	10.0f, -1.5f, -0.25f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	10.0f, -1.5f, 0.25f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	10.0f, 1.5f, 0.25f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

	-10.0f, -1.5f, -0.25f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,				//Dӣ
	10.0f, -1.5f, -0.25f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
	10.0f, -1.5f, 0.25f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
	10.0f, -1.5f, 0.25f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
	-10.0f, -1.5f, 0.25f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
	-10.0f, -1.5f, -0.25f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,

	-10.0f, 1.5f, -0.25f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,				//G�RA
	10.0f, 1.5f, -0.25f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
	10.0f, 1.5f, 0.25f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	10.0f, 1.5f, 0.25f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	-10.0f, 1.5f, 0.25f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
	-10.0f, 1.5f, -0.25f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
};

