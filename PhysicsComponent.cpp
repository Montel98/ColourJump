#pragma once

#include "PhysicsComponent.h"

// Adds a new acceleration component to the entity's component list
void physicsComponent::addComponent(glm::vec3 *newComponent) {
	components.push_back(newComponent);
}

// Removes an acceleration component if exists, otherwise no changes made
void physicsComponent::removeComponent(glm::vec3* component) {
	for (int c = 0; c < components.size(); ++c) {
		glm::vec3 *it = components[c];
		if (it == component) {
			components.erase(components.begin() + c);
		}
	}
}

void physicsComponent::updateState(float dt) {
	glm::vec3 rAcceleration(0.0f);

	// Sum all acceleration components to get a resultant vector
	for (int c = 0; c < components.size(); ++c) {
		glm::vec3 *component = components[c];
		rAcceleration.x += component->x;
		rAcceleration.y += component->y;
		rAcceleration.z += component->z;
	}

	acceleration = rAcceleration;
	velocity += rAcceleration * dt;
	position += velocity * dt;
}