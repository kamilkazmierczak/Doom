#pragma once
#include "IObject.h"
#include "Model.h"
#include "IArtificialIntelligence.h"

class ModelObject : public IObject
{
private:
	Model *_model;
	ShaderInterface *_shader; //na razie stala (tworzona w konstruktorze)
	vector <ThreeVertices> *_myRealVertices;
	//to powinno byc w klasie Enemy - jak bd czas taka zrob
	GLfloat _health; //tego tu nie powinno byc - powinna byc klasa Enemy (ze wzgledu na czas na razie to tu zostanie)
	IArtificialIntelligence *_Ai;


public:
	void draw();
	void configShader(mat4& model, mat4& view, mat4& projection);
	Object_Type getObjectType();


	//to samo co zmienna _health - tego tu byc nie powinno (potem to zmien i zrob nowa klase)
	GLfloat getHealth();
	void changeHealth(GLfloat change);
	IArtificialIntelligence *getAi();


	//tylko model
	void loadRealVertices(mat4& model);
	vector <ThreeVertices>* getRealVertices();

	ModelObject(Model *model, IArtificialIntelligence *Ai);
	~ModelObject();
};

