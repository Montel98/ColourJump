#pragma once

#include "CollisionBox.h"

CollisionBox::CollisionBox(glm::vec3 lc, glm::vec3 uc) {
	xMin = lc.x;
	xMax = uc.x;
	yMin = lc.y;
	yMax = uc.y;
	zMin = lc.z;
	zMax = uc.z;
}