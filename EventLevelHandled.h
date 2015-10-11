//
// EventLevelHandled.h
//

#ifndef __EVENTLEVELHANDLED_H__
#define __EVENTLEVELHANDLED_H__

//Dragonfly Headers
#include "Event.h"

const std::string LEVELHANDLED_EVENT = "levelhandled";

class EventLevelHandled : public df::Event {
private:
	bool completed;
	int score;

public:
	EventLevelHandled(bool new_completed, int new_score);

	//return true if level was completed, false if failed
	bool levelCompleted() const;

	//return the player's score from the level
	int getScore() const;
};
#endif