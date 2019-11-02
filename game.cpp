#pragma once

#include "game.h"

extern glm::vec3 normalForce(0.0f, 0.0f, 9.8f);
extern glm::vec3 gravity(0.0f, 0.0f, -9.8f);											

void Controller::draw(Entity* entity, Camera& camera) {
	glm::vec3 position = entity->getPhysicsComponent().position;
	int id = entity->get_block_ID();
	cubeRenderer.render(position, Block::colourValues[id].first, camera);
}

Controller::Controller(levelMap &mapLevel, Player &p, InputController& ic, WorldTime& wt) : map(mapLevel), player(p), inputController(ic), time(wt), round(wt,4,4), cubeRenderer(scene)  {
	roundNumber = 1;
	blockVal = -1;
}

void Controller::updateStates(Camera &camera) {

	float dt = time.getDeltaTime();
	inputController.ProcessInputs(dt);
	player.act();
	player.getPhysicsComponent().updateState(dt);
	player.updateSector(); // update player's grid for purpose of collision checking
	camera.setPosition(player.getPhysicsComponent().position);
	camera.setDirection(player.direction);
	updateRound();

	for (unsigned int x = 0; x < map.objects.size(); ++x) {
		for (unsigned int y = 0; y < map.objects[x].size(); ++y) {
			Entity *currentObject = &map.objects[x][y];
			
			// Make cubes fall if round has ended
			if (round.isActiveInter() && !currentObject->isGravityEnabled()) {
				if (currentObject->get_block_ID() != blockVal && !currentObject->isDestroyed) {
					currentObject->getPhysicsComponent().addComponent(&gravity);
					currentObject->gravityEnabled = true;
				}
			}

			// reset cube position and disable gravity on new round
			else if (round.isActiveRound() && currentObject->isGravityEnabled()) {
				if (!currentObject->isDestroyed) {
					currentObject->getPhysicsComponent().removeComponent(&gravity);
					currentObject->getPhysicsComponent().position.z = 0;
					currentObject->getPhysicsComponent().velocity.z = 0;
					currentObject->gravityEnabled = false;
				}
			}
			
			currentObject->act();
			currentObject->getPhysicsComponent().updateState(dt);
		}
	}

	player.getPhysicsComponent().removeComponent(&gravity);
	checkCollisions();

	if (player.isOnSurface) {
		player.getPhysicsComponent().removeComponent(&gravity);
		player.getPhysicsComponent().velocity.z = 0.0f;
	}
	else {
		player.getPhysicsComponent().addComponent(&gravity);
	}
}

void Controller::checkCollisions() {
	CollisionController col(player);
	col.checkCollisions(map);
	player.isOnSurface = false;

	while (col.unhandledCollisions()) {
		CollisionEvent e = col.getCollisionEvent();

		if (e.entity->get_block_ID() != blockVal) {
			e.entity->isDestroyed = true;
		}
		if (e.surfaceNormal.z == 1.0f) {
			player.isOnSurface = true;
		}
		// halt x component of player if collision is on x plane
		else if (e.surfaceNormal.x == 1.0f || e.surfaceNormal.x == -1.0f) {
			player.getPhysicsComponent().velocity.x = 0.0f;
		}
		// halt y component of player if collision is on x plane
		else if (e.surfaceNormal.y == 1.0f || e.surfaceNormal.y == -1.0f) {
			player.getPhysicsComponent().velocity.y = 0.0f;
		}
		col.popCollisionEvent();
	}
}

void Controller::updateRound() {
	round.updateState();

	if (round.getRoundNumber() == 0) {
		round.startRound();
		prevBlockVal = blockVal;
		blockVal = rand() % 8;
		//std::cout << "ROUND " << round.getRoundNumber() << std::endl;
		//std::cout << colourNames[blockVal] << std::endl;
	}
	else {
		if (round.isRoundFinished()) {
			round.startInter();
		}
		else if (round.isInterFinished()) {
			map.setRandomColours();
			round.startRound();
			prevBlockVal = blockVal;
			blockVal = rand() % 8;
			//std::cout << "ROUND " << round.getRoundNumber() << std::endl;
			//std::cout << colourNames[blockVal] << std::endl;
		}
	}
}

void Controller::drawScene(Camera &camera) {
	for (unsigned int x = 0; x < map.objects.size(); ++x) {
		for (unsigned int y = 0; y < map.objects[x].size(); ++y) {
			Entity *current_object = &map.objects[x][y];
			draw(current_object, camera);
		}
	}
}