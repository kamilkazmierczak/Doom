#include "RenderSystem.h"


void RenderSystem::render(VertexBuffer *vertexBuffer)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//shaderArray->at(0)->//tu zrob metode RUN co odpali USE
	//glUseProgram(0); //WTF
	
	shaderArray->at(0)->use();

	/*ZAKAZANE ZAKAZANE ZAKAZANE
	glLoadIdentity();
	
	gluLookAt(0.0f, 0.0f, -5.0f, 
			  0.0f, 0.0f, 0.0f, 
			  0.0f, 1.0f, 0.0f);
	*/		  
	
	//TU TEZ NIE POWINNO BYC ZERO (1arg)
	//TYLKO //glGetUniformLocation(lightingShader.Program, "dirLight.direction")

	GLint uniformlocation = shaderArray->at(0)->getUniformLocation("uColor");
	glUniform4f(uniformlocation, 1.0f, 0.0f, 0.0f, 1.0f);

	vertexBuffer->configureVertexAttributes(0);//vertexposition (layout =0 ) chyba tam sie VAO ustawia (ale bez bind!!?)

	vertexBuffer->renderVertexBuffer();

	//glDrawArrays(GL_TRIANGLES, 0, 3);

	

	glfwSwapBuffers(_window);
	glfwPollEvents();
}


RenderSystem::RenderSystem() :_window(glfwGetCurrentContext())
{
	shaderArray = new vector < ShaderInterface *>;
	ShaderInterface *shader = new ShaderInterface("ColorShader.vs", "ColorShader.frag");
	shaderArray->push_back(shader);
}


RenderSystem::~RenderSystem()
{
	//delete shaderArray->at(0);
	//delete shaderArray;
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

