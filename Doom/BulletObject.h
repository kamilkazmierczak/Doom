#pragma once

#include "IObject.h"
#include "Sphere.h"
//#include "ShaderInterface.h"

#include <iostream>

using namespace std;
using namespace glm;

enum Bullet_Type{
	BU_PLAYER,
	BU_ENEMY
};

class BulletObject : public IObject
{
private:
	GLuint VAO3;
	Sphere *_sphere;
	ShaderInterface *_shader; //na razie stala (tworzona w konstruktorze)
	bool _destroy;
	Bullet_Type  _bulletType;//lepiej to zrobic jako dwie klasy dzidziczace z klasy BulletObject #nie ma czasu

public:
	void draw();
	void configShader(mat4& model, mat4& view, mat4& projection);
	bool toDestroy();
	void destroy();
	
	Object_Type getObjectType();
	Bullet_Type getBulletType();



	//tylko BulletObject
	float getRadius();

	BulletObject(Sphere* sphere, Bullet_Type type);
	~BulletObject();
};

