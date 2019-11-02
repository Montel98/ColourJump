#pragma once

#ifndef ENTITY_H
#define ENTITY_H

#include <glm/gtc/matrix_transform.hpp>
#include "PhysicsComponent.h"
#include "CollisionBox.h"

class Entity {
public:
	bool gravityEnabled;
	bool isDestroyed;

	Entity(float, float, float);
	physicsComponent state;
	CollisionBox cBox; // The collision bounds for the entity
	virtual void act() = 0;
	virtual int get_block_ID() const = 0;
	bool isGravityEnabled() { return gravityEnabled; }

	physicsComponent& getPhysicsComponent() {
		return state;
	}
	CollisionBox& getCollisionBox() {
		return cBox;
	}
};

#endif