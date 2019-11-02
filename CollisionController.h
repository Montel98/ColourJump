#pragma once

#ifndef COLLISIONCONTROLLER_H
#define COLLISIONCONTROLLER_H

#include <glm/gtc/matrix_transform.hpp>
#include "Entity.h"
#include "Player.h"
#include "levelMap.h"
#include <queue>


struct Overlap {
	char axis;
	float displacement;
	Overlap(char, float);
};

class CollisionEvent {
public:
	glm::vec3 surfaceNormal; // Vector perpendicular to collision face
	glm::vec3 displacement;
	Entity* entity; // Entity that collided with player
	CollisionEvent(Entity*, glm::vec3);
};

class CollisionController {
private:
	Player &player;
	bool isCollision(Entity*);
	void handleCollision(Entity*);
	Overlap getMinOverlap(Entity*); // Gets the axis with min overlap between the bounding boxes
	glm::vec3 getSurfaceNormal(Entity*, Overlap&);
	bool isValidCollision(Entity*, Overlap&); // Checks if corrected position does not result in another collsion
	std::queue<CollisionEvent> collisions; // Queue of collision events with player
public:
	CollisionController(Player&);
	void checkCollisions(levelMap&);
	bool unhandledCollisions();
	CollisionEvent& getCollisionEvent();
	void popCollisionEvent();
};

#endif