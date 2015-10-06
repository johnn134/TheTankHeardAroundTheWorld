#include "Tank.h"
#include "ResourceManager.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "GameManager.h"
#include "GraphicsManager.h"
#include "Line.h"
#include "EventStep.h"
#include "utility.h"
#include "Bullet.h"

int Tank::eventHandler(const df::Event *p_e) {
	//catch keyboard events
	if (p_e->getType() == df::KEYBOARD_EVENT) {
		const df::EventKeyboard *p_keyboard_event = static_cast <const df::EventKeyboard *> (p_e);
		kbd(p_keyboard_event);
		return 1;
	}

	//catch step events
	if (p_e->getType() == df::STEP_EVENT){
		step();
		return 1;
	}

	//catch mouse events
	if (p_e->getType() == df::A_MOUSE_EVENT) {
		const df::EventMouse *p_mouse_event = static_cast <const df::EventMouse *> (p_e);

		mouse(p_mouse_event);
	}

	//event ignored
	return 0;
}

void Tank::kbd(const df::EventKeyboard *p_keyboard_event) {
	switch (p_keyboard_event->getKey()) {
	case df::Keyboard::Q:			// quit
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
			df::GameManager &gm = df::GameManager::getInstance();
			gm.setGameOver(true);
		}
		break;

	case df::Keyboard::W:			// up
		if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
			moveOnY(-1);
		break;

	case df::Keyboard::S:			// down
		if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
			moveOnY(+1);
		break;

	case df::Keyboard::A:			// left
		if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
			moveOnX(-1);
		break;

	case df::Keyboard::D:			// right
		if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
			moveOnX(+1);
		break;

	case df::Keyboard::SPACE:		// fire main cannon
		if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
			//fireCannon();
		break;
	}
}

// Decrease rate restriction counters
void Tank::step() {
	// Move countdown
	move_countdown--;
	if (move_countdown < 0)
		move_countdown = 0;

	// cannon cooldown
	cannonCD--;
	if (cannonCD < 0)
		cannonCD = 0;

	// machinegun cooldown
	gunCD--;
	if (gunCD < 0)
		gunCD = 0;
}

void Tank::mouse(const df::EventMouse *p_event_mouse){
	if (p_event_mouse->getMouseAction() == df::PRESSED){
		if (gunCD == 0){
			fireGun(p_reticle->getPosition());
		}
	}
}

void Tank::fireGun(df::Position target){
	//create bullet and send it flying
	Bullet *p_bullet = new Bullet(getPosition());
	df::Line l(p_bullet->getPosition(), target);
	p_bullet->setYVelocity();
}

// Move up or down
void Tank::moveOnY(int dy) {
	// See if time to move
	if (move_countdown > 0)
		return;
	move_countdown = move_slowdown;

	// If stays on window, allow move
	df::Position new_pos(getPosition().getX(), getPosition().getY() + dy);
	df::WorldManager &world_manager = df::WorldManager::getInstance();
	if ((new_pos.getY() > 4) && (new_pos.getY() < world_manager.getBoundary().getVertical() - 4))
		world_manager.moveObject(this, new_pos);
}

// Move left or right
void Tank::moveOnX(int dx) {
	// See if time to move
	if (move_countdown > 0)
		return;
	move_countdown = move_slowdown;

	// If stays on window, allow move
	df::Position new_pos(getPosition().getX() + dx, getPosition().getY());
	df::WorldManager &world_manager = df::WorldManager::getInstance();
	if ((new_pos.getX() > 4) && (new_pos.getX() < world_manager.getBoundary().getHorizontal() - 4))
		world_manager.moveObject(this, new_pos);
}

void Tank::draw(void){
	df::GraphicsManager &ghm = df::GraphicsManager::getInstance();
	int dir_frame = 0;
	df::Line l(getPosition(), p_reticle->getPosition());
	int angle = df::angleBetween(l.getStart(), l.getEnd());
	
	if ((angle <= 23 && angle >= 0) || (angle < 360 && angle > 338))
		dir_frame = 2;
	else if (angle > 23 && angle <= 68)
		dir_frame = 3;
	else if (angle > 68 && angle <= 113)
		dir_frame = 4;
	else if (angle > 113 && angle <= 158)
		dir_frame = 5;
	else if (angle > 158 && angle <= 203)
		dir_frame = 6;
	else if (angle > 203 && angle <= 248)
		dir_frame = 7;
	else if (angle > 248 && angle <= 293)
		dir_frame = 0;
	else if (angle > 293 && angle <= 338)
		dir_frame = 1;

	ghm.drawFrame(getPosition(), getSprite()->getFrame(dir_frame), true);
}

Tank::Tank(){
	df::WorldManager &world_manager = df::WorldManager::getInstance();
	df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
	df::LogManager &log_manager = df::LogManager::getInstance();

	// Link to "player" sprite
	df::Sprite *p_temp_sprite;
	p_temp_sprite = resource_manager.getSprite("player");
	if (!p_temp_sprite) {
		log_manager.writeLog("Tank::Tank(): Warning! Sprite '%s' not found", "player");
	}
	else {
		setSprite(p_temp_sprite);
		setSpriteSlowdown(0);
		setTransparency();	   // Transparent sprite.
	}

	setType("Player");
	df::Position pos(world_manager.getBoundary().getHorizontal() / 2, world_manager.getBoundary().getVertical() / 2);
	setPosition(pos);

	registerInterest(df::KEYBOARD_EVENT);
	registerInterest(df::STEP_EVENT);
	registerInterest(df::A_MOUSE_EVENT);

	//make aming reticle
	p_reticle = new Reticle();
	p_reticle->draw();

	move_slowdown = 2;
	move_countdown = move_slowdown;
}