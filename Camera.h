#pragma once

#ifndef CAMERA_H
#define CAMERA_H

#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
	glm::vec3 pos;
	glm::vec3 looking;
	glm::vec3 up;
	glm::vec3 direction;
	float sensitivity;

public:
	Camera(glm::vec3, glm::vec3, glm::vec3);
	void rotateH(float); // rotate horizontal relative to camera orientation
	void rotateV(float); // rotate vertical relative to camera orientation
	void setPosition(glm::vec3);
	void setDirection(glm::vec3);
};

#endif