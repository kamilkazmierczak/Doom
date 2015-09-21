#include "ShaderData.h"




ShaderData::ShaderData(vector<Light>*light,vector <Material>*material, Vector4 newColor, Vector3 newPosition, Vector3 newPosition2) :_uLightArray(light), _uMaterialArray(material), _uColorValue(newColor), _uLightPosition(newPosition), _uLightPosition2(newPosition2)
{
	//vector<Light> *_uLightArray;
	//vector<Material> *_uMaterialArray

		//_uLightArray = new vector<Light>();
		//_uMaterialArray = new vector<Material>();
}


ShaderData::~ShaderData()
{
}


vector<Light>* ShaderData::get_uLightArray()
{
	return _uLightArray;
}

void ShaderData::set_uLightArray(vector<Light>* newLights)
{
	_uLightArray = newLights;
}

vector<Material>* ShaderData::get_uMaterialArray()
{
	return _uMaterialArray;
}

void ShaderData::set_uMaterialArray(vector<Material>* newMaterials)
{
	_uMaterialArray = newMaterials;
}


void ShaderData::set_uColorValue(Vector4 newColor)
{
	_uColorValue = newColor;
}

Vector4 ShaderData::get_uColorValue()
{
	return _uColorValue;
}

void ShaderData::set_uLightPosition(Vector3 newLight)
{
	_uLightPosition = newLight;
}


Vector3 ShaderData::get_uLightPosition()
{
	return _uLightPosition;
}


void ShaderData::set_uLightPosition2(Vector3 newLight)
{
	_uLightPosition2 = newLight;
}


Vector3 ShaderData::get_uLightPosition2()
{
	return _uLightPosition2;
}
