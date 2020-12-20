#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "stb_image.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "mesh.h"
#include "texture.h"
#include "shader.h"


class Model 
{
    public:
        Model();
        ~Model();
        void loadModel(std::string path);
        void Draw();

    private:
        std::vector<Mesh> meshes;
        std::string directory;

        void processNode(aiNode* node, const aiScene* scene);
        Mesh processMesh(aiMesh* mesh, const aiScene* scene);
};

class RenderModel 
{
public:
	//
	std::string modelPath;

	// Define the material of this  render model
	glm::vec3 albedoColor = glm::vec3(1.0f);
	Texture objectAlbedo;
	Texture objectNormal;
	Texture objectRoughness;
	Texture objectMetalness;
	Texture objectAO;
	glm::vec3 materialF0 = glm::vec3(0.04f);  // UE4 dielectric

	// Define Model
	glm::mat4 extraModel;
	glm::vec3 modelScale;
	glm::vec3 modelPosition;
	glm::vec3 modelRotationAxis;
	float modelRotationSpeed;
	
	// Define Model Render Things
	 glm::mat4 projViewModel;
	// glm::mat4 preProjMat4;
	glm::mat4 prevProjViewModel;
	bool bRotation = false;

	// We can still define  the  shader here. But not needed for current  settins
	

	void initMaterial( 
	    const std::string materialName,
		const std::string objectAlbedoPath,
		const std::string objectNormalPath,
		const std::string objectRoughnessPath,
		const std::string objectMetalnessPath,
		const std::string objectAOPath,
		glm::vec3 albedoColor_input)
	{
		objectAlbedo.setTexture(objectAlbedoPath.c_str(), materialName+"Albedo", true);
		objectNormal.setTexture(objectNormalPath.c_str(), materialName+ "Normal", true);
		objectRoughness.setTexture(objectRoughnessPath.c_str(), materialName + "Roughness", true);
		objectMetalness.setTexture(objectMetalnessPath.c_str(), materialName + "Metalness", true);
		objectAO.setTexture(objectAOPath.c_str(), materialName + "AO", true);		
		albedoColor = albedoColor_input;
	}


	void initModelParas(std::string path ,glm::vec3 modelScale_input, glm::vec3 modelPosition_input, glm::vec3 modelRotationAxis_input, float modelRotationSpeed_input)
	{
		modelPath = path;
		loadModel(modelPath);

		modelScale = modelScale_input ;
		modelPosition = modelPosition_input;
		modelRotationAxis = modelRotationAxis_input;
		modelRotationSpeed = modelRotationSpeed_input;
		extraModel = glm::mat4();
	}

	void Render(Shader &gBufferShader,glm::mat4 &projection, glm::mat4 &view, float f_time)
	{
		glm::mat4 model;
		model = glm::mat4();
		model = model * extraModel;
		model = glm::translate(model, modelPosition);		
		GLfloat rotationAngle = f_time/ 5.0f * modelRotationSpeed;
		model = glm::rotate(model, rotationAngle, modelRotationAxis);
		model = glm::scale(model, modelScale);
		

		projViewModel = projection * view * model;

		if (!bRotation)
			prevProjViewModel = projViewModel;

		glUniformMatrix4fv(glGetUniformLocation(gBufferShader.Program, "projViewModel"), 1, GL_FALSE, glm::value_ptr(projViewModel));
		glUniformMatrix4fv(glGetUniformLocation(gBufferShader.Program, "prevProjViewModel"), 1, GL_FALSE, glm::value_ptr(prevProjViewModel));
		glUniformMatrix4fv(glGetUniformLocation(gBufferShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniform3f(glGetUniformLocation(gBufferShader.Program, "albedoColor"), albedoColor.r, albedoColor.g, albedoColor.b);


		glActiveTexture(GL_TEXTURE0);
		objectAlbedo.useTexture();
		glUniform1i(glGetUniformLocation(gBufferShader.Program, "texAlbedo"), 0);
		glActiveTexture(GL_TEXTURE1);
		objectNormal.useTexture();
		glUniform1i(glGetUniformLocation(gBufferShader.Program, "texNormal"), 1);
		glActiveTexture(GL_TEXTURE2);
		objectRoughness.useTexture();
		glUniform1i(glGetUniformLocation(gBufferShader.Program, "texRoughness"), 2);
		glActiveTexture(GL_TEXTURE3);
		objectMetalness.useTexture();
		glUniform1i(glGetUniformLocation(gBufferShader.Program, "texMetalness"), 3);
		glActiveTexture(GL_TEXTURE4);
		objectAO.useTexture();
		glUniform1i(glGetUniformLocation(gBufferShader.Program, "texAO"), 4);
		
		Draw();
		
		prevProjViewModel = projViewModel;
	}
	void mult(float a);


	   	 
	RenderModel();
	~RenderModel();

	void loadModel(std::string path);
	void Draw();
private:
	std::vector<Mesh> meshes;
	std::string directory;
	void normalize();
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
};







