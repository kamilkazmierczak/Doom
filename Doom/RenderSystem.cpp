#include "RenderSystem.h"
#include "Constants.h"

using namespace glm;

void RenderSystem::render(vector<Entity*> *entityArray)
{

	for (vector<Entity *>::iterator iterator = entityArray->begin(); iterator != entityArray->end(); iterator++)
	{

		Entity *entity = *iterator;
		if (entity->getVertexBuffer() != NULL)
		{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		entity->getVertexBuffer()->getShader()->use();

		//Transformacje
		mat4 model;
		mat4 view;
		mat4 projection;

		//zeby sie rowno krecilo we wszystkie strony to rotate(mode,....,vec3(1.0f, 1.0f, 1.0f));
		model = rotate(model, radians(entity->getRotation().x), vec3(1.0f, 0.0f, 0.0f));
		model = rotate(model, radians(entity->getRotation().y), vec3(0.0f, 1.0f, 0.0f));
		model = rotate(model, radians(entity->getRotation().z), vec3(0.0f, 0.0f, 1.0f));

		model = scale(model, vec3(entity->getScale().x, entity->getScale().y, entity->getScale().z));
		view = translate(view, vec3(entity->getPosition().x, entity->getPosition().y, entity->getPosition().z));
		//temporary
		
		view = lookAt(vec3(_currentCamera->getPosition().x, _currentCamera->getPosition().y, _currentCamera->getPosition().z),
			vec3(_currentCamera->getEyeVector().x, _currentCamera->getEyeVector().y, _currentCamera->getEyeVector().z),
			vec3(_currentCamera->getUpVector().x, _currentCamera->getUpVector().y, _currentCamera->getUpVector().z));
			
		/*
		view = lookAt(vec3(1.0f, 1.0f, 2.0f),
		vec3(0.0f, 0.0f, 0.0f),
		vec3(0.0f, 1.0f, 0.0f));
		*/

		projection = perspective(radians(45.0f), (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);


		//przekazanie do shadera
		GLint modelLoc = (entity->getVertexBuffer()->getShader())->getUniformLocation("model");
		GLint viewLoc = (entity->getVertexBuffer()->getShader())->getUniformLocation("view");
		GLint projLoc = (entity->getVertexBuffer()->getShader())->getUniformLocation("projection");

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, value_ptr(projection));

		//ZMIEN TO NA
		// uColorlocation = (vertexBuffer->getShader())->get_uColor;
		//ale wtedy nie zwraca -1 gdy nie istnieje
		/*
		GLint uColorlocation = (vertexBuffer->getShader())->getUniformLocation("uColor");
		if (uColorlocation != -1){
		glUniform4f(uColorlocation, 1.0f, 0.0f, 0.0f, 1.0f);
		}
		*/

		glUniform4f((entity->getVertexBuffer()->getShader())->get_uColor(),
			entity->getVertexBuffer()->getShaderData()->get_uColorValue().x,
			entity->getVertexBuffer()->getShaderData()->get_uColorValue().y,
			entity->getVertexBuffer()->getShaderData()->get_uColorValue().z,
			entity->getVertexBuffer()->getShaderData()->get_uColorValue().w);

		glUniform3f((entity->getVertexBuffer()->getShader())->get_uLightPosition(),
			entity->getVertexBuffer()->getShaderData()->get_uLightPosition().x,
			entity->getVertexBuffer()->getShaderData()->get_uLightPosition().y,
			entity->getVertexBuffer()->getShaderData()->get_uLightPosition().z);

		//vertexBuffer->configureVertexAttributes();  przeniesiono do konstruktora w "VertexBuffer"
		entity->getVertexBuffer()->renderVertexBuffer();

		//glDrawArrays(GL_TRIANGLES, 0, 3);



		glfwSwapBuffers(_window);
		glfwPollEvents();
		}
	}
}


RenderSystem::RenderSystem() :_window(glfwGetCurrentContext()), _cameraSystem(&CameraSystem::getCameraSystem())
{
	
}


RenderSystem::~RenderSystem()
{

}

Entity* RenderSystem::getCurrentCamera()
{
	return _currentCamera;
}

void RenderSystem::setCurrentCamera(Entity *newCamera)
{
	_currentCamera = newCamera;
}


RenderSystem& RenderSystem::getRenderSystem()
{
	static RenderSystem *renderSystem = NULL;

	if (renderSystem == NULL){
		renderSystem = new RenderSystem();
		
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glEnable(GL_DEPTH_TEST);
	}

	return *renderSystem;
}

void RenderSystem::destroyRenderSystem()
{
	RenderSystem *renderSystem = &getRenderSystem();
	delete renderSystem;
}

