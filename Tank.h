// the tank that the player controls

#ifndef __TANK_H__
#define __TANK_H__

#include "Object.h"
#include "EventKeyboard.h"
#include "EventMouse.h"
#include "EventCollision.h"
#include "Reticle.h"
#include "Position.h"

const int TANK_HEALTH = 50;

class Tank : public df::Object{

private:
	int move_slowdown;
	int move_countdown;
	int cannonCD;
	int gunCD;
	bool wide_shot;
	bool cannon_CDR;
	bool angle_cannon;
	int wide_shotCD;
	int cannon_CDRCD;
	int angle_cannonCD;
	int health;
	int lives;
	
	//handle keyboard events
	void kbd(const df::EventKeyboard *p_event_kbd);

	//hande step events
	void step();

	//handle mouse events
	void mouse(const df::EventMouse *p_event_mouse);

	//handle collision events
	void hit(const df::EventCollision *p_event_collision);

	//draw frames to match where the reticle is
	void draw(void);

	//fire machinegun at target
	void fireGun(df::Position target);

	//fire main cannon
	void fireCannon();

	//move along x or y axis
	void moveOnX(int dx);
	void moveOnY(int dy);

	//pointer to the reticle
	Reticle *p_reticle;

public:
	Tank();
	~Tank();
	int eventHandler(const df::Event *p_e);
};
#endif