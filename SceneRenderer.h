#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLEW_STATIC
#include <GL/glew.h>

#ifndef SCENERENDERER_H
#define SCENERENDERER_H

class SceneRenderer {
public:
	GLuint uniView, uniProj, uniModel, uniLightPos, uniLightColour;
	GLuint vertexShader, fragmentShader;
	GLuint shaderProgram;
	glm::vec3 lightPos, lightColour;
	glm::mat4 proj, model;

	SceneRenderer();
};

#endif