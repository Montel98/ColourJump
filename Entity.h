#pragma once

#ifndef ENTITY_H
#define ENTITY_H

#include <glm/gtc/matrix_transform.hpp>
#include "PhysicsComponent.h"
#include "CollisionBox.h"

class Entity {
public:
	Entity(float, float, float);
	physicsComponent state;
	CollisionBox cBox;
	virtual void act() = 0;
	virtual int get_block_ID() const = 0;
	physicsComponent& getPhysicsComponent() {
		return state;
	}
	CollisionBox& getCollisionBox() {
		return cBox;
	}
};

#endif