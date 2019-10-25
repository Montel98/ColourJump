#pragma once

#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 facing, glm::vec3 upwards) : pos(position), looking(facing), up(upwards) {
	direction = looking - pos;
}

void Camera::rotateH(float angle) {
	glm::mat4 rot = glm::rotate(glm::mat4(1.0f), (-1 * angle * 0.005f), up);
	glm::vec4 bla1(direction, 1);
	bla1 = rot * bla1;

	direction.x = bla1.x;
	direction.y = bla1.y;
	direction.z = bla1.z;

	looking = pos + direction;
}

void Camera::rotateV(float angle) {
	glm::mat4 rot = glm::rotate(glm::mat4(1.0f), (-1 * angle * 0.005f), glm::cross(direction, up));
	glm::vec4 bla(direction, 1);
	bla = rot * bla;

	direction.x = bla.x;
	direction.y = bla.y;
	direction.z = bla.z;

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