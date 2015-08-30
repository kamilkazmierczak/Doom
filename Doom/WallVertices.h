#pragma once
#include "VertexData.h"

/*
To sa wspolrzedne podlogi obrocone o 90 stopni pozniej, problem w tym
ze przy "chyba" poprawnych cos jest nie tak ze swiatlem 
+ nawet przy tych jak zmieniam recznie pozycje y (inne pewnie tez)
to swiatlo padajace na to jest podniesione co nie powinno miec miejsca
moze to wina shadera a moze czegos innego - nie wiem
*/



VertexDataPNT wallVertices[] = {
	// Positions          // Normals         // Texture Coords
	8.0f, 0.0f, 2.0f, 0.0f, 1.0f, 0.0f, 5.0f, 0.0f,
	-8.0f, 0.0f, 2.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
	-8.0f, 0.0f, -2.0f, 0.0f, 1.0f, 0.0f, 0.0f, 5.0f,

	8.0f, 0.0f, 2.0f, 0.0f, 1.0f, 0.0f, 5.0f, 0.0f,
	-8.0f, 0.0f, -2.0f, 0.0f, 1.0f, 0.0f, 0.0f, 5.0f,
	8.0f, 0.0f, -2.0f, 0.0f, 1.0f, 0.0f, 5.0f, 5.0f
};

/*
VertexDataPNT wallVertices[] = {
	// Positions          // Normals         // Texture Coords
	8.0f, 8.0f, 0.0f,		0.0f, 0.0f, 1.0f,	 5.0f, 0.0f,
	-8.0f, 8.0f, 0.0f,		0.0f, 0.0f, 1.0f,	0.0f, 0.0f,
	-8.0f, -8.0f, 0.0f,		0.0f, 0.0f, 1.0f,	0.0f, 5.0f,

	8.0f, 8.0f, 0.0f,		0.0f, 0.0f, 1.0f,	5.0f, 0.0f,
	-8.0f, -8.0f, 0.0f,		0.0f, 0.0f, 1.0f,	0.0f, 5.0f,
	8.0f, -8.0f, 0.0f,		0.0f, 0.0f, 1.0f,	5.0f, 5.0f
};
*/