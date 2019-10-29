#pragma once

#ifndef WORLDTIME_H
#define WORLDTIME_H

#include <chrono>

class WorldTime {
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> tStart;
	mutable float tPrev;
public:
	WorldTime();
	float getDeltaTime() const;
	float getElapasedTime() const;
};

class Timer {
private:
	WorldTime & time;
	float duration;
	float tStart;
	mutable float tCurrent;
	bool active;
public:
	Timer(WorldTime&);
	Timer(WorldTime&, float);
	void Start();
	void reset();
	void setDuration(float);
	bool isFinished() const;
	bool isActive() const;
};

#endif