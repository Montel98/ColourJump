#pragma once

#include "LevelMap.h"
#include "block.h"

#define TILE_SIZE 2

// Populate map with blocks
levelMap::levelMap(int size, WorldTime &wt) : dimension(size) {
	int colour;
	for (int x = 0; x < size; ++x) {
		std::vector<Block>newRow;
		objects.push_back(newRow);
		for (int y = 0; y < dimension; ++y) {
			colour = 0;
			objects[x].push_back(Block(colour, 0.5f * x, 0.5f * y, 0, wt));
		}
	}

	setRandomColours();
}

// Set colours of each tile
// Each tile has an area of TILE_SIZE * TILE_SIZE
void levelMap::setRandomColours() {
	for (int x = 0; x < dimension; x += TILE_SIZE) {
		for (int y = 0; y < dimension; y += TILE_SIZE) {
			int colour = rand() % 8;
			objects[x][y].setColour(colour);
			objects[x + 1][y].setColour(colour);
			objects[x][y + 1].setColour(colour);
			objects[x + 1][y + 1].setColour(colour);
		}
	}
}