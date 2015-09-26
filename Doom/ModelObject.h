#pragma once
#include "IObject.h"
#include "Model.h"
#include "IArtificialIntelligence.h"

class ModelObject : public IObject
{
private:
	Model *_model;
	ShaderInterface *_shader; 
	vector <ThreeVertices> *_myRealVertices;
	GLfloat _health; 
	IArtificialIntelligence *_Ai;


public:
	void draw();
	void configShader(mat4& model, mat4& view, mat4& projection);
	Object_Type getObjectType();

	GLfloat getHealth();
	void changeHealth(GLfloat change);
	IArtificialIntelligence *getAi();

	void loadRealVertices(mat4& model);
	vector <ThreeVertices>* getRealVertices();

	ModelObject(Model *model, IArtificialIntelligence *Ai);
	~ModelObject();
};

