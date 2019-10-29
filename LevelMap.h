#pragma once

#ifndef LEVELMAP_H
#define LEVELMAP_H

#include <vector>
#include "Block.h"


class levelMap {
private:
	int dimension;
public:
	levelMap(int, WorldTime&);
	void setRandomColours();
	std::vector<std::vector<Block>> objects;
};

#endif