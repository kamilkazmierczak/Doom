#include "RenderSystem.h"
#include "Constants.h"
#include "SphereObject.h"
#include "ModelObject.h"
#include "CollisionDetection.h"

using namespace glm;

void RenderSystem::render(vector<Entity*> *entityArray)
{


	mat4 view;
	mat4 model;
	mat4 projection;
	vector <ThreeVertices> *realCurrentVertices = nullptr;
	int distance = 0;
	int test = 0;
	static bool ttmp = false;
	int i = 0;

	projection = perspective(radians(_currentCamera->Zoom), (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (ttmp == false)
	{
		cout << "once" << endl;
	}

	view = _currentCamera->GetViewMatrix();
	for (vector<Entity *>::iterator iterator = entityArray->begin(); iterator != entityArray->end(); iterator++)
	{
		glEnable(GL_DEPTH_TEST); //tego tu nie powinno byc ale jakims cudem sie wylacza samo wiec trzeba wlaczac

		Entity *entity = *iterator;
		distance = std::distance(entityArray->begin(), iterator);


		

		//pobranie rzeczywistych wierzcholkow
		//nie wazne z jakiego typu entity mamy do czynienia
		entity->loadRealVertices();
		//tu moga byc problemy przy 1 iteracji ew. zignoruj wszystko co sie stanie w pierwszej iteracji
		//moga ale nie musza
		realCurrentVertices = entity->getRealVertices();


		
		//if (ttmp ==true)
		//{
		//	if (entity->getType() != ENTITY_BULLET)
		//	{
		//		//cout << i++ << endl;
		//		for (vector<ThreeVertices>::iterator iterator = realCurrentVertices->begin(); iterator != realCurrentVertices->end(); iterator++)
		//		{
		//			//cout << "ok" << endl;
		//			//cout << iterator->a.x << endl;
		//		}
		//	}
		//}
		//
		









		//VertexBuffer
		if (entity->getVertexBuffer() != NULL)
		{
		entity->getVertexBuffer()->getShader()->use();


		//zeby sie rowno krecilo we wszystkie strony to rotate(mode,....,vec3(1.0f, 1.0f, 1.0f));
		model = translate(model, vec3(entity->getPosition().x, entity->getPosition().y, entity->getPosition().z));

		model = rotate(model, radians(entity->getRotation().x), vec3(1.0f, 0.0f, 0.0f));
		model = rotate(model, radians(entity->getRotation().y), vec3(0.0f, 1.0f, 0.0f));
		model = rotate(model, radians(entity->getRotation().z), vec3(0.0f, 0.0f, 1.0f));

		model = scale(model, vec3(entity->getScale().x, entity->getScale().y, entity->getScale().z));
		

		
		//COLLISION DETECTION
		entity->getVertexBuffer()->loadRealVertices(model);
			
		/*if (test ==1)
		{
			static bool tmp = true;
			if (tmp)
			{
				tmp = false;


				realCurrentVertices = entity->getRealVertices();

				for (vector<ThreeVertices>::iterator iterator = realCurrentVertices->begin(); iterator != realCurrentVertices->end(); iterator++)
				{
					cout << "#############NEW ONE##############" << endl;
					cout << iterator->a.x << endl;
					cout << iterator->a.y << endl;
					cout << iterator->a.z << endl;
					cout << "##" << endl;
					cout << iterator->b.x << endl;
					cout << iterator->b.y << endl;
					cout << iterator->b.z << endl;
					cout << "##" << endl;
					cout << iterator->c.x << endl;
					cout << iterator->c.y << endl;
					cout << iterator->c.z << endl;
					cout << "##" << endl;
				}

			}
		}
		test++;*/


		
		//END OF COLLISION DETECTION


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
		
		//NEW
		//entity->getObject()->draw()


		//SKYBOX
		if (entity->getVertexBuffer()->getTextureLoader() != NULL &&
			entity->getVertexBuffer()->getTextureLoader()->getTextureType() == TX_SKYBOX)
		{
			glDepthMask(GL_TRUE);
			view = _currentCamera->GetViewMatrix();
		}


		//troche to glupie ale nie mam pomyslu innego
		//view = translate(view, vec3(-entity->getPosition().x, -entity->getPosition().y, -entity->getPosition().z));
		model = mat4();
		}


		//IObject
		if (entity->getObject() != NULL)
		{

			model = translate(model, vec3(entity->getPosition().x, entity->getPosition().y, entity->getPosition().z));

			model = rotate(model, radians(entity->getRotation().x), vec3(1.0f, 0.0f, 0.0f));
			model = rotate(model, radians(entity->getRotation().y), vec3(0.0f, 1.0f, 0.0f));
			model = rotate(model, radians(entity->getRotation().z), vec3(0.0f, 0.0f, 1.0f));

			model = scale(model, vec3(entity->getScale().x, entity->getScale().y, entity->getScale().z));

			entity->getObject()->configShader(model,view,projection); //uruchamia tez shader->Use()

			//SPHERE
			if (entity->getObject()->getObjectType() == OB_SPHERE)
			{
				SphereObject *sphereObj = nullptr;
				try {sphereObj = dynamic_cast<SphereObject*>(entity->getObject()); }
				catch (bad_cast& bc){cerr << "bad_cast caught: " << bc.what() << endl;}

				//cout << sphereObj->getRadius() << endl;
				
				if (ttmp ==true)
				{
					

					//Sprawdz wszystkie inne Entity
					for (vector<Entity *>::iterator iterator = entityArray->begin(); iterator != entityArray->end(); iterator++)
					{
						if (distance != std::distance(entityArray->begin(), iterator))
						{//Operacje na wszystkich innych Entity
							Entity *otherEntity = *iterator;
							otherEntity->loadRealVertices();

							if (otherEntity->getType() == ENTITY_BULLET)
								continue;

			
							if (otherEntity->getVertexBuffer() != NULL &&
								otherEntity->getVertexBuffer()->getTextureLoader() != NULL &&
								otherEntity->getVertexBuffer()->getTextureLoader()->getTextureType() == TX_SKYBOX)
								continue;

							if (otherEntity->getRealVertices() == nullptr)
								cout << "Cos jest nie tak #1" << endl;

							//zabawa z reszta swiata
		

								//transformacja srodka sfery na rzeczywiste wspolrzedne
								/*vec4 sphereCentreTransform = model* vec4(entity->getPosition().x,
																		 entity->getPosition().y,
																		 entity->getPosition().z,
																		 1.0f);*/


																	 //kazda sfera ma swoj poczatek w 0,0,0
																	 //logiczne -> trojkat tez ma podane blisko 0
							vec4 sphereCentreTransform = model* vec4(vec3(0.0f), 1.0f);

						 
							vec3 sphereCentreReal = vec3(sphereCentreTransform) / sphereCentreTransform.w;

					/*		cout << "####REAL" << endl;
							cout << sphereCentreReal.x << endl;
							cout << sphereCentreReal.y << endl;
							cout << sphereCentreReal.z << endl;*/
						/*	cout << "####NORMAL" << endl;
							cout << entity->getPosition().x << endl;
							cout << entity->getPosition().y << endl;
							cout << entity->getPosition().z << endl;
							*/

							//cout << "NEXT######################################" << endl;
				
							realCurrentVertices = otherEntity->getRealVertices();
							//int nrOfTriangles = realCurrentVertices->size();
							int i = 0;
							for (vector<ThreeVertices>::iterator iterator = realCurrentVertices->begin(); iterator != realCurrentVertices->end(); iterator++)
							{
								vec3 *real[3];
								//przelec po wszystkich trojkatach danego obiektu
								for (int k = 0; k < realCurrentVertices->size(); k++)
								{
									real[0] = &realCurrentVertices->at(k).a;
									real[1] = &realCurrentVertices->at(k).b;
									real[2] = &realCurrentVertices->at(k).c;

									/*cout << "Triangle" << endl;
									cout << real[0]->x << " " << real[0]->y << " " << real[0]->z << endl;
									cout << real[1]->x << " " << real[1]->y << " " << real[1]->z << endl;
									cout << real[2]->x << " " << real[2]->y << " " << real[2]->z << endl;*/


									bool bCollided = SpherePolygonCollision(*real, sphereCentreReal, 3, sphereObj->getRadius());
									if (bCollided)
										cout << "kolizja" << endl;
								}
								
								




								//cout << "first" << endl;
								//cout << "#####" << endl;
								//cout << i++ << endl;
								//cout << "vertices" << endl;
								//cout << "#####" << endl;
							}



						}
					}


				}
	




			}//koniec zabawy ze sfera


			//MODEL (nie testowane)
			if (entity->getObject()->getObjectType() == OB_MODEL)
			{
				ModelObject *modelObj = nullptr;
				try {modelObj = dynamic_cast<ModelObject*>(entity->getObject()); }
				catch (bad_cast& bc){ cerr << "bad_cast caught: " << bc.what() << endl;}

				modelObj->loadRealVertices(model);	
			}


			entity->getObject()->draw();
			//chyba
			model = mat4(); 
		}




	}
	glfwSwapBuffers(_window);
	glfwPollEvents();
	ttmp = true;
	i = 0;
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

