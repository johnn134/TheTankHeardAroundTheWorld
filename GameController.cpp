/*
* GameController.cpp
*/

//Dragonfly Headers
#include "ObjectList.h"
#include "WorldManager.h"

//Game Headers
#include "Bomber.h"
#include "EnemyTank.h"
#include "EventKeyboard.h"
#include "FootSoldier.h"
#include "GameController.h"
#include "GameStart.h"
#include "Helicopter.h"
#include "Jeep.h"
#include "Mortar.h"
#include "RocketSoldier.h"

GameController::GameController() {

	setType("GameStart");

	// Put in center of screen.
	setLocation(df::CENTER_CENTER);

	// Register for "keyboard" event.
	registerInterest(df::KEYBOARD_EVENT);

	paused = false;
}

int GameController::eventHandler(const df::Event *p_e) {

	if (p_e->getType() == df::KEYBOARD_EVENT) {
		df::EventKeyboard *p_keyboard_event = (df::EventKeyboard *) p_e;
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
			switch (p_keyboard_event->getKey()) {
			case df::Keyboard::RETURN: 			// pause
				if (paused)
					pause();
				else
					play();
				break;
			default:
				break;
		}
		return 1;
	}
}

void GameController::pause() {
	df::WorldManager &world_manager = df::WorldManager::getInstance();

	df::ObjectList ol = world_manager.getAllObjects();
	df::ObjectListIterator li(&ol);
	for (li.first(); !li.isDone(); li.next()) {
		if (li.currentObject()->getType() != "Tank") {
			li.currentObject()->setYVelocity(0);
			if (li.currentObject()->getType() == "Bomber") {
				Bomber *p_ve = static_cast <Bomber *>(li.currentObject());
				p_ve->setPause(true);
			}
			else if (li.currentObject()->getType() == "EnemyTank") {
				EnemyTank *p_ve = static_cast <EnemyTank *>(li.currentObject());
				p_ve->setPause(true);
			}
			else if (li.currentObject()->getType() == "FootSoldier") {
				FootSoldier *p_ve = static_cast <FootSoldier *>(li.currentObject());
				p_ve->setPause(true);
			}
			else if (li.currentObject()->getType() == "Helicopter") {
				Helicopter *p_ve = static_cast <Helicopter *>(li.currentObject());
				p_ve->setPause(true);
			}
			else if (li.currentObject()->getType() == "Jeep") {
				Jeep *p_ve = static_cast <Jeep *>(li.currentObject());
				p_ve->setPause(true);
			}
			else if (li.currentObject()->getType() == "Mortar") {
				Mortar *p_ve = static_cast <Mortar *>(li.currentObject());
				p_ve->setPause(true);
			}
			else if (li.currentObject()->getType() == "RocketSoldier") {
				RocketSoldier *p_ve = static_cast <RocketSoldier *>(li.currentObject());
				p_ve->setPause(true);
			}
		}
	}

	paused = true;
}

void GameController::play() {
	df::WorldManager &world_manager = df::WorldManager::getInstance();

	df::ObjectList ol = world_manager.getAllObjects();
	df::ObjectListIterator li(&ol);
	for (li.first(); !li.isDone(); li.next()) {
		if (li.currentObject()->getType() != "Tank") {
			li.currentObject()->setYVelocity(SCROLL_SPEED);
			if (li.currentObject()->getType() == "Bomber") {
				Bomber *p_ve = static_cast <Bomber *>(li.currentObject());
				p_ve->setPause(true);
			}
			else if (li.currentObject()->getType() == "EnemyTank") {
				EnemyTank *p_ve = static_cast <EnemyTank *>(li.currentObject());
				p_ve->setPause(true);
			}
			else if (li.currentObject()->getType() == "FootSoldier") {
				FootSoldier *p_ve = static_cast <FootSoldier *>(li.currentObject());
				p_ve->setPause(true);
			}
			else if (li.currentObject()->getType() == "Helicopter") {
				Helicopter *p_ve = static_cast <Helicopter *>(li.currentObject());
				p_ve->setPause(true);
			}
			else if (li.currentObject()->getType() == "Jeep") {
				Jeep *p_ve = static_cast <Jeep *>(li.currentObject());
				p_ve->setPause(true);
			}
			else if (li.currentObject()->getType() == "Mortar") {
				Mortar *p_ve = static_cast <Mortar *>(li.currentObject());
				p_ve->setPause(true);
			}
			else if (li.currentObject()->getType() == "RocketSoldier") {
				RocketSoldier *p_ve = static_cast <RocketSoldier *>(li.currentObject());
				p_ve->setPause(true);
			}
		}
	}

	paused = false;
}

void GameController::draw() {

}