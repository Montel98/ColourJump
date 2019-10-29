#pragma once

#include "Block.h"

Block::Block(int block_ID, float xPos, float yPos, float zPos, WorldTime &wt) : Entity(xPos, yPos, zPos), block_ID(block_ID), destructionTimer(wt) {
}

void Block::act() {
	if (isDestroyed) {
		if (destructionTimer.isActive() && destructionTimer.isFinished()) {
			getPhysicsComponent().addComponent(new glm::vec3(0.0f, 0.0f, -9.8f));
			destructionTimer.reset();
		}
		else if(!destructionTimer.isActive()) {
			destructionTimer.setDuration(0.5f);
			destructionTimer.Start();
		}
	}
}

void Block::destroy() {
	isDestroyed = true;
}

void Block::setColour(int colourValue) {
	block_ID = colourValue;
}

int Block::get_block_ID() const {
	return block_ID;
}