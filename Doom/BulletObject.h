#pragma once

#include "IObject.h"
#include "Sphere.h"


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
	ShaderInterface *_shader;
	bool _destroy;
	Bullet_Type  _bulletType;

public:
	void draw();
	void configShader(mat4& model, mat4& view, mat4& projection);
	bool toDestroy();
	void destroy();
	
	Object_Type getObjectType();
	Bullet_Type getBulletType();

	float getRadius();

	BulletObject(Sphere* sphere, Bullet_Type type);
	~BulletObject();
};

