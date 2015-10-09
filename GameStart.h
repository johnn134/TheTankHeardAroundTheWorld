//
// GameStart.h
//

#include "Music.h"
#include "ViewObject.h"

const float SCROLL_SPEED = 0.40f;

class GameStart : public df::ViewObject {

private:
	void start();

public:
	GameStart();
	int eventHandler(const df::Event *p_e);
	void draw();
};
