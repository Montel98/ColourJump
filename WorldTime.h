#pragma once

#ifndef WORLDTIME_H
#define WORLDTIME_H

#include <chrono>

class WorldTime {
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> tStart;
	float tPrev;
public:
	WorldTime();
	float getElapsedTime();
};

#endif