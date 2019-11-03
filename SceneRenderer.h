#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLEW_STATIC
#include <GL/glew.h>

#ifndef SCENERENDERER_H
#define SCENERENDERER_H

class SceneRenderer {
private:
	GLuint uniView, uniProj, uniModel, uniLightPos, uniLightColour; // Handles to all shader uniforms
	GLuint vertexShader, fragmentShader;
	GLuint shaderProgram; // Handle to shader program
	GLuint viewingPos;
	glm::vec3 lightPos, lightColour;
	glm::mat4 proj, model; // Model and projection matrices

public:
	SceneRenderer();
	void setSpotLightPostion();

	// CubeRenderer and SceneRenderer are tightly coupled
	// CubeRenderer needs access the private handles
	friend class CubeRenderer;
};

#endif