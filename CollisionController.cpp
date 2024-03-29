#pragma once
#include "CollisionController.h"

CollisionController::CollisionController(Player& p) : player(p) {
}

bool CollisionController::unhandledCollisions() {
	return collisions.size() > 0;
}

// Determine if player is within collision box bounds of entity
bool CollisionController::isCollision(Entity* entity) {
	physicsComponent &pPos = player.getPhysicsComponent();

	physicsComponent &tPos = entity->getPhysicsComponent();

	return ((tPos.position.x + entity->getCollisionBox().xMin <= pPos.position.x + player.getCollisionBox().xMax &&
		tPos.position.x + entity->getCollisionBox().xMax >= pPos.position.x + player.getCollisionBox().xMin) &&
		(tPos.position.y + entity->getCollisionBox().yMin <= pPos.position.y + player.getCollisionBox().yMax &&
			tPos.position.y + entity->getCollisionBox().yMax >= pPos.position.y + player.getCollisionBox().yMin) &&
			(tPos.position.z + entity->getCollisionBox().zMin <= pPos.position.z + player.getCollisionBox().zMax &&
				tPos.position.z + entity->getCollisionBox().zMax >= pPos.position.z + player.getCollisionBox().zMin));
}

Overlap CollisionController::getMinOverlap(Entity* entity) {

	Overlap overlaps[3] = { Overlap('X', INT_MAX), Overlap('Y', INT_MAX), Overlap('Z', INT_MAX) };
	glm::vec3 displacements[] = { glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.0f) };
	physicsComponent &pPos = player.getPhysicsComponent();
	physicsComponent &tPos = entity->getPhysicsComponent();
	float offset = 0.000001f; // offset from collision point

	//x
	// If x velocity is positive, entity can only possibly hit lower x face
	if (pPos.velocity.x > 0) {
		overlaps[0].displacement = (tPos.position.x + entity->getCollisionBox().xMin) - (pPos.position.x + player.getCollisionBox().xMax) - offset;
	}
	// If x velocity is negative, entity can only possibly hit upper x face
	else if (pPos.velocity.x < 0) {
		overlaps[0].displacement = (tPos.position.x + entity->getCollisionBox().xMax) - (pPos.position.x + player.getCollisionBox().xMin) + offset;
	}

	//y
	// If y velocity is positive, entity can only possibly hit lower y face
	if (pPos.velocity.y > 0) {
		overlaps[1].displacement = (tPos.position.y + entity->getCollisionBox().yMin) - (pPos.position.y + player.getCollisionBox().yMax) - offset;
	}
	// If y velocity is negative, entity can only possibly hit upper y face
	else if (pPos.velocity.y < 0) {
		overlaps[1].displacement = (tPos.position.y + entity->getCollisionBox().yMax) - (pPos.position.y + player.getCollisionBox().yMin) + offset;
	}

	//z
	// If y velocity is positive, entity can only possibly hit lower z face
	if (pPos.velocity.z > 0) {
		overlaps[2].displacement = (tPos.position.z + entity->getCollisionBox().zMin) - (pPos.position.z + player.getCollisionBox().zMax) - offset;
	}
	// If y velocity is negative, entity can only possibly hit upper z face
	else if (pPos.velocity.z <= 0) {
		overlaps[2].displacement = (tPos.position.z + entity->getCollisionBox().zMax) - (pPos.position.z + player.getCollisionBox().zMin) + offset;
	}

	// find component with lowest overlap during collision
	Overlap& min_overlap = overlaps[0];
	for (int c = 0; c < 3; ++c) {
		if (abs(min_overlap.displacement) > abs(overlaps[c].displacement)) {
			min_overlap = overlaps[c];
		}
	}
	return min_overlap;
}

// Returns the surface normal of the face that collided with the player
glm::vec3 CollisionController::getSurfaceNormal(Entity* entity, Overlap& overlap) {
	if (overlap.axis == 'X') {
		if (player.getPhysicsComponent().velocity.x > 0) {
			return glm::vec3(-1.0f, 0.0f, 0.0f);
		}
		else if (player.getPhysicsComponent().velocity.x < 0) {
			return glm::vec3(1.0f, 0.0f, 0.0f);
		}
	}

	if (overlap.axis == 'Y') {
		if (player.getPhysicsComponent().velocity.y > 0) {
			return glm::vec3(0.0f, -1.0f, 0.0f);
		}
		else if (player.getPhysicsComponent().velocity.y < 0) {
			return glm::vec3(0.0f, 1.0f, 0.0f);
		}
	}

	if (overlap.axis == 'Z') {
		if (player.getPhysicsComponent().velocity.z > 0) {
			return glm::vec3(0.0f, 0.0f, -1.0f);
		}
		else if (player.getPhysicsComponent().velocity.z < 0) {
			return glm::vec3(0.0f, 0.0f, 1.0f);
		}
	}
}

// Determines axis with smallest overlap during collision
// Corrects the player's to be slightly out of collision zone
void CollisionController::handleCollision(Entity* entity) {
	if (isCollision(entity)) {
		Overlap overlap = getMinOverlap(entity);
		if (isValidCollision(entity, overlap)) {
			glm::vec3 normal = getSurfaceNormal(entity, overlap);
			glm::vec3 displacement(0.0f);

			if (overlap.axis == 'X') {
				player.getPhysicsComponent().position.x += overlap.displacement;
			}
			else if (overlap.axis == 'Y') {
				player.getPhysicsComponent().position.y += overlap.displacement;
			}
			else if (overlap.axis == 'Z') {
				player.getPhysicsComponent().position.z += overlap.displacement;
			}
			collisions.push(CollisionEvent(entity, normal));
		}
	}
}

// Check adjacent 9 cells for collisions
void CollisionController::checkCollisions(levelMap& map) {
	int offsets[] = { -1, 0, 1 };
	for (unsigned int x = 0; x < 3; ++x) {
		for (unsigned int y = 0; y < 3; ++y) {
			if (x + player.sectorX < map.objects.size() && y + player.sectorY < map.objects[0].size()) {
				handleCollision(&map.objects[x + player.sectorX][y + player.sectorY]);
			}
		}
	}
}

// Verifies if position correction does not result in another collision
bool CollisionController::isValidCollision(Entity* entity, Overlap& overlap) {
	glm::vec3 temp = player.getPhysicsComponent().position;
	bool isValid;

	if (overlap.axis == 'X') {
		player.getPhysicsComponent().position.x += overlap.displacement;
		isValid = !isCollision(entity);
		player.getPhysicsComponent().position.x = temp.x; //restore x position
	}
	else if (overlap.axis == 'Y') {
		player.getPhysicsComponent().position.y += overlap.displacement;
		isValid = !isCollision(entity);
		player.getPhysicsComponent().position.y = temp.y; //restore y position
	}
	else if (overlap.axis == 'Z') {
		player.getPhysicsComponent().position.z += overlap.displacement;
		isValid = !isCollision(entity);
		player.getPhysicsComponent().position.z = temp.z; //restore z position
	}

	return isValid;
}

CollisionEvent& CollisionController::getCollisionEvent() {
	return collisions.front();
}

void CollisionController::popCollisionEvent() {
	collisions.pop();
}

Overlap::Overlap(char axis, float overlap) : axis(axis), displacement(overlap) {
}

CollisionEvent::CollisionEvent(Entity* entity, glm::vec3 normal) : surfaceNormal(normal), entity(entity) {
}