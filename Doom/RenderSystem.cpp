#include "RenderSystem.h"
#include "Constants.h"
#include "SphereObject.h"
#include "ModelObject.h"
#include "CollisionDetection.h"
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/string_cast.hpp>
using namespace glm;

void RenderSystem::render(vector<Entity*> *entityArray)
{
	mat4 view;
	mat4 model;
	mat4 projection;
	vector <ThreeVertices> *realCurrentVertices = nullptr;
	int distance = 0;
	int test = 0;
	int i = 0;

	projection = perspective(radians(_cameraSystem->getCurrentCamera()->Zoom), (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//wywal _currentCamera i uzywaj _cameraSystem;
	//_cameraSystem->getCurrentCamera()->getCenter();
	view = _cameraSystem->getCurrentCamera()->GetViewMatrix();
	//_currentCamera->GetViewMatrix();

	//
	for (vector<Entity *>::iterator iterator = entityArray->begin(); iterator != entityArray->end(); iterator++)
	{
		glEnable(GL_DEPTH_TEST); //tego tu nie powinno byc ale jakims cudem sie wylacza samo wiec trzeba wlaczac
		Entity *entity = *iterator;
		distance = std::distance(entityArray->begin(), iterator);
		entity->loadRealVertices(); //to pobiera efet dzialania funkji loadRealVertices(model) (dla obiektow)

		//nie jestem pewien czy te podstawienie tu powinno byc
		//w obiektach pod ten wskaznik podstawiam aktualne realne ale innych obiektow
		realCurrentVertices = entity->getRealVertices(); 


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

		entity->getVertexBuffer()->loadRealVertices(model);

		
		//COLLISION DETECTION
		//vec3 u = vec3(0.0f, 0.0f, 1.0f);
		//vec3 u2 = vec3(1.0f, 0.0f, 1.0f);
		////double angle = AngleBetweenVectors(v1, v2);
		//vec3 v =/* u +*/ u2;
	
		//GLfloat angle = glm::orientedAngle(normalize(v1), normalize(newv), vec3(0.0f, 0.0f, 0.0f));
		//GLfloat angle =glm::orientedAngle(normalize(vec2(newv.x, newv.z)), normalize(vec2(v1.x, v1.z)));
		/*GLfloat angle;
		cout << "GLM" << endl;
		angle = glm::orientedAngle(normalize(vec2(u.x, u.z)), normalize(vec2(v.x, v.z)));
		cout << angle << endl;
		cout << "atan2" << endl;
		angle = atan2(v.z, v.x) - atan2(u.z, u.x);
		cout << angle << endl;

		cout << "##" << endl;*/
	/*	cout << newv.x << endl;
		cout << newv.y << endl;
		cout << newv.z << endl;*/

	
		

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

			
		entity->getVertexBuffer()->renderVertexBuffer();	
		
		//SKYBOX
		if (entity->getVertexBuffer()->getTextureLoader() != NULL &&
			entity->getVertexBuffer()->getTextureLoader()->getTextureType() == TX_SKYBOX)
		{
			glDepthMask(GL_TRUE);
			view = _cameraSystem->getCurrentCamera()->GetViewMatrix();
		}

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
		

				//DETEKCJA KOLIZJI
				if (_firstRender != true)
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

							vec4 sphereCentreTransform = model* vec4(vec3(0.0f), 1.0f);
							vec3 sphereCentreReal = vec3(sphereCentreTransform) / sphereCentreTransform.w;
							realCurrentVertices = otherEntity->getRealVertices();

							//zabawa z reszta swiata
							for (vector<ThreeVertices>::iterator iterator = realCurrentVertices->begin(); iterator != realCurrentVertices->end(); iterator++)
							{
								vec3 *real[3];
								//przelec po wszystkich trojkatach danego obiektu
								for (int k = 0; k < realCurrentVertices->size(); k++)
								{
									real[0] = &realCurrentVertices->at(k).a;
									real[1] = &realCurrentVertices->at(k).b;
									real[2] = &realCurrentVertices->at(k).c;

									bool bCollided = SpherePolygonCollision(*real, sphereCentreReal, 3, sphereObj->getRadius());
									if (bCollided)
									{
										//cout << "kolizja sfery" << endl;

										if (otherEntity->getType() == ENTITY_MAP)
										{
											//cout << "udzerzyles w mape" << endl;
											//cout << "end" << endl;
										}

										if (otherEntity->getType() == ENTITY_ENEMY)
										{
											//cout << "udzerzyles we wroga" << endl;
											ModelObject *enemyObj = nullptr;
											try { enemyObj = dynamic_cast<ModelObject*>(otherEntity->getObject()); }
											catch (bad_cast& bc){ cerr << "bad_cast caught: " << bc.what() << endl; }

											cout << enemyObj->getHealth() << endl;
											cout << "koniec umierania" << endl;
											if (enemyObj->getHealth() > 0.0f)
											{
												enemyObj->changeHealth(-100.0f);
											}
											
											



										}

		

									}
								}	
								
							}
						}
					}
					//cout << "koniec kolizji ze sfera" << endl;
				}
			}//koniec zabawy ze sfera


			//MODEL (nie testowane)
			if (entity->getObject()->getObjectType() == OB_MODEL)
			{
				ModelObject *modelObj = nullptr;
				try {modelObj = dynamic_cast<ModelObject*>(entity->getObject()); }
				catch (bad_cast& bc){ cerr << "bad_cast caught: " << bc.what() << endl;}

				modelObj->loadRealVertices(model);	

				//ARTIFICIAL INTELLIGENCE

				if (entity->getType() == ENTITY_ENEMY)
				{
					_Ai->moveToCamera(entity, DalekSpeed);

					////ZACHOWANIE W PRZYPADKU UDZERZENIA W MAPE



				}
		
				//#ARTIFICIAL INTELLIGENCE



				//DETEKCJA KOLIZJI
				if (_firstRender != true)
				{
					//detekcja

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
								cout << "Cos jest nie tak #2" << endl;

							realCurrentVertices = otherEntity->getRealVertices();

											//po wszystkich moich trojkatach
							for (int l = 0; l < entity->getRealVertices()->size(); l++)
							{
								vec3 *myReal[3];
								myReal[0] = &entity->getRealVertices()->at(l).a;
								myReal[1] = &entity->getRealVertices()->at(l).b;
								myReal[2] = &entity->getRealVertices()->at(l).c;

								//zabawa z reszta swiata
								for (vector<ThreeVertices>::iterator iterator = realCurrentVertices->begin(); iterator != realCurrentVertices->end(); iterator++)
								{
									//przelec po wszystkich trojkatach danego obiektu
									vec3 *real[3];
									for (int k = 0; k < realCurrentVertices->size(); k++)
									{
										real[0] = &realCurrentVertices->at(k).a;
										real[1] = &realCurrentVertices->at(k).b;
										real[2] = &realCurrentVertices->at(k).c;

										//ze wzgledu na ulomnosc funkcji IntersectedPolygon
										//trzeba jej przekazac wspolrzedne lini
										//wiec dla trojkata beda to 3 linie
										vec3 *realLine[2];
										for (int t = 0; t < 3; t++)
										{
											realLine[0] = real[(t + 1) % 3];
											realLine[1] = real[(t + 2) % 3];


											vec3 _myReal[3];
											vec3 _realLine[2];

											_myReal[0] = *myReal[0];
											_myReal[1] = *myReal[1];
											_myReal[2] = *myReal[2];

											_realLine[0] = *realLine[0];
											_realLine[1] = *realLine[1];


											//tu sie dzieje cos dziwnego, ale mozesz przekazac
											///myReal bez kopiowanie bez sensu, ale NIE MOZESZ
											//przekazac *realLine bo jakies cuda sie dzieja
											//i wykrywa kolizje gdy jej nie ma

											bool bCollided = IntersectedPolygon(_myReal, _realLine, 3);
											//bool bCollided = IntersectedPolygon(*myReal,*realLine, 3);
											if (bCollided)
											{
												//cout << "kolizja modelu" << endl;
												_Ai->moveWhenCollision(entity, DalekSpeed);



											}
											
	

										}
									}
								}
							}
							//cout << "koniec kolizji z modele" << endl;
						}
					}





				}



			}


			entity->getObject()->draw();
			//chyba
			model = mat4(); 
		}





	}
	glfwSwapBuffers(_window);
	_firstRender = false;
	if (_firstRender != true)
	{
		update(entityArray); //usun obiekty
		checkForNewObjects(entityArray);
	}

	glfwPollEvents();
	i = 0;
}




