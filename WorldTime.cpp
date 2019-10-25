#pragma once

#include "WorldTime.h"

WorldTime::WorldTime() : tStart(std::chrono::high_resolution_clock::now()), tPrev(0) {

}

float WorldTime::getElapsedTime() {
	std::chrono::time_point<std::chrono::high_resolution_clock> tNow = std::chrono::high_resolution_clock::now();
	float elapsed = std::chrono::duration_cast<std::chrono::duration<float>>(tNow - tStart).count();
	float dt = elapsed - tPrev;
	tPrev = elapsed;
	return dt;
}