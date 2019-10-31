#pragma once

#include "WorldTime.h"
#include <iostream>

WorldTime::WorldTime() : tStart(std::chrono::high_resolution_clock::now()), tPrev(0) {
	//
}

// Get the difference (dt) between the current and last recorded time
float WorldTime::getDeltaTime() const {
	float elapsed = getElapasedTime();
	float dt = elapsed - tPrev;
	tPrev = elapsed; // Save current time as previous for next call
	return dt;
}

// Get time passed since WorldTime was instantiated
float WorldTime::getElapasedTime() const {
	std::chrono::time_point<std::chrono::high_resolution_clock> tNow = std::chrono::high_resolution_clock::now();
	float elapsed = std::chrono::duration_cast<std::chrono::duration<float>>(tNow - tStart).count();
	return elapsed;
}

Timer::Timer(WorldTime &t) : duration(0), time(t), tStart(0), tCurrent(0), active(false) {
	//
}

Timer::Timer(WorldTime &t, float dur) : duration(dur), time(t), tStart(0), tCurrent(0), active(false) {
	//
}

void Timer::Start() {
	tStart = time.getElapasedTime();
	tCurrent = tStart;
	active = true;
}

bool Timer::isFinished() const {
	tCurrent = time.getElapasedTime();
	return ((tCurrent - tStart) > duration);
}

void Timer::reset() {
	tStart = time.getElapasedTime();
	tCurrent = tStart;
	active = false;
}

void Timer::setDuration(float newDuration) {
	duration = newDuration;
}

bool Timer::isActive() const {
	return active;
}