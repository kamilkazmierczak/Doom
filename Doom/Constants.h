#pragma once
#include  <GLFW\glfw3.h>
//const GLuint WIDTH = 800, HEIGHT = 600;
const GLuint DefaultWidth = 800, DefaultHeight = 600;
const GLfloat UpdatesPerSecond = 60.0f;
const glm::vec3 CameraPosition = glm::vec3(0.0f, 0.0f, 2.0f);
const bool FpsCamera = true;
const bool Show_Bounding_Boxes = false;
const bool EnemyMovementEnabled = true;
const GLfloat BulletSpeed = 0.08f;
const GLfloat BulletRadius = 0.05f;  //0.05f
const GLfloat DalekSpeed = 0.019f;  //0.019f
const GLfloat R2R2Speed = 0.019f;  //0.019f
const GLfloat TimeToEscape = 1.5f; //czas z jakim dalek ignoruje obecnosc kamery i za nia nie jedzie
const GLfloat ReloadTime = 0.5f;
const GLfloat MaxAmmo = 15.0f;
const GLfloat MaxHealth = 100.0f;
const GLfloat BulletDamage = 2.0f; //1.0f
const GLfloat DalekBulletDamage = 10.0f;
const GLfloat ShootingConstant = 10.0f;
const int NumberOfDaleks = 3;

/*
#error C1189: #error :  gl.h included before glew.h
- Entity musi byc zadeklarowane przed Vector3 i Vector4 
- dla bezpieczenstwa <GLFW\glfw3.h> dodawac jako ostatni
*/