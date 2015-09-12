#include "ModelObject.h"


ModelObject::ModelObject(Model *model) : _model(model)
{
	_typeOfObject = OB_SPHERE;
	_shader = new ShaderInterface("model_loading.vs", "model_loading.frag");

}


ModelObject::~ModelObject()
{
}


void ModelObject::draw()
{
	_model->Draw(_shader->getShader(), _gameModel, _gameView, _gameProjection);
}

void ModelObject::configShader(mat4& model, mat4& view, mat4& projection)
{
	_gameModel = model;
	_gameView = view;
	_gameProjection = projection;

	_shader->use();

	//BARDZO TMP
	// Positions of the point lights
	glm::vec3 pointLightPositions[] = {
		glm::vec3(0.7f, 0.2f, 2.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f, 2.0f, -12.0f),
		glm::vec3(0.0f, 0.0f, -3.0f)
	};


	// Set the lighting uniforms
	//glUniform3f(glGetUniformLocation(shader->Program, "viewPos"), camera.Position.x, camera.Position.y, camera.Position.z);
	// Point light 1
	//glUniform3f(glGetUniformLocation(_shader->Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);

	
	glUniform3f(_shader->getUniformLocation("pointLights[0].ambient"), 0.05f, 0.05f, 0.05f);
	glUniform3f(_shader->getUniformLocation("pointLights[0].diffuse"), 1.0f, 1.0f, 1.0f);
	glUniform3f(_shader->getUniformLocation("pointLights[0].specular"), 1.0f, 1.0f, 1.0f);
	glUniform1f(_shader->getUniformLocation("pointLights[0].constant"), 1.0f);
	glUniform1f(_shader->getUniformLocation("pointLights[0].linear"), 0.009);
	glUniform1f(_shader->getUniformLocation("pointLights[0].quadratic"), 0.0032);
	// Point light 2
	//glUniform3f(_shader->getUniformLocation("pointLights[1].position"), pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
	glUniform3f(_shader->getUniformLocation("pointLights[1].ambient"), 0.05f, 0.05f, 0.05f);
	glUniform3f(_shader->getUniformLocation("pointLights[1].diffuse"), 1.0f, 1.0f, 1.0f);
	glUniform3f(_shader->getUniformLocation("pointLights[1].specular"), 1.0f, 1.0f, 1.0f);
	glUniform1f(_shader->getUniformLocation("pointLights[1].constant"), 1.0f);
	glUniform1f(_shader->getUniformLocation("pointLights[1].linear"), 0.009);
	glUniform1f(_shader->getUniformLocation("pointLights[1].quadratic"), 0.0032);


	//przekazanie do shadera
	GLint modelLoc = _shader->getUniformLocation("model");
	GLint viewLoc = _shader->getUniformLocation("view");
	GLint projLoc = _shader->getUniformLocation("projection");

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(_gameModel));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(_gameView));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, value_ptr(_gameProjection));

}