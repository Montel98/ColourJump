#pragma once

#include "Entity.h"

Entity::Entity(float xPos, float yPos, float zPos) : cBox(glm::vec3(0, 0, 0),
	glm::vec3(0 + 0.5f, 0 + 0.5f, 0 + 0.5f)) {
	this->state.position = glm::vec3(xPos, yPos, zPos);
	this->state.velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	this->state.acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
}