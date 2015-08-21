#include "RenderSystem.h"
#include "Constants.h"

using namespace glm;

void RenderSystem::render(VertexBuffer *vertexBuffer)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//shaderArray->at(0)->//tu zrob metode RUN co odpali USE
	//glUseProgram(0); //WTF
	//_resourceManager->getVertexBufferArray())->at(0)
	//ResourceManager::getShaderArray();

	//_shaderArray->at(0)->use();

	/*ZAKAZANE ZAKAZANE ZAKAZANE
	glLoadIdentity();
	
	gluLookAt(3.0f, 2.0f, -2.0f, 
			  0.0f, 0.0f, 0.0f, 
			  0.0f, 1.0f, 0.0f);
	*/		  
	
	//TU TEZ NIE POWINNO BYC ZERO (1arg)
	//TYLKO //glGetUniformLocation(lightingShader.Program, "dirLight.direction")

	(vertexBuffer->getShader())->use();

	//Transformacje
	mat4 model;
	mat4 view;
	mat4 projection;				 //wzgledem osi x
	model = rotate(model, -20.0f, vec3(1.0f, 0.0f, 0.0f));
	view = translate(view, vec3(0.0f, 0.0f, -3.0f));
	projection = perspective(radians(45.0f), (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
	//przekazanie do shadera
	GLint modelLoc = (vertexBuffer->getShader())->getUniformLocation("model");
	GLint viewLoc = (vertexBuffer->getShader())->getUniformLocation("view");
	GLint projLoc = (vertexBuffer->getShader())->getUniformLocation("projection");
	
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, value_ptr(projection));


	GLint uColorlocation = (vertexBuffer->getShader())->getUniformLocation("uColor");
	glUniform4f(uColorlocation, 1.0f, 0.0f, 0.0f, 1.0f);
	vertexBuffer->configureVertexAttributes();
	vertexBuffer->renderVertexBuffer();

	//glDrawArrays(GL_TRIANGLES, 0, 3);

	

	glfwSwapBuffers(_window);
	glfwPollEvents();
}


RenderSystem::RenderSystem() :_window(glfwGetCurrentContext())
{

}


RenderSystem::~RenderSystem()
{

}


RenderSystem& RenderSystem::getRenderSystem()
{
	static RenderSystem *renderSystem = NULL;

	if (renderSystem == NULL){
		renderSystem = new RenderSystem();
		
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

		/*CHYBA ZAKAZANE ZAKAZANE ZAKAZANE
		glMatrixMode(GL_PROJECTION);
		gluPerspective(75.0f, 800.0f / 600.0f, 1, 1000); //to bylo w tutorialu ale inna funkcja
		glViewport(0.0f, 0.0f, 800.0, 600.0f);
		glMatrixMode(GL_MODELVIEW);
		*/
	}

	return *renderSystem;
}

void RenderSystem::destroyRenderSystem()
{
	RenderSystem *renderSystem = &getRenderSystem();
	delete renderSystem;
}

