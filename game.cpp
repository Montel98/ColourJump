#pragma once

#include "game.h"

extern glm::vec3 normalForce(0.0f, 0.0f, 9.8f);
extern glm::vec3 gravity(0.0f, 0.0f, -9.8f);
extern glm::vec3 blue(0, 0, 1);
extern glm::vec3 green(0, 1, 0);
extern glm::vec3 red(1, 0, 0);
extern glm::vec3 yellow(1, 1, 0);
extern glm::vec3 aqua(0.0f, 1.0f, 0.78f);
extern glm::vec3 purple(0.55f, 0.0f, 1.0f);

extern std::map<int, glm::vec3>colours = { {0, glm::vec3(0, 0, 1)},
											{1, glm::vec3(0, 1, 0)},
											{2, glm::vec3(1, 0, 0)},
											{3, glm::vec3(1, 1, 0)},
											{4, glm::vec3(0.0f, 1.0f, 0.78f)},
											{5, glm::vec3(0.55f, 0.0f, 1.0f)},
											{6, glm::vec3(1.0f, 0.6f, 0.0f)},
											{7, glm::vec3(1.0f, 1.0f, 1.0f)} };

extern std::map<int, std::string>colourNames = { {0, "BLUE"},
												{1, "GREEN"},
												{2, "RED"},
												{3, "YELLOW"},
												{4, "AQUA"},
												{5, "PURPLE"},
												{6, "ORANGE"},
												{7, "WHITE"} };
												

void Controller::draw(Entity* entity, Camera& camera) {
	glm::vec3 position = entity->getPhysicsComponent().position;
	int id = entity->get_block_ID();
	renderer.render(position, colours[id], camera);

}

Controller::Controller(levelMap &mapLevel, Renderer &r, Player &p, InputController& ic, WorldTime& wt) : map(mapLevel), renderer(r), player(p), inputController(ic), time(wt), round(wt,4,4)  {
	roundNumber = 1;
	blockVal = -1;
}

void Controller::updateStates(Camera &camera) {

	float dt = time.getDeltaTime();
	inputController.ProcessInputs(dt);
	player.act();
	player.getPhysicsComponent().updateState(dt);
	player.updateSector();

	camera.setPosition(player.getPhysicsComponent().position);
	camera.setDirection(player.direction);

	round.updateState();
	if (round.getRoundNumber() == 0) {
		round.startRound();
		prevBlockVal = blockVal;
		blockVal = rand() % 8;
		std::cout << "ROUND " << round.getRoundNumber() << std::endl;
		std::cout << colourNames[blockVal] << std::endl;
	}
	else {
		if (round.isRoundFinished()) {
			round.startInter();
		}
		else if (round.isInterFinished()) {
			map.setRandomColours();
			round.startRound();
			prevBlockVal = blockVal;
			blockVal = rand() % 6;
			std::cout << "ROUND " << round.getRoundNumber() << std::endl;
			std::cout << colourNames[blockVal] << std::endl;
		}
	}

	//std::cout << "ACC: " << player.getPhysicsComponent().acceleration.x << "," << player.getPhysicsComponent().acceleration.y << "," << player.getPhysicsComponent().acceleration.z << std::endl;
	//std::cout << "VEL: " << player.getPhysicsComponent().velocity.x << "," << player.getPhysicsComponent().velocity.y << "," << player.getPhysicsComponent().velocity.z << std::endl;
	//std::cout << "POS: " << player.getPhysicsComponent().position.x << "," << player.getPhysicsComponent().position.y << "," << player.getPhysicsComponent().position.z << std::endl;

	for (unsigned int x = 0; x < map.objects.size(); ++x) {
		for (unsigned int y = 0; y < map.objects[x].size(); ++y) {
			Entity *currentObject = &map.objects[x][y];
			
			if (round.isActiveInter() && !currentObject->isGravityEnabled()) {
				if (currentObject->get_block_ID() != blockVal && !currentObject->isDestroyed) {
					currentObject->getPhysicsComponent().addComponent(&gravity);
					currentObject->gravityEnabled = true;
				}
			}
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
		else if (e.surfaceNormal.x == 1.0f || e.surfaceNormal.x == -1.0f) {
			player.getPhysicsComponent().velocity.x = 0.0f;
		}
		else if (e.surfaceNormal.y == 1.0f || e.surfaceNormal.y == -1.0f) {
			player.getPhysicsComponent().velocity.y = 0.0f;
		}
		col.popCollisionEvent();
	}

	if (player.isOnSurface) {
		player.getPhysicsComponent().removeComponent(&gravity);
		player.getPhysicsComponent().velocity.z = 0.0f;
	}
	else {
		player.getPhysicsComponent().addComponent(&gravity);
	}

	for (unsigned int x = 0; x < map.objects.size(); ++x) {
		for (unsigned int y = 0; y < map.objects[x].size(); ++y) {
			Entity *current_object = &map.objects[x][y];
			draw(current_object, camera);
		}
	}
}