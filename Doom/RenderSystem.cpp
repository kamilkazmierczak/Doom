#include "RenderSystem.h"
#include "Constants.h"
#include "BulletObject.h"
#include "ModelObject.h"
#include "CollisionDetection.h"
#include "Player.h"
#include "EnvironmentReactions.h"
#include "TextRender.h"
#include "GameManager.h"
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

	GLuint WIDTH = GameManager::_Width;
	GLuint HEIGHT = GameManager::_Height;

	projection = perspective(radians(_cameraSystem->getCurrentCamera()->Zoom), (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	view = _cameraSystem->getCurrentCamera()->GetViewMatrix();
	

	
	for (vector<Entity *>::iterator iterator = entityArray->begin(); iterator != entityArray->end(); iterator++)
	{
		glEnable(GL_DEPTH_TEST); //tego tu nie powinno byc ale jakims cudem sie wylacza samo wiec trzeba wlaczac
		
		Entity *entity = *iterator;
		distance = std::distance(entityArray->begin(), iterator);
		entity->loadRealVertices(); //to pobiera efet dzialania funkji loadRealVertices(model) (dla obiektow)

		realCurrentVertices = entity->getRealVertices(); 
		
		if (_firstRender != true)
		{
			if (entity->getType() != ENTITY_GUN)
			{
				_cameraSystem->reactOnMap(entity);
			}
			else
			{
				//setGunPosition(entity);
			}

			EnvironmentReactions *environment = &EnvironmentReactions::getEnvironmentReactions();
			environment->react();
		}	


		//VertexBuffer
		if (entity->getVertexBuffer() != NULL)
		{
		entity->getVertexBuffer()->getShader()->use();

		model = translate(model, vec3(entity->getPosition().x, entity->getPosition().y, entity->getPosition().z));
		model = rotate(model, radians(entity->getRotation().x), vec3(1.0f, 0.0f, 0.0f));
		model = rotate(model, radians(entity->getRotation().y), vec3(0.0f, 1.0f, 0.0f));
		model = rotate(model, radians(entity->getRotation().z), vec3(0.0f, 0.0f, 1.0f));
		model = scale(model, vec3(entity->getScale().x, entity->getScale().y, entity->getScale().z));

		entity->getVertexBuffer()->loadRealVertices(model);


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


		glUniform3f((entity->getVertexBuffer()->getShader())->getUniformLocation("uViewPosition"),
			_cameraSystem->getCurrentCamera()->getPosition().x,
			_cameraSystem->getCurrentCamera()->getPosition().y,
			_cameraSystem->getCurrentCamera()->getPosition().z);

		//light1
			glUniform3f((entity->getVertexBuffer()->getShader())->getUniformLocation("light[0].position"),
				entity->getVertexBuffer()->getShaderData()->get_uLightArray()->at(0).position.x,
				entity->getVertexBuffer()->getShaderData()->get_uLightArray()->at(0).position.y,
				entity->getVertexBuffer()->getShaderData()->get_uLightArray()->at(0).position.z);


			glUniform3f((entity->getVertexBuffer()->getShader())->getUniformLocation("light[0].ambient"),
				entity->getVertexBuffer()->getShaderData()->get_uLightArray()->at(0).ambient.x,
				entity->getVertexBuffer()->getShaderData()->get_uLightArray()->at(0).ambient.y,
				entity->getVertexBuffer()->getShaderData()->get_uLightArray()->at(0).ambient.z);

			glUniform3f((entity->getVertexBuffer()->getShader())->getUniformLocation("light[0].diffuse"),
				entity->getVertexBuffer()->getShaderData()->get_uLightArray()->at(0).diffuse.x,
				entity->getVertexBuffer()->getShaderData()->get_uLightArray()->at(0).diffuse.y,
				entity->getVertexBuffer()->getShaderData()->get_uLightArray()->at(0).diffuse.z);

			glUniform3f((entity->getVertexBuffer()->getShader())->getUniformLocation("light[0].specular"),
				entity->getVertexBuffer()->getShaderData()->get_uLightArray()->at(0).specular.x,
				entity->getVertexBuffer()->getShaderData()->get_uLightArray()->at(0).specular.y,
				entity->getVertexBuffer()->getShaderData()->get_uLightArray()->at(0).specular.z);

			//light2

			glUniform3f((entity->getVertexBuffer()->getShader())->getUniformLocation("light[1].position"),
				entity->getVertexBuffer()->getShaderData()->get_uLightArray()->at(1).position.x,
				entity->getVertexBuffer()->getShaderData()->get_uLightArray()->at(1).position.y,
				entity->getVertexBuffer()->getShaderData()->get_uLightArray()->at(1).position.z);


			glUniform3f((entity->getVertexBuffer()->getShader())->getUniformLocation("light[1].ambient"),
				entity->getVertexBuffer()->getShaderData()->get_uLightArray()->at(1).ambient.x,
				entity->getVertexBuffer()->getShaderData()->get_uLightArray()->at(1).ambient.y,
				entity->getVertexBuffer()->getShaderData()->get_uLightArray()->at(1).ambient.z);

			glUniform3f((entity->getVertexBuffer()->getShader())->getUniformLocation("light[1].diffuse"),
				entity->getVertexBuffer()->getShaderData()->get_uLightArray()->at(1).diffuse.x,
				entity->getVertexBuffer()->getShaderData()->get_uLightArray()->at(1).diffuse.y,
				entity->getVertexBuffer()->getShaderData()->get_uLightArray()->at(1).diffuse.z);

			glUniform3f((entity->getVertexBuffer()->getShader())->getUniformLocation("light[1].specular"),
				entity->getVertexBuffer()->getShaderData()->get_uLightArray()->at(1).specular.x,
				entity->getVertexBuffer()->getShaderData()->get_uLightArray()->at(1).specular.y,
				entity->getVertexBuffer()->getShaderData()->get_uLightArray()->at(1).specular.z);


			glUniform3f((entity->getVertexBuffer()->getShader())->getUniformLocation("material.specular"),
				entity->getVertexBuffer()->getShaderData()->get_uMaterial().specular.x,
				entity->getVertexBuffer()->getShaderData()->get_uMaterial().specular.y,
				entity->getVertexBuffer()->getShaderData()->get_uMaterial().specular.z);

			glUniform1f((entity->getVertexBuffer()->getShader())->getUniformLocation("material.shininess"),
				entity->getVertexBuffer()->getShaderData()->get_uMaterial().shininess);
		
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
				BulletObject *sphereObj = nullptr;
				try {sphereObj = dynamic_cast<BulletObject*>(entity->getObject()); }
				catch (bad_cast& bc){cerr << "bad_cast caught: " << bc.what() << endl;}
		

				//DETEKCJA KOLIZJI
				if (_firstRender != true)
				{

					if (entity->getType() == ENTITY_BULLET && sphereObj->getBulletType() == BU_ENEMY)
					{
						//KOLIZJA Z GRACZEM
						Player* player = &Player::getPlayer();
						
						vec4 BulletCentreTransform = model* vec4(vec3(0.0f), 1.0f);
						vec3 BulletCentreReal = vec3(BulletCentreTransform) / BulletCentreTransform.w;
						GLfloat bulletRadius = sphereObj->getRadius();
						GLfloat spheresDistance = glm::distance(BulletCentreReal, vec3(player->getPosition().x, player->getPosition().y, player->getPosition().z));

						//detekcja kolizji
		
						if (bulletRadius + _cameraSystem->getCurrentCamera()->getRadius() > spheresDistance)
						{
							player->changeHealth(-DalekBulletDamage);
							sphereObj->destroy();
						}
						
						//# KOLIZJA Z GRACZEM
					}



				if (!sphereObj->toDestroy())
				 {
					//Sprawdz wszystkie inne Entity
					for (vector<Entity *>::iterator iterator = entityArray->begin(); iterator != entityArray->end(); iterator++)
					{
						if (distance != std::distance(entityArray->begin(), iterator))
						{//Operacje na wszystkich innych Entity
							Entity *otherEntity = *iterator;
							otherEntity->loadRealVertices();

							if (otherEntity->getType() == ENTITY_BULLET)
							{
								sphereObj->toDestroy();
								continue;
							}


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
										sphereObj->destroy();
										
										if (otherEntity->getType() == ENTITY_MAP)
										{
											//cout << "udzerzyles w mape" << endl;
										}

										if (otherEntity->getType() == ENTITY_ENEMY)
										{
											//cout << "udzerzyles we wroga" << endl;
											ModelObject *enemyObj = nullptr;
											try { enemyObj = dynamic_cast<ModelObject*>(otherEntity->getObject()); }
											catch (bad_cast& bc){ cerr << "bad_cast caught: " << bc.what() << endl; }

											if (sphereObj->getBulletType() == BU_PLAYER)
											{
												cout << enemyObj->getHealth() << endl;
												
												if (enemyObj->getHealth() > 0.0f)
												{
													enemyObj->changeHealth(-BulletDamage);
												}
											}


										}

		

									}
								}	
								
							}
						}
					}
				  }
					
				}
			}


			//MODEL
			if (entity->getObject()->getObjectType() == OB_MODEL)
			{
				ModelObject *modelObj = nullptr;
				try {modelObj = dynamic_cast<ModelObject*>(entity->getObject()); }
				catch (bad_cast& bc){ cerr << "bad_cast caught: " << bc.what() << endl;}

				modelObj->loadRealVertices(model);	

				//ARTIFICIAL INTELLIGENCE

				if (entity->getType() == ENTITY_ENEMY)
				{
					
					if (EnemyMovementEnabled)
					{
						modelObj->getAi()->move(entity, DalekSpeed);
					}
					
				}
		
				if (entity->getType() == ENTITY_R2R2)
				{
					modelObj->getAi()->move(entity, R2R2Speed);
				}


				//#ARTIFICIAL INTELLIGENCE



				if (entity->getType() != ENTITY_MAP)
				{
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

												bool bCollided = IntersectedPolygon(_myReal, _realLine, 3);
												if (bCollided)
												{

													if (entity->getType() == ENTITY_ENEMY)
													{
														modelObj->getAi()->moveWhenCollision(entity, DalekSpeed);
													}

												}




											}
										}
									}
								}
								
							}
						}
					}//Koniec detekcji
				}


			}


			entity->getObject()->draw();
			model = mat4(); 
		}





	}
	renderTextInformation();
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



