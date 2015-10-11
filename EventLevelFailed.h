//
// EventLevelFailed.h
//

#ifndef __EVENTLEVELFAILED_H__
#define __EVENTLEVELFAILED_H__

//Dragonfly Headers
#include "Event.h"

const std::string LEVELFAILED_EVENT = "levelfailed";

class EventLevelFailed : public df::Event {
public:
	EventLevelFailed();
};
#endif