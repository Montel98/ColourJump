#include "Round.h"

Round::Round(WorldTime &wt, float startDur, float interDur) : roundTimer(wt), interTimer(wt), roundNumber(0) {
	interFinished = false;
	roundFinished = false;
	roundDuration = startDur;
	interDuration = interDur;
	roundTimer.setDuration(roundDuration);
	interTimer.setDuration(interDuration);
	durationFactor = 0.9;
}

bool Round::isActiveRound() {
	return activeRound;
}

bool Round::isActiveInter() {
	return activeInter;
}

bool Round::isRoundFinished() {
	return roundFinished;
}

bool Round::isInterFinished() {
	return interFinished;
}

void Round::startRound() {
	roundDuration *= durationFactor; // Shorten round
	roundTimer.setDuration(roundDuration);
	roundTimer.reset();
	roundTimer.Start();
	activeRound = true;
	roundFinished = false;
	interFinished = false;
	roundNumber++;
}

void Round::startInter() {
	interTimer.reset();
	interTimer.Start();
	activeInter = true;
	interFinished = false;
	roundFinished = false;
}

void Round::updateState() {
	if (roundTimer.isFinished() && roundTimer.isActive()) {
		roundTimer.reset();
		activeRound = false;
		roundFinished = true;
	}

	if (interTimer.isFinished() && interTimer.isActive()) {
		interTimer.reset();
		activeInter = false;
		interFinished = true;
	}
}

int Round::getRoundNumber() {
	return roundNumber;
}