#pragma once

#include "LevelMap.h"
#include "block.h"

levelMap::levelMap(int dimension) {
	for (int x = 0; x < dimension; ++x) {
		std::vector<Entity*>newRow;
		objects.push_back(newRow);
		for (int y = 0; y < dimension; ++y) {
			int color = rand() % 7;
			objects[x].push_back(new Block(color, 0.5f * x, 0.5f * y, 0));
			if (color != 6) {
				//objects[x].back()->getPhysicsComponent().velocity = glm::vec3(0.0f, 0.0f, 10.0f);
				//objects[x].back()->getPhysicsComponent().addComponent(new glm::vec3(0.0f, 0.0f, -9.8f));
			}
		}
	}
}