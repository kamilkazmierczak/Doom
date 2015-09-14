#define _USE_MATH_DEFINES
#include <cmath>

#include "Sphere.h"


Sphere::Sphere(float radius, int slices, int stacks) :_radius(radius), _slices(slices), _stacks(stacks)
{
	makeVertices();
	makeIndices();
}


Sphere::~Sphere()
{
}

void Sphere::makeVertices()
{
	//fill vertices array 
	float const R = 1.0f / (_slices - 1);
	float const S = 1.0f / (_stacks - 1);
	int count = 0;

	for (int r = 0; r < _slices; ++r) {
		for (int s = 0; s < _stacks; ++s) {
			float const y = (float)(sin(-M_PI_2 + M_PI * r * R));
			float const x = (float)(cos(2 * M_PI * s * S) * sin(M_PI * r  * R));
			float const z = (float)(sin(2 * M_PI * s * S) * sin(M_PI * r  * R));

			//vec3 tmp = vec3(x, y, z)*_radius;
			//cout << tmp.x << " " << tmp.y << " " << tmp.z << endl;
			_vertices.push_back(vec3(x, y, z)*_radius);
			count++;
		}
	}
}


void Sphere::makeIndices()
{
	//fill indices array 
	for (int r = 0; r < _slices; ++r) {
		for (int s = 0; s < _stacks; ++s) {
			int curRow = r * _stacks;
			int nextRow = (r + 1) * _stacks;
			_indices.push_back(curRow + s);
			_indices.push_back(nextRow + s);
			_indices.push_back(nextRow + (s + 1));

			_indices.push_back(curRow + s);
			_indices.push_back(nextRow + (s + 1));
			_indices.push_back(curRow + (s + 1));
		}
	}
}

void Sphere::test()
{
	
	cout << "Vertives" << endl;

	for (vector<vec3>::iterator iterator = _vertices.begin(); iterator != _vertices.end(); iterator++)
	{
		//cout << iterator->x << " " << iterator->y << " " << iterator->z << endl;
	}
}


float Sphere::getRadius()
{
	return _radius;
}


vector<vec3> Sphere::getVertives()
{
	return _vertices;
}

vector<GLuint> Sphere::getIndices()
{
	return _indices;
}


int Sphere::GetTotalVertices()
{
	return _slices*_stacks;
}

int Sphere::GetTotalIndices()
{
	//6 faces with 2 triangles each with 3 vertices
	return _slices*_stacks * 2 * 3;
}