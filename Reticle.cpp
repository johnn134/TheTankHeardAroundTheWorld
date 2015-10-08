#include "Reticle.h"
#include "EventMouse.h"
#include "GraphicsManager.h"
#include "utility.h"
#include "WorldManager.h"

//event handler
int Reticle::eventHandler(const df::Event *p_e) {

	if (p_e->getType() == df::A_MOUSE_EVENT) {
		const df::EventMouse *p_mouse_event = static_cast <const df::EventMouse *> (p_e);

		if (p_mouse_event->getMouseAction() == df::MOVED) {
			// Change location to new mouse position
			setPosition(viewToWorld(p_mouse_event->getMousePosition()));
			return 1;
		}
	}

	//ignore event
	return 0;
}

// Draw reticle on window.
void Reticle::draw() {
	df::GraphicsManager &graphics_manager = df::GraphicsManager::getInstance();
	graphics_manager.drawCh(getPosition(), RETICLE_CHAR, df::RED);
}

//Reticle constructor
Reticle::Reticle(){
	//needed managers
	df::WorldManager &world_manager = df::WorldManager::getInstance();

	//set type and solidness
	setType("Reticle");
	setSolidness(df::SPECTRAL);

	// Make Reticle in foreground
	setAltitude(df::MAX_ALTITUDE);

	//interested in mouse events
	registerInterest(df::A_MOUSE_EVENT);

	//start in center of screen
	int view_h = world_manager.getView().getHorizontal();
	int view_v = world_manager.getView().getVertical();
	df::Position pos(view_h / 2, view_v / 2);
	setPosition(df::viewToWorld(pos));
}