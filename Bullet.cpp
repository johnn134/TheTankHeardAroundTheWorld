#include "Bullet.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "LogManager.h"
#include "EventOut.h"
#include "EventCollision.h"
#include "EventView.h"
#include "GraphicsManager.h"

//bullet event handler
int Bullet::eventHandler(const df::Event *p_e) {
	//Out of Bounds Event
	if (p_e->getType() == df::OUT_EVENT) {
		out();
		return 1;
	}

	//collision detected
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision *p_collision_event = static_cast <const df::EventCollision *> (p_e);
		hit(p_collision_event);
		return 1;
	}

	//event ignored
	return 0;
}

//bullet is out of bounds, mark for deletion
void Bullet::out(){
	df::WorldManager &world_manager = df::WorldManager::getInstance();
	world_manager.markForDelete(this);
}

// If Bullet hits Saucer, mark Saucer and Bullet for deletion
void Bullet::hit(const df::EventCollision *p_collision_event) {

}

void Bullet::draw(void){
	df::GraphicsManager &graphics_manager = df::GraphicsManager::getInstance();
	graphics_manager.drawCh(getPosition(), BULLET_CHAR, df::RED);
}

//Bullet constructor
Bullet::Bullet(df::Position tank_pos){
	//needed managers
	df::LogManager &log_manager = df::LogManager::getInstance();
	df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
	df::WorldManager &world_manager = df::WorldManager::getInstance();

	//define type
	setType("Bullet");

	// Set starting location, based on hero's position passed in.
	setPosition(tank_pos);
}