void RenderSystem::setGunPosition(Entity* entity)
{
	CameraSystem *cameraSystem = &CameraSystem::getCameraSystem();
	vec3 cameraPosition = cameraSystem->getCurrentCamera()->getPosition();
	vec3 cameraCenter = cameraSystem->getCurrentCamera()->getCenter();
	vec3 cameraUp = cameraSystem->getCurrentCamera()->getUp();


	vec2 u = vec2(0.0f, -1.0f);
	vec2 v = vec2(cameraCenter.x, cameraCenter.z);
	GLfloat CameraAngle = -1 * 180 / pi<GLfloat>() * fmodf(atan2(u.x*v.y - v.x*u.y, u.x*v.x + u.y*v.y), 2 * pi<GLfloat>());


	glm::mat4 gunPos = glm::mat4(1.0f);

	gunPos = glm::translate(gunPos, cameraPosition);
	gunPos = glm::translate(gunPos, cameraCenter);

	gunPos = glm::translate(gunPos, glm::rotateY(glm::vec3(1.35, 0.0f, 1.0f),
		(glm::radians(CameraAngle) + glm::radians(90.0f))));


	vec4 gunPosition = vec4(1.0f);
	gunPosition = gunPos * gunPosition;

	entity->setPosition(makeVector3(gunPosition.x-1.0f, gunPosition.y-1.0f, gunPosition.z-1.0f));


	u = vec2(0.0f, 1.0f); //wektor wskazujacy kierunek wzroku modelu
	v = normalize(vec2(cameraCenter.x, cameraCenter.z));
	GLfloat angleX = -1 * 180 / pi<GLfloat>() * fmodf(atan2(u.x*v.y - v.x*u.y, u.x*v.x + u.y*v.y), 2 * pi<GLfloat>());
	
	u = vec2(1.0f, 0.0f); //wektor wskazujacy kierunek wzroku modelu
	v = normalize(vec2(1.0f, cameraCenter.y));
	GLfloat angleY = -1 * 180 / pi<GLfloat>() * fmodf(atan2(u.x*v.y - v.x*u.y, u.x*v.x + u.y*v.y), 2 * pi<GLfloat>());
	

	entity->setRotation(makeVector3(-angleY, angleX, entity->getRotation().z));


}





