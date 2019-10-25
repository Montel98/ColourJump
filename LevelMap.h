#pragma once

#ifndef LEVELMAP_H
#define LEVELMAP_H

#include <vector>
#include "Entity.h"


class levelMap {
private:
	int dimension;
public:
	levelMap(int);
	std::vector<std::vector<Entity*>> objects;
};

#endif