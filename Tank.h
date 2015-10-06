// the tank that the player controls

#include "Object.h"
#include "EventKeyboard.h"
#include "EventMouse.h"
#include "Reticle.h"
#include "Position.h"

class Tank : public df::Object{

private:
	int move_slowdown;
	int move_countdown;
	int cannonCD;
	int gunCD;

	//handle keyboard events
	void kbd(const df::EventKeyboard *p_event_kbd);

	//hande step events
	void step();

	//handle mouse events
	void mouse(const df::EventMouse *p_event_mouse);

	//draw frames to match where the reticle is
	void draw(void);

	//fire machinegun at target
	void fireGun(df::Position target);

	//move along x or y axis
	void moveOnX(int dx);
	void moveOnY(int dy);

	//pointer to the reticle
	Reticle *p_reticle;

public:
	Tank();
	//~Tank();
	int eventHandler(const df::Event *p_e);
};