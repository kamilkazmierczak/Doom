#pragma once
#include "IObject.h"
#include "Model.h"

class ModelObject : public IObject
{
private:
	Model *_model;
	ShaderInterface *_shader; //na razie stala (tworzona w konstruktorze)

public:
	void draw();
	void configShader(mat4& model, mat4& view, mat4& projection);

	ModelObject(Model *model);
	~ModelObject();
};

