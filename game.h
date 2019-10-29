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
#include "round.h"
#include <iostream>
#include <map>
#include <string>

class Controller {
private:
	levelMap &map;
	Renderer &renderer;
	Player &player;
	WorldTime &time;
	InputController &inputController;
	Round round;
	float dt;
	int roundNumber;
	int blockVal;
	int prevBlockVal;

public:
	Controller(levelMap&, Renderer&, Player&, InputController&, WorldTime&);
	void updateStates(Camera &camera);
	void draw(Entity*, Camera&);
};

#endif // !GAME_H