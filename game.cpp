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

void Controller::draw(Entity* entity, Camera& camera) {
	glm::vec3 position = entity->getPhysicsComponent().position;
	int iD = entity->get_block_ID();
	switch (iD) {
	case 0:
		renderer.render(position, blue, camera);
		break;
	case 1:
		renderer.render(position, green, camera);
		break;
	case 2:
		renderer.render(position, red, camera);
		break;
	case 3:
		renderer.render(position, yellow, camera);
		break;
	case 4:
		renderer.render(position, red, camera);
		break;
	case 5:
		renderer.render(position, aqua, camera);
		break;
	case 6:
		renderer.render(position, purple, camera);
		break;
	default:
		renderer.render(position, blue, camera);
		break;
	}
}

Controller::Controller(levelMap &mapLevel, Renderer &r, Player &p, InputController& ic) : map(mapLevel), renderer(r), player(p), inputController(ic) {
}

void Controller::updateStates(WorldTime &time, Camera &camera) {
	float dt = time.getElapsedTime();
	inputController.ProcessInputs(dt);
	player.act();
	player.getPhysicsComponent().updateState(dt);
	player.updateSector();
	//std::cout << "Sector X: " << player.sectorX << " Sector Y: " << player.sectorY << std::endl;
	camera.setPosition(player.getPhysicsComponent().position);
	camera.setDirection(player.direction);
	//std::cout << "ACC: " << player.getPhysicsComponent().acceleration.x << "," << player.getPhysicsComponent().acceleration.y << "," << player.getPhysicsComponent().acceleration.z << std::endl;
	//std::cout << "VEL: " << player.getPhysicsComponent().velocity.x << "," << player.getPhysicsComponent().velocity.y << "," << player.getPhysicsComponent().velocity.z << std::endl;

	for (int x = 0; x < map.objects.size(); ++x) {
		for (int y = 0; y < map.objects[x].size(); ++y) {
			Entity *current_object = map.objects[x][y];
			current_object->act();
			current_object->getPhysicsComponent().updateState(dt);
		}
	}
	player.getPhysicsComponent().removeComponent(&gravity);
	CollisionController col(player);
	col.checkCollisions(map);
	player.isOnSurface = false;
	while (col.unhandledCollisions()) {
		CollisionEvent e = col.getCollisionEvent();
		std::cout << e.surfaceNormal.x << "," << e.surfaceNormal.y << "," << e.surfaceNormal.z << std::endl;
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

	for (int x = 0; x < map.objects.size(); ++x) {
		for (int y = 0; y < map.objects[x].size(); ++y) {
			Entity *current_object = map.objects[x][y];
			draw(current_object, camera);
		}
	}
}