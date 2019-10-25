#pragma once

#ifndef COLLISIONBOX_H
#define COLLISIONBOX_H

#include <glm/gtc/matrix_transform.hpp>

class CollisionBox {
public:
	CollisionBox(glm::vec3, glm::vec3);
	float xMin, xMax, yMin, yMax, zMin, zMax; // plane boundaries
};

#endif