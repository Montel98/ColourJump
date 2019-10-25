#pragma once

#ifndef BLOCK_H
#define BLOCK_H

#include "Entity.h"

class Block : public Entity {
private:
	int block_ID;
	bool gravity_enabled;
	bool is_destroyed;
public:
	Block(int, float, float, float);
	virtual int get_block_ID() const { return block_ID; }
	virtual void act() {};
};

Block::Block(int block_ID, float xPos, float yPos, float zPos) : Entity(xPos, yPos, zPos), block_ID(block_ID) {
}

#endif // !BLOCK_H
