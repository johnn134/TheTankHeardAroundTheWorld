//view object to show the score

#ifndef __SCORE_H__
#define __SCORE_H__

#include "ViewObject.h"
#include "Event.h"

#define SCORE_STRING "Score: "

class Score : public df::ViewObject{
private:

public:
	Score();
	int eventHandler(const df::Event *p_e);
};
#endif