void RenderSystem::checkForNewObjects(vector<Entity *> *entityArray)
{
	for (vector<Entity *>::iterator iterator = _newObjects->begin(); iterator != _newObjects->end(); iterator++)
	{
		entityArray->push_back(*iterator);
		_firstRender = true;
	}

	if (_newObjects->size() != 0)
	{
		_newObjects->clear();
	}
}




void RenderSystem::update(vector<Entity *> *entityArray)
{
	//DESTRUKCJE
	for (vector<Entity *>::iterator iterator = entityArray->begin(); iterator != entityArray->end();/**/)
	{
		Entity *entity = *iterator;

		//DESTRUKCJE
		bool destroy = false;
		if (entity->getType() == ENTITY_ENEMY)
		{

			//nie istnieje koniecznosc by to sprawdzac (enemy jest modelem i jest OB_MODEL)
			//if (entity->getObject() != NULL)
			//if (entity->getObject()->getObjectType() == OB_MODEL)

			ModelObject *enemyObj = nullptr;
			try { enemyObj = dynamic_cast<ModelObject*>(entity->getObject()); }
			catch (bad_cast& bc){ cerr << "bad_cast caught: " << bc.what() << endl; }

			if (enemyObj->getHealth() <= 0.0f)
			{
				cout << "ktos tu umarl" << endl;
				destroy = true;
			}

		}
		if (destroy)
		{
			delete entity;
			iterator = entityArray->erase(iterator);
		}
		else
		{
			++iterator;
		}

	}		
}




RenderSystem::RenderSystem() :_window(glfwGetCurrentContext()), _cameraSystem(&CameraSystem::getCameraSystem()),_Ai(&ArtificialIntelligence::getArtificialIntelligence()), _firstRender(true)
{
	_newObjects = new vector<Entity *>();
}


RenderSystem::~RenderSystem()
{

}

//Camera* RenderSystem::getCurrentCamera()
//{
//	return _currentCamera;
//}
//
//void RenderSystem::setCurrentCamera(Camera *newCamera)
//{
//	_currentCamera = newCamera;
//}


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

vector<Entity *>* RenderSystem::getNewObjects()
{
	return _newObjects;
}