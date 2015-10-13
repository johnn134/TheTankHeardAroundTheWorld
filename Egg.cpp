#include "Egg.h"
#include "EventStep.h"
#include "Jeep.h"
#include "Bomber.h"
#include "EnemyTank.h"
#include "Helicopter.h"
#include "WorldManager.h"
#include "GraphicsManager.h"

int Egg::eventHandler(const df::Event *p_e){
	//step events
	if (p_e->getType() == df::STEP_EVENT){
		step();
		return 1;
	}

	//event ignored
	return 0;
}

void Egg::step(){
	Object *p_o;
	df::Position alt_pos;

	//if on screen then hatch
	if (getPosition().getY() >= 0){
		if (eggType == "Jeep"){
			p_o = new Jeep(getPosition(), target);
			p_o->setYVelocity(getYVelocity() * 2);
		}
		else if (eggType == "Bomber")
			p_o = new Bomber(getPosition());
		else if (eggType == "Helicopter"){
			alt_pos.setXY(getPosition().getX(), getPosition().getY() + 1);
			p_o = new Helicopter(alt_pos);
		}
		else if (eggType == "EnemyTank"){
			alt_pos.setXY(getPosition().getX(), getPosition().getY() + 5);
			p_o = new EnemyTank(alt_pos, target);
		}

		df::WorldManager &world_manager = df::WorldManager::getInstance();
		world_manager.markForDelete(this);
	}
}

void Egg::draw(void){
	df::GraphicsManager &ghm = df::GraphicsManager::getInstance();
	ghm.drawCh(getPosition(), EGG_CHAR, df::BLACK);
}

Egg::Egg(std::string objType, df::Position eggPos, df::Object *new_player){
	eggType = objType;
	target = new_player;

	setSolidness(df::SPECTRAL);
	setPosition(eggPos);
}