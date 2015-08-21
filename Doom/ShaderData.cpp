#include "ShaderData.h"




ShaderData::ShaderData(Vector4 newColor, Vector3 newPosition) :_uColorValue(newColor), _uLightPosition(newPosition)
{
}


ShaderData::~ShaderData()
{
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

