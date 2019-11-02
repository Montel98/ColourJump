#pragma once

#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 facing, glm::vec3 upwards) : pos(position), looking(facing), up(upwards) {
	direction = looking - pos;
	sensitivity = 0.002f;
}

// Rotate camera about "horizontal" axis perpendicular to player's line of site
void Camera::rotateH(float angle) {
	glm::mat4 rot = glm::rotate(glm::mat4(1.0f), (-1 * angle), up);
	glm::vec4 dir4(direction, 1);
	dir4 = rot * dir4;

	direction.x = dir4.x;
	direction.y = dir4.y;
	direction.z = dir4.z;

	looking = pos + direction;
}

// Rotate camera about "verticle" axis perpendicular to player's line of site
void Camera::rotateV(float angle) {
	glm::mat4 rot = glm::rotate(glm::mat4(1.0f), (-1 * angle), glm::cross(direction, up));
	glm::vec4 dir4(direction, 1);
	dir4 = rot * dir4;

	direction.x = dir4.x;
	direction.y = dir4.y;
	direction.z = dir4.z;

	looking = pos + direction;
}

void Camera::setPosition(glm::vec3 newPos) {
	pos = newPos + glm::vec3(0.25f, 0.25f, 1.25f);
	looking = pos + direction;
}

void Camera::setDirection(glm::vec3 newDirection) {
	direction = newDirection;
	looking = pos + direction;
}