void RenderSystem::renderTextInformation()
{
	TextRender *textRender = &TextRender::getTextRender();
	Player *player = &Player::getPlayer();
	GLuint WIDTH = GameManager::_Width;
	GLuint HEIGHT = GameManager::_Height;

	GLfloat healthf = player->getHealth();
	GLfloat ammof = player->getAmmo();
	string health = to_string(healthf).substr(0, to_string(healthf).find_last_of("."));
	string ammo = to_string(ammof).substr(0, to_string(ammof).find_last_of("."));


	if (healthf<=30.0f)
	{
		textRender->renderText("Health: ", 25.0f, 25.0f, 1.0f, glm::vec3(1.0, 0.0f, 0.0f));
		textRender->renderText(health, 195.0f, 25.0f, 1.0f, glm::vec3(1.0, 0.0f, 0.0f));
	}
	else
	{
		textRender->renderText("Health: ", 25.0f, 25.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
		textRender->renderText(health, 195.0f, 25.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
	}

	textRender->renderText("Ammo: ", WIDTH - 223.0f, 25.0f, 1.0f, glm::vec3(0.0, 0.5f, 1.0f));
	textRender->renderText(ammo, WIDTH - 68.0f, 25.0f, 1.0f, glm::vec3(0.0, 0.5f, 1.0f));


	EnvironmentReactions *environment = &EnvironmentReactions::getEnvironmentReactions();
	if (environment->getAllEnemyDeadStatus() == true)
	{
		textRender->renderText("VICTORY!", (WIDTH / 2) - 185.0f, HEIGHT / 2, 2.0f, glm::vec3(1.0, 0.5f, 0.0f));
	}else if(healthf <= 0.0f)
	{
		textRender->renderText("GAME OVER", (WIDTH / 2) - 250.0f, HEIGHT / 2, 2.0f, glm::vec3(1.0, 0.0f, 0.0f));
	}

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


void RenderSystem::setFreshRender()
{
	_firstRender = true;
}

void RenderSystem::update(vector<Entity *> *entityArray)
{
	//DESTRUKCJE
	for (vector<Entity *>::iterator iterator = entityArray->begin(); iterator != entityArray->end();/**/)
	{
		Entity *entity = *iterator;
		bool destroy = false;

		if (entity->getType() == ENTITY_ENEMY)
		{

			ModelObject *enemyObj = nullptr;
			try { enemyObj = dynamic_cast<ModelObject*>(entity->getObject()); }
			catch (bad_cast& bc){ cerr << "bad_cast caught: " << bc.what() << endl; }
			EnvironmentReactions *environment = &EnvironmentReactions::getEnvironmentReactions();


			if (enemyObj->getHealth() <= 0.0f)
			{
				cout << "ktos tu umarl" << endl;
				destroy = true;
				environment->countDalek();
			}

		}

		if (entity->getType() == ENTITY_BULLET)
		{
			BulletObject *sphereObj = nullptr;
			try { sphereObj = dynamic_cast<BulletObject*>(entity->getObject()); }
			catch (bad_cast& bc){cerr << "bad_cast caught: " << bc.what() << endl;}

				if (sphereObj->toDestroy())
				{
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


RenderSystem::RenderSystem() :_window(glfwGetCurrentContext()), _cameraSystem(&CameraSystem::getCameraSystem()), _firstRender(true)
{
	_newObjects = new vector<Entity *>();
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