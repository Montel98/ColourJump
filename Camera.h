#pragma once

#ifndef CAMERA_H
#define CAMERA_H

#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
	glm::vec3 pos; // Camera position
	glm::vec3 looking; // Position in world space camera is 'looking' at
	glm::vec3 up; // Up vector perpendicular to camera's direction vector
	glm::vec3 direction; // looking - pos
	float sensitivity;

public:
	Camera(glm::vec3, glm::vec3, glm::vec3);
	void rotateH(float); // rotate horizontally relative to camera orientation
	void rotateV(float); // rotate vertically relative to camera orientation
	void setPosition(glm::vec3);
	void setDirection(glm::vec3);
};

#endif