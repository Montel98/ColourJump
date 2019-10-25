#pragma once

#ifndef INPUTCONTROLLER_H
#define INPUTCONTROLLER_H

#include "Player.h"
#include "Camera.h"
#include <Map>
#include <SDL.h>

class InputController {
private:
	Player &player;
	Camera &camera;
	bool release;
	const Uint8* state = SDL_GetKeyboardState(NULL);
	std::map<std::string, glm::vec3>forces;

public:
	InputController(Player&, Camera&);
	void ProcessInputs(float);
	glm::vec3 jumping;
	glm::vec3 vel;
	glm::vec3 lastDir;
	float vMag;
};

#endif