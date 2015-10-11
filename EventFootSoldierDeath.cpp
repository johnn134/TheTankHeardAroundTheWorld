/*
* EventFootSoldierDeath.cpp
*/

//Game Headers
#include "EventFootSoldierDeath.h"

EventFootSoldierDeath::EventFootSoldierDeath(df::Object *new_soldier) {
	setType(FOOT_SOLDIER_DEATH_EVENT);
	soldier = new_soldier;
}

df::Object *EventFootSoldierDeath::getSoldier() const {
	return soldier;
}