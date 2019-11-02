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

// Link colour id with actual colour values and names
std::map<int, pair<glm::vec3, string>> Block::colourValues = { {0, pair<glm::vec3, string>(glm::vec3(0, 0, 1), "BLUE")},
											{1, pair<glm::vec3, string>(glm::vec3(0, 1, 0), "GREEN")},
											{2, pair<glm::vec3, string>(glm::vec3(1, 0, 0), "RED")},
											{3, pair<glm::vec3, string>(glm::vec3(1, 1, 0), "YELLOW")},
											{4, pair<glm::vec3, string>(glm::vec3(0.0f, 1.0f, 0.78f), "AQUA")},
											{5, pair<glm::vec3, string>(glm::vec3(0.55f, 0.0f, 1.0f), "PURPLE")},
											{6, pair<glm::vec3, string>(glm::vec3(1.0f, 0.6f, 0.0f), "ORANGE")},
											{7, pair<glm::vec3, string>(glm::vec3(1.0f, 1.0f, 1.0f), "WHITE")} };