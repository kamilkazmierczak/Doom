#include "ShaderData.h"




ShaderData::ShaderData(vector<Light>*light,Material material, Vector4 newColor) :_uLightArray(light), _uMaterial(material), _uColorValue(newColor)
{
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

Material ShaderData::get_uMaterial()
{
	return _uMaterial;
}

void ShaderData::set_uMaterial(Material newMaterial)
{
	_uMaterial = newMaterial;
}


void ShaderData::set_uColorValue(Vector4 newColor)
{
	_uColorValue = newColor;
}

Vector4 ShaderData::get_uColorValue()
{
	return _uColorValue;
}