#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include "Vector3.h"
#include "Vector4.h"
#include <vector>

using namespace std;

struct Light {
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};

struct Material {
	glm::vec3 specular;
	float shininess;
};

class ShaderData
{
private:
	Vector4 _uColorValue;
	Vector3 _uLightPosition;
	Vector3 _uLightPosition2;
	vector<Light> *_uLightArray; 
	vector<Material> *_uMaterialArray;

public:
	ShaderData(vector<Light>* light, vector<Material>* material, Vector4 newColor, Vector3 newPosition, Vector3 newPosition2);
	~ShaderData();

	Vector4 get_uColorValue();
	void set_uColorValue(Vector4 newColor);

	vector<Light> *get_uLightArray();
	void set_uLightArray(vector<Light>* newLights);

	vector <Material> *get_uMaterialArray();
	void set_uMaterialArray(vector <Material>* newMaterials);

	Vector3 get_uLightPosition();
	void set_uLightPosition(Vector3 newLight);

	Vector3 get_uLightPosition2();
	void set_uLightPosition2(Vector3 newLight);

};

