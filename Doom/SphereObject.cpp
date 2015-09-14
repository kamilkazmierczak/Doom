#include "SphereObject.h"


SphereObject::SphereObject(Sphere *sphere) :_sphere(sphere)
{
	_typeOfObject = OB_SPHERE;
	_shader = new ShaderInterface("sphere.vs", "sphere.frag");



	GLuint VBO3, EBO3;
	glGenVertexArrays(1, &VAO3);
	glGenBuffers(1, &VBO3);
	glGenBuffers(1, &EBO3);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO3);

	glBindBuffer(GL_ARRAY_BUFFER, VBO3);
	glBufferData(GL_ARRAY_BUFFER, _sphere->getVertives().size() * sizeof(vec3), _sphere->getVertives().data(), GL_STATIC_DRAW);

	//EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO3);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _sphere->getIndices().size() * sizeof(GLuint), _sphere->getIndices().data(), GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	//SFERA KONFIGURACJA END

}


SphereObject::~SphereObject()
{
}


void SphereObject::draw()
{
	//cout << "Rysuje z klasy SphereObject" << endl;
	glBindVertexArray(VAO3);
	glDrawElements(GL_TRIANGLES, _sphere->GetTotalIndices(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

}



void SphereObject::configShader(mat4& model, mat4& view, mat4& projection)
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



}

float SphereObject::getRadius()
{
	return _sphere->getRadius();
}

Object_Type SphereObject::getObjectType()
{
	return _typeOfObject;
}