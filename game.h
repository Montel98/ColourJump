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
#include "CubeRenderer.h"
#include "WorldTime.h"
#include "round.h"
#include <iostream>
#include <map>
#include <string>

class Controller {
private:
	levelMap &map;
	Player &player;
	WorldTime &time;
	InputController &inputController;
	SceneRenderer scene;
	CubeRenderer cubeRenderer;
	Round round;
	float dt;
	int roundNumber;
	int blockVal;
	int prevBlockVal;

public:
	Controller(levelMap&, Player&, InputController&, WorldTime&);
	void updateStates(Camera &camera);
	void draw(Entity*, Camera&);
	void updateRound();
	void checkCollisions();
	void drawScene(Camera&);
	void updateMap();
};

#endif // !GAME_H