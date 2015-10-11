//
// EventFootSoldierDeath.h
//

#ifndef __EVENTFOOTSOLDIERDEATH_H__
#define __EVENTFOOTSOLDIERDEATH_H__

//Dragonfly Headers
#include "Event.h"
#include "Object.h"

const std::string FOOT_SOLDIER_DEATH_EVENT = "footsoldierdeath";

class EventFootSoldierDeath : public df::Event {
private:
	df::Object *soldier;

public:
	EventFootSoldierDeath(df::Object *new_soldier);

	df::Object *getSoldier() const;
};
#endif