//bullet that the player shoots

#include "Object.h"
#include "EventCollision.h"

#define BULLET_CHAR 'o'

class Bullet : public df::Object {

private:
	//out of bounds
	void out();

	//collide with something
	void hit(const df::EventCollision *p_collision_event);

public:
	Bullet(df::Position tank_pos);
	void draw(void);
	int eventHandler(const df::Event *p_e);
};