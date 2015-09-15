#pragma once
#include "IObject.h"
#include "Model.h"


class ModelObject : public IObject
{
private:
	Model *_model;
	ShaderInterface *_shader; //na razie stala (tworzona w konstruktorze)
	vector <ThreeVertices> *_myRealVertices;

public:
	void draw();
	void configShader(mat4& model, mat4& view, mat4& projection);
	Object_Type getObjectType();


	//tylko model
	void loadRealVertices(mat4& model);
	vector <ThreeVertices>* getRealVertices();

	ModelObject(Model *model);
	~ModelObject();
};

