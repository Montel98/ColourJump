#pragma once
#include "InputController.h"

InputController::InputController(Player &player, Camera &camera) : player(player), camera(camera), jumping(0.0f, 0.0f, 40.0), vel(0.0f), vMag(0.0f), lastDir(0.0f) {
	release = false;
}

void InputController::ProcessInputs(float dt) {
	SDL_Event userEvent;

	if (SDL_PollEvent(&userEvent)) {
	}

	vel.x = vel.y = vel.z = 0;

	float vMax = 2.0f;
	float acceleration = 8.0f;
	glm::vec3 dirW(player.direction.x, player.direction.y, 0);
	glm::vec3 dirS(-1 * player.direction.x, -1 * player.direction.y, 0);
	glm::vec3 dirD(glm::cross(glm::vec3(player.direction.x, player.direction.y, 0), glm::vec3(0.0f, 0.0f, 1.0f)));
	glm::vec3 dirA(glm::cross(glm::vec3(-1 * player.direction.x, -1 * player.direction.y, 0), glm::vec3(0.0f, 0.0f, 1.0f)));

	if (state[SDL_SCANCODE_LSHIFT]) {
		vMax = 3.0f;
	}

	if (state[SDL_SCANCODE_SPACE]) {
		if (!player.isJumping) {
			player.getPhysicsComponent().addComponent(&jumping);
			player.isJumping = true;
		}
	}

	if (player.isJumping && player.getPhysicsComponent().velocity.z >= 3) {
		player.getPhysicsComponent().velocity.z = 3;
		player.getPhysicsComponent().removeComponent(&jumping);
	}

	if (player.isJumping && player.isOnSurface) {
		player.isJumping = false;
	}

	//MOVE FORWARDS
	if (state[SDL_SCANCODE_W]) {
		vel.x += dirW.x;
		vel.y += dirW.y;
	}

	//MOVE BACKWARDS
	if (state[SDL_SCANCODE_S]) {
		vel.x += dirS.x;
		vel.y += dirS.y;
	}

	//MOVE RIGHT
	if (state[SDL_SCANCODE_D]) {
		vel.x += dirD.x;
		vel.y += dirD.y;
	}

	//MOVE LEFT
	if (state[SDL_SCANCODE_A]) {
		vel.x += dirA.x;
		vel.y += dirA.y;
	}

	if (vel.x != 0 && vel.y != 0) {
		vel.x = vel.x / glm::length(vel);
		vel.y = vel.y / glm::length(vel);
	}
	vMag += acceleration * dt;

	if (vMag <= vMax) {
		player.getPhysicsComponent().velocity.x = vel.x * vMag;
		player.getPhysicsComponent().velocity.y = vel.y * vMag;
	}
	else {
		player.getPhysicsComponent().velocity.x = vel.x * vMax;
		player.getPhysicsComponent().velocity.y = vel.y * vMax;
	}
	if (!state[SDL_SCANCODE_W] && !state[SDL_SCANCODE_A] && !state[SDL_SCANCODE_S] && !state[SDL_SCANCODE_D]) {
		release = true;
		vMag = 0.0f;
	}

	int x, y;
	Uint32 mouseState = SDL_GetRelativeMouseState(&x, &y);

	//look left/right
	glm::mat4 rot = glm::rotate(glm::mat4(1.0f), (-1 * x * 0.005f), glm::vec3(0, 0, 1));
	glm::vec4 bla1(player.direction, 1);
	bla1 = rot * bla1;

	player.direction.x = bla1.x;
	player.direction.y = bla1.y;
	player.direction.z = bla1.z;

	//look up/down
	glm::mat4 rot1 = glm::rotate(glm::mat4(1.0f), (-1 * y * 0.005f), glm::cross(player.direction, glm::vec3(0, 0, 1)));
	glm::vec4 bla(player.direction, 1);
	bla = rot1 * bla;

	player.direction.x = bla.x;
	player.direction.y = bla.y;
	player.direction.z = bla.z;
}