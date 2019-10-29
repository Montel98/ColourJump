#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player : public Entity {
public:
	float walkingSpeed;
	float runningSpeed;

	bool isWalking;
	bool isJumping;
	bool isOnSurface;

	int sectorX, sectorY;
	glm::vec3 direction; // direction player is facing
	glm::vec3 walkVector;
	virtual int get_block_ID() const { return 0; }
	virtual void act() {};
	Player(float, float, float);
	void updateSector();
	void initMotionSpeeds(float, float);
};

#endif