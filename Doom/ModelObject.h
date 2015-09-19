#pragma once
#include "IObject.h"
#include "Model.h"


class ModelObject : public IObject
{
private:
	Model *_model;
	ShaderInterface *_shader; //na razie stala (tworzona w konstruktorze)
	vector <ThreeVertices> *_myRealVertices;
	GLfloat _health; //tego tu nie powinno byc - powinna byc klasa Enemy (ze wzgledu na czas na razie to tu zostanie)
public:
	void draw();
	void configShader(mat4& model, mat4& view, mat4& projection);
	Object_Type getObjectType();


	//to samo co zmienna _health - tego tu byc nie powinno (potem to zmien i zrob nowa klase)
	GLfloat getHealth();
	void changeHealth(GLfloat change);



	//tylko model
	void loadRealVertices(mat4& model);
	vector <ThreeVertices>* getRealVertices();

	ModelObject(Model *model);
	~ModelObject();
};

