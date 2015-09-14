#pragma once

#include "IObject.h"
#include "Sphere.h"
//#include "ShaderInterface.h"

#include <iostream>

using namespace std;
using namespace glm;

class SphereObject : public IObject
{
private:
	GLuint VAO3;
	Sphere *_sphere;
	ShaderInterface *_shader; //na razie stala (tworzona w konstruktorze)

public:
	void draw();
	void configShader(mat4& model, mat4& view, mat4& projection);
	Object_Type getObjectType();

	//tylko SphereObject
	float getRadius();

	SphereObject(Sphere* sphere);
	~SphereObject();
};

