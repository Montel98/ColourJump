#pragma once

#ifndef GAME_H
#define GAME_H

#include "Entity.h"
#include "LevelMap.h"
#include "Player.h"
#include "Camera.h"
#include "render.h"
#include "InputController.h"
#include "CollisionController.h"
#include "WorldTime.h"
#include <iostream>

class Controller {
private:
	levelMap &map;
	Renderer &renderer;
	Player &player;
	InputController &inputController;
	float dt;

public:
	Controller(levelMap&, Renderer&, Player&, InputController&);
	void updateStates(WorldTime &time, Camera &camera);
	void draw(Entity*, Camera&);
};

#endif // !GAME_H