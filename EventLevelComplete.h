//
// EventLevelComplete.h
//

#ifndef __EVENTLEVELCOMPLETE_H__
#define __EVENTLEVELCOMPLETE_H__

//Dragonfly Headers
#include "Event.h"

const std::string LEVELCOMPLETE_EVENT = "levelcomplete";

class EventLevelComplete : public df::Event {
public:
	EventLevelComplete();
};
#endif