#pragma once
#include "ShaderInterface.h"
// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
using namespace glm;

enum Object_Type{
	OB_MODEL,
	OB_SPHERE
};


class IObject
{
private:
	

protected:
	Object_Type _typeOfObject;
	mat4 _gameModel;
	mat4 _gameView;
	mat4 _gameProjection;

	//do detekcji kolizji
	/*vector <ThreeVertices> *_myVertices;
	vector <ThreeVertices> *_myRealVertices;*/
	//void loadVertices(GLvoid *table, GLsizeiptr size, GLsizeiptr dataSize);

public:

	virtual void draw() = 0;
	//virtual ShaderInterface* getShader() = 0; //TYLKO NA CZAS TESTOW SFERY (model tego na bank nie bd mial)
	virtual void configShader(mat4& model, mat4& view, mat4& projection) = 0;
	virtual Object_Type getObjectType() = 0;

	IObject();
	virtual ~IObject();
};

