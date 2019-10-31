#pragma once

#ifndef CUBERENDERER_H
#define CUBERENDERER_H

#include "SceneRenderer.h"
#include "Camera.h"

class CubeRenderer {
private:
	GLint uniColour;
	SceneRenderer& sceneRenderer;
public:
	CubeRenderer(SceneRenderer&);
	void render(const glm::vec3 &position, const glm::vec3 &color, const Camera &camera);
};

#endif