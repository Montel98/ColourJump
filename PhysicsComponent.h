#pragma once

#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

#include <glm/gtc/matrix_transform.hpp>
#include <vector>

class physicsComponent {
public:
	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 acceleration;
public:
	void updateState(float dt);
	std::vector<glm::vec3*> components; // Acceleration components at a specific instant
	void addComponent(glm::vec3*);
	void removeComponent(glm::vec3*);

};

#endif