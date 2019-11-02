#pragma once

#ifndef BLOCK_H
#define BLOCK_H

#include "Entity.h"
#include "WorldTime.h"
#include <utility>
#include <string>
#include <map>

using std::map;
using std::pair;
using std::string;

class Block : public Entity {
private:
	int block_ID; // Colour id of the block
	Timer destructionTimer; // Timer to set delay before object destruction
public:
	static map<int, pair<glm::vec3, string>> colourValues;
	Block(int, float, float, float, WorldTime&);
	virtual int get_block_ID() const;
	virtual void act();
	void setColour(int);
	void destroy();
};

#endif // !BLOCK_H
