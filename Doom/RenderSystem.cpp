#include "RenderSystem.h"
#include "Constants.h"


using namespace glm;

void RenderSystem::render(vector<Entity*> *entityArray)
{
	mat4 view;
	mat4 model;
	mat4 projection;

	projection = perspective(radians(_currentCamera->Zoom), (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	view = _currentCamera->GetViewMatrix();
	for (vector<Entity *>::iterator iterator = entityArray->begin(); iterator != entityArray->end(); iterator++)
	{

		Entity *entity = *iterator;
		if (entity->getVertexBuffer() != NULL)
		{
		entity->getVertexBuffer()->getShader()->use();


		//zeby sie rowno krecilo we wszystkie strony to rotate(mode,....,vec3(1.0f, 1.0f, 1.0f));
		model = rotate(model, radians(entity->getRotation().x), vec3(1.0f, 0.0f, 0.0f));
		model = rotate(model, radians(entity->getRotation().y), vec3(0.0f, 1.0f, 0.0f));
		model = rotate(model, radians(entity->getRotation().z), vec3(0.0f, 0.0f, 1.0f));

		model = scale(model, vec3(entity->getScale().x, entity->getScale().y, entity->getScale().z));
		view = translate(view, vec3(entity->getPosition().x, entity->getPosition().y, entity->getPosition().z));


			//SKYBOX
			if (entity->getVertexBuffer()->getTextureLoader() != NULL &&
				entity->getVertexBuffer()->getTextureLoader()->getTextureType() == TX_SKYBOX)
			{
				view = glm::mat4(mat3(view));
				glDepthMask(GL_FALSE);
			}
		
		

		//przekazanie do shadera
		GLint modelLoc = (entity->getVertexBuffer()->getShader())->getUniformLocation("model");
		GLint viewLoc = (entity->getVertexBuffer()->getShader())->getUniformLocation("view");
		GLint projLoc = (entity->getVertexBuffer()->getShader())->getUniformLocation("projection");

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, value_ptr(projection));

		

		glUniform4f((entity->getVertexBuffer()->getShader())->get_uColor(),
			entity->getVertexBuffer()->getShaderData()->get_uColorValue().x,
			entity->getVertexBuffer()->getShaderData()->get_uColorValue().y,
			entity->getVertexBuffer()->getShaderData()->get_uColorValue().z,
			entity->getVertexBuffer()->getShaderData()->get_uColorValue().w);

		glUniform3f((entity->getVertexBuffer()->getShader())->get_uLightPosition(),
			entity->getVertexBuffer()->getShaderData()->get_uLightPosition().x,
			entity->getVertexBuffer()->getShaderData()->get_uLightPosition().y,
			entity->getVertexBuffer()->getShaderData()->get_uLightPosition().z);

			
		//entity->getVertexBuffer()->configureVertexAttributes(); // przeniesiono do konstruktora w "VertexBuffer"
		entity->getVertexBuffer()->renderVertexBuffer();	


		//SKYBOX
		if (entity->getVertexBuffer()->getTextureLoader() != NULL &&
			entity->getVertexBuffer()->getTextureLoader()->getTextureType() == TX_SKYBOX)
		{
			glDepthMask(GL_TRUE);
			view = _currentCamera->GetViewMatrix();
		}


		//troche to glupie ale nie mam pomyslu innego
		view = translate(view, vec3(-entity->getPosition().x, -entity->getPosition().y, -entity->getPosition().z));
		model = mat4();
		}
	}
	glfwSwapBuffers(_window);
	glfwPollEvents();
}


RenderSystem::RenderSystem() :_window(glfwGetCurrentContext()), _cameraSystem(&CameraSystem::getCameraSystem())
{
	
}


RenderSystem::~RenderSystem()
{

}

Camera* RenderSystem::getCurrentCamera()
{
	return _currentCamera;
}

void RenderSystem::setCurrentCamera(Camera *newCamera)
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

