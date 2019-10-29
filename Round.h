#pragma once

#ifndef ROUND_H
#define ROUND_H

#include "WorldTime.h"
#include <iostream>

class Round {
private:
	int roundNumber;
	bool activeRound;
	bool activeInter;
	bool roundFinished;
	bool interFinished;
	float roundDuration;
	float interDuration;
	float durationFactor;
public:
	Timer roundTimer;
	Timer interTimer;
	Round(WorldTime &wt, float startRoundDur, float interDur);
	bool isRoundFinished();
	bool isInterFinished();
	bool isActiveRound();
	bool isActiveInter();
	void startRound();
	void startInter();
	void updateState();
	int getRoundNumber();
};

#endif