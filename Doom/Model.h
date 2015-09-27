#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <SOIL/SOIL.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Shader.h"
#include "Constants.h"
#include "Mesh.h"
#include "VertexData.h"
#include "VertexBuffer.h"


using namespace glm;



class Model
{
public:
	Model(GLchar* path) :_firstMesh(true)
	{
		bbShader = new Shader("boundingbox.vs", "boundingbox.frag");
		configcube();
		this->loadModel(path);
		
	}

	void Draw(Shader *shader,mat4& model, mat4& view, mat4& projection)
	{
		_gameModel = model;
		_gameView = view;
		_gameProjection = projection;

		for (GLuint i = 0; i < this->meshes.size(); i++)
			this->meshes[i].Draw(shader);

		drawBoundingBox();
	}

	vector <ThreeVertices>*getRealVertices()
	{
		return _myRealVertices;
	}

	void loadRealVertices(mat4& model)
	{
		_myRealVertices->clear();
		ThreeVertices data;
		vec3 point = vec3(0.0f);
		vec4 point4 = vec4(0.0f);

		int i = 0;
		int j = 0;

		for (vector<ThreeVertices>::iterator iterator = _myVertices->begin(); iterator != _myVertices->end(); iterator++)
		{

			data.a = iterator->a;
			point4 = model * modelTransform * vec4(data.a.x, data.a.y, data.a.z, 1.0f);
			data.a = vec3(point4) / point4.w;

			data.b = iterator->b;
			point4 = model * modelTransform * vec4(data.b.x, data.b.y, data.b.z, 1.0f);
			data.b = vec3(point4) / point4.w;

			data.c = iterator->c;
			point4 = model * modelTransform * vec4(data.c.x, data.c.y, data.c.z, 1.0f);
			data.c = vec3(point4) / point4.w;

			_myRealVertices->push_back(data);
		}
	}


private:

	vector<Mesh> meshes;
	string directory;
	vector<Texture> textures_loaded;
	bool _firstMesh;
	Shader *bbShader;
	glm::mat4 _gameModel;
	glm::mat4 _gameView;
	glm::mat4 _gameProjection;
	GLuint BBVAO; //BoundingBoxVAO

	//do detekcji kolizji
	vector <ThreeVertices> *_myVertices;
	vector <ThreeVertices> *_myRealVertices;
	int nrOfVertices;

	//Bounding box
	glm::mat4 modelTransform; //macierz modelu 
	GLfloat
		min_x = 0.0f, max_x = 0.0f,
		min_y = 0.0f, max_y = 0.0f,
		min_z = 0.0f, max_z = 0.0f;


	GLint TextureFromFile(const char* path, string directory)
	{
		string filename = string(path);
		filename = directory + '/' + filename;
		GLuint textureID;
		glGenTextures(1, &textureID);
		int width, height;
		unsigned char* image = SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);
		SOIL_free_image_data(image);
		return textureID;
	}



	void configcube()
	{
		VertexDataP vertices[] = {
			-0.5f, -0.5f, -0.5f,
			0.5f, -0.5f, -0.5f,
			0.5f, 0.5f, -0.5f,
			0.5f, 0.5f, -0.5f,
			-0.5f, 0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,

			-0.5f, -0.5f, 0.5f,
			0.5f, -0.5f, 0.5f,
			0.5f, 0.5f, 0.5f,
			0.5f, 0.5f, 0.5f,
			-0.5f, 0.5f, 0.5f,
			-0.5f, -0.5f, 0.5f,

			-0.5f, 0.5f, 0.5f,
			-0.5f, 0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f, 0.5f,
			-0.5f, 0.5f, 0.5f,

			0.5f, 0.5f, 0.5f,
			0.5f, 0.5f, -0.5f,
			0.5f, -0.5f, -0.5f,
			0.5f, -0.5f, -0.5f,
			0.5f, -0.5f, 0.5f,
			0.5f, 0.5f, 0.5f,

			-0.5f, -0.5f, -0.5f,
			0.5f, -0.5f, -0.5f,
			0.5f, -0.5f, 0.5f,
			0.5f, -0.5f, 0.5f,
			-0.5f, -0.5f, 0.5f,
			-0.5f, -0.5f, -0.5f,

			-0.5f, 0.5f, -0.5f,
			0.5f, 0.5f, -0.5f,
			0.5f, 0.5f, 0.5f,
			0.5f, 0.5f, 0.5f,
			-0.5f, 0.5f, 0.5f,
			-0.5f, 0.5f, -0.5f,
		};



		_myRealVertices = new vector<ThreeVertices>();
		_myVertices = new vector<ThreeVertices>();
		nrOfVertices = sizeof(vertices) / (3 * sizeof(GLfloat));


		ThreeVertices data;
		vec3 point = vec3(0.0f);

		int j = 0;
		for (int i = 0; i < nrOfVertices; i++)
		{
			if (j % 3 == 0)	j = 0;

			point.x = vertices[i].positionCoordinates.x;
			point.y = vertices[i].positionCoordinates.y;
			point.z = vertices[i].positionCoordinates.z;
			
			if (j == 0)
			{
				data.a = point;
				j++;
			}
			else if (j == 1)
			{
				data.b = point;
				j++;
			}
			else
			{
				data.c = point;
				_myVertices->push_back(data);
				j++;
			}
		}

		GLuint VBO;
		glGenVertexArrays(1, &BBVAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(BBVAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		glBindVertexArray(0);
	}


	void drawBoundingBox()
	{
	
		bbShader->Use();

		glm::mat4 newModel = _gameModel * modelTransform;

		GLint modelLoc = glGetUniformLocation(bbShader->Program, "model");
		GLint viewLoc = glGetUniformLocation(bbShader->Program, "view");
		GLint projLoc = glGetUniformLocation(bbShader->Program, "projection");
		
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(_gameView));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(_gameProjection));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(newModel));


		if (Show_Bounding_Boxes)
		{
			glBindVertexArray(BBVAO);
			glLineWidth(5.0f);
			glDrawArrays(GL_LINES, 0, 36); 
			glBindVertexArray(0);		   
		}

	}


	
	void loadModel(string path)
	{
	
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);
		
		if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
		{
			cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
			return;
		}
		
		this->directory = path.substr(0, path.find_last_of('/'));

		this->processNode(scene->mRootNode, scene);

		glm::vec3 size = glm::vec3(max_x - min_x, max_y - min_y, max_z - min_z);
		glm::vec3 center = glm::vec3((min_x + max_x) / 2, (min_y + max_y) / 2, (min_z + max_z) / 2);
		modelTransform = glm::translate(glm::mat4(1), center)* glm::scale(glm::mat4(1), size);

		cout << "#";

	}

	
	void processNode(aiNode* node, const aiScene* scene)
	{
		
		for (GLuint i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			this->meshes.push_back(this->processMesh(mesh, scene));
		}
		
		for (GLuint i = 0; i < node->mNumChildren; i++)
		{
			this->processNode(node->mChildren[i], scene);
		}

	}

	Mesh processMesh(aiMesh* mesh, const aiScene* scene)
	{
		
		vector<Vertex> vertices;
		vector<GLuint> indices;
		vector<Texture> textures;

		
		for (GLuint i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex vertex;
			glm::vec3 vector;
				
			//Bounding Box
			if (_firstMesh)
			{
				min_x = max_x = mesh->mVertices[0].x;
				min_y = max_y = mesh->mVertices[0].y;
				min_z = max_z = mesh->mVertices[0].z;
				_firstMesh = false;
			}
			if (mesh->mVertices[i].x < min_x) min_x = mesh->mVertices[i].x;
			if (mesh->mVertices[i].x > max_x) max_x = mesh->mVertices[i].x;
			if (mesh->mVertices[i].y < min_y) min_y = mesh->mVertices[i].y;
			if (mesh->mVertices[i].y > max_y) max_y = mesh->mVertices[i].y;
			if (mesh->mVertices[i].z < min_z) min_z = mesh->mVertices[i].z;
			if (mesh->mVertices[i].z > max_z) max_z = mesh->mVertices[i].z;


			vector.x = mesh->mVertices[i].x;
			vector.y = mesh->mVertices[i].y;
			vector.z = mesh->mVertices[i].z;
			vertex.Position = vector;

			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex.Normal = vector;
	
			if (mesh->mTextureCoords[0]) 
			{
				glm::vec2 vec;
	
				vec.x = mesh->mTextureCoords[0][i].x;
				vec.y = mesh->mTextureCoords[0][i].y;
				vertex.TexCoords = vec;
			}
			else
				vertex.TexCoords = glm::vec2(0.0f, 0.0f);
			vertices.push_back(vertex);
		}
		
		for (GLuint i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
		
			for (GLuint j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}
	
		if (mesh->mMaterialIndex >= 0)
		{
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

			vector<Texture> diffuseMaps = this->loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
			textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
	
			vector<Texture> specularMaps = this->loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
			textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		}

		return Mesh(vertices, indices, textures);
	}

	vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName)
	{
		vector<Texture> textures;
		for (GLuint i = 0; i < mat->GetTextureCount(type); i++)
		{
			aiString str;
			mat->GetTexture(type, i, &str);
			
			GLboolean skip = false;
			for (GLuint j = 0; j < textures_loaded.size(); j++)
			{
				if (textures_loaded[j].path == str)
				{
					textures.push_back(textures_loaded[j]);
					skip = true; 
					break;
				}
			}
			if (!skip)
			{   
				Texture texture;
				texture.id = TextureFromFile(str.C_Str(), this->directory);
				texture.type = typeName;
				texture.path = str;
				textures.push_back(texture);
				this->textures_loaded.push_back(texture);
			}
		}
		return textures;
	}
};
