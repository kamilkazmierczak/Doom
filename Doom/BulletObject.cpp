#include "BulletObject.h"


BulletObject::BulletObject(Sphere *sphere, Bullet_Type type) :_sphere(sphere), _destroy(false), _bulletType(type)
{
	_typeOfObject = OB_SPHERE;
	_shader = new ShaderInterface("Shaders/Sphere.vs", "Shaders/Sphere.frag");
	

	GLuint VBO3, EBO3;
	glGenVertexArrays(1, &VAO3);
	glGenBuffers(1, &VBO3);
	glGenBuffers(1, &EBO3);

	glBindVertexArray(VAO3);

	glBindBuffer(GL_ARRAY_BUFFER, VBO3);
	glBufferData(GL_ARRAY_BUFFER, _sphere->getVertives().size() * sizeof(vec3), _sphere->getVertives().data(), GL_STATIC_DRAW);

	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO3);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _sphere->getIndices().size() * sizeof(GLuint), _sphere->getIndices().data(), GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);


}


BulletObject::~BulletObject()
{
}


void BulletObject::draw()
{
	glBindVertexArray(VAO3);
	glDrawElements(GL_TRIANGLES, _sphere->GetTotalIndices(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

}


void BulletObject::destroy()
{
	_destroy = true;
}

bool BulletObject::toDestroy()
{
	return _destroy;
}

void BulletObject::configShader(mat4& model, mat4& view, mat4& projection)
{
	_gameModel = model;
	_gameView = view;
	_gameProjection = projection;

	_shader->use();
	//przekazanie do shadera
	GLint modelLoc = _shader->getUniformLocation("model");
	GLint viewLoc = _shader->getUniformLocation("view");
	GLint projLoc = _shader->getUniformLocation("projection");

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(_gameModel));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(_gameView));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, value_ptr(_gameProjection));

	if (_bulletType == BU_PLAYER)	
		glUniform4f(_shader->get_uColor(), 0.0f, 0.0f, 1.0f, 1.0f);
	
	if (_bulletType == BU_ENEMY)
		glUniform4f(_shader->get_uColor(), 1.0f, 0.0f, 0.0f, 1.0f);

}

float BulletObject::getRadius()
{
	return _sphere->getRadius();
}

Object_Type BulletObject::getObjectType()
{
	return _typeOfObject;
}

Bullet_Type BulletObject::getBulletType()
{
	return _bulletType;
}