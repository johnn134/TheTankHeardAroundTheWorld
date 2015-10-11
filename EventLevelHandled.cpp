/*
* EventLevelHandled.cpp
*/

//Game Headers
#include "EventLevelHandled.h"

EventLevelHandled::EventLevelHandled(bool new_completed, int new_score) {
	setType(LEVELHANDLED_EVENT);
	completed = new_completed;
	score = new_score;
}

//return true if level was completed, false if failed
bool EventLevelHandled::levelCompleted() const {
	return completed;
}

//return the player's score from the level
int EventLevelHandled::getScore() const {
	return score;
}