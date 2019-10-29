#pragma once

#include "player.h"

Player::Player(float xPos, float yPos, float zPos) : Entity(xPos, yPos, zPos), isWalking(false), isJumping(false), isOnSurface(false), direction(1.0f, 1.0f, 0.0f) {
	walkVector.x = 0.0f;
	walkVector.y = 0.0f;
	walkVector.z = 0.0f;
	getPhysicsComponent().addComponent(&walkVector);
	//state.velocity.z = 5.0f;
	//getPhysicsComponent().addComponent(&gravity);
	updateSector();
}

void Player::updateSector() {
	sectorX = floor(getPhysicsComponent().position.x / 0.5f);
	sectorY = floor(getPhysicsComponent().position.y / 0.5f);
}

void Player::initMotionSpeeds(float wSpeed, float rSpeed) {
	walkingSpeed = wSpeed;
	runningSpeed = rSpeed;
}