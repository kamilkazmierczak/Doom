#include "ModelObject.h"
#include "ResourceManager.h"
#include "CameraSystem.h"
#include <glm/gtx/string_cast.hpp>


ModelObject::ModelObject(Model *model) : _model(model), _health(100.0f)
{
	_typeOfObject = OB_MODEL;
	_shader = new ShaderInterface("model_loading.vs", "model_loading.frag");

}


ModelObject::~ModelObject()
{
}


vector <ThreeVertices>* ModelObject::getRealVertices()
{
	return _myRealVertices;
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

	ResourceManager *resourceManager = &ResourceManager::getResourceManager();
	CameraSystem *cameraSystem = &CameraSystem::getCameraSystem();

	Camera *currentCamera = cameraSystem->getCurrentCamera();	

	//pod 5 jest vertexBuffer lampy a w jej ShaderData jest pozycja swiatla
	Vector3 lamp1Position = resourceManager->getVertexBufferArray()->at(5)->getShaderData()->get_uLightPosition();
	//vec3 lamp1Position = vec3(lamp1Position_.x, lamp1Position_.y, lamp1Position_.z);

	//TEMPORARY
	Vector3 lamp2Position = lamp1Position;

	//cout << glm::to_string(lamp1Position) << endl;

	// Set the lighting uniforms
	glUniform3f(_shader->getUniformLocation("viewPos"), currentCamera->Position.x, currentCamera->Position.y, currentCamera->Position.z);
	
	// Point light 1
	glUniform3f(_shader->getUniformLocation("pointLights[0].position"), lamp1Position.x, lamp1Position.y, lamp1Position.z);
	glUniform3f(_shader->getUniformLocation("pointLights[0].ambient"), 0.05f, 0.05f, 0.05f);
	glUniform3f(_shader->getUniformLocation("pointLights[0].diffuse"), 1.0f, 1.0f, 1.0f);
	glUniform3f(_shader->getUniformLocation("pointLights[0].specular"), 1.0f, 1.0f, 1.0f);
	glUniform1f(_shader->getUniformLocation("pointLights[0].constant"), 1.0f);
	glUniform1f(_shader->getUniformLocation("pointLights[0].linear"), 0.009);
	glUniform1f(_shader->getUniformLocation("pointLights[0].quadratic"), 0.0032);
	// Point light 2
	glUniform3f(_shader->getUniformLocation("pointLights[1].position"), lamp2Position.x, lamp2Position.y, lamp2Position.z);
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

Object_Type ModelObject::getObjectType()
{
	return _typeOfObject;
}


void ModelObject::loadRealVertices(mat4& model)
{
	_model->loadRealVertices(model);
	_myRealVertices = _model->getRealVertices();
}

GLfloat ModelObject::getHealth()
{
	return _health;
}

void ModelObject::changeHealth(GLfloat change)
{
	_health += change; //mozesz dodawac i odejmowac
}