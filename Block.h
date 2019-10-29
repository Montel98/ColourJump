#pragma once

#ifndef BLOCK_H
#define BLOCK_H

#include "Entity.h"
#include "WorldTime.h"

class Block : public Entity {
private:
	int block_ID;
	Timer destructionTimer;
public:
	Block(int, float, float, float, WorldTime&);
	virtual int get_block_ID() const;
	virtual void act();
	void setColour(int);
	void destroy();
};

#endif // !BLOCK_H
