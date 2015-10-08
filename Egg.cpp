#include "Egg.h"
#include "EventStep.h"
#include "Jeep.h"
#include "Bomber.h"
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
	//if on screen then hatch
	if (getPosition().getY() >= 0){
		if (eggType == "Jeep")
			new Jeep(getPosition(), target);
		else if (eggType == "Bomber")
			new Bomber(getPosition());
		else if (eggType == "Helicopter"){
			getPosition().setY(1);
			new Helicopter(getPosition());
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