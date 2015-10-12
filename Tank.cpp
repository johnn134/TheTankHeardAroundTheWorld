#include "Tank.h"
#include "ResourceManager.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "GameManager.h"
#include "GraphicsManager.h"
#include "Line.h"
#include "EventStep.h"
#include "utility.h"
#include "PlayerGunShot.h"
#include "PlayerCannonShot.h"
#include "PowerUp.h"
#include "Health.h"
#include "Lives.h"
#include "EnemyGunShot.h"
#include "EventView.h"
#include "EventLevelFailed.h"

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
		return 1;
	}

	//catch collision events
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision *p_event_collision = static_cast <const df::EventCollision *> (p_e);

		hit(p_event_collision);
		return 1;
	}

	//event ignored
	return 0;
}

void Tank::hit(const df::EventCollision *p_event_collision){
	//hit a powerup
	if (p_event_collision->getObject2()->getType() == "PowerUp" || p_event_collision->getObject1()->getType() == "PowerUp"){
		// Play "power-up-get" sound.
		df::Sound *p_sound = df::ResourceManager::getInstance().getSound("power-up-get");
		p_sound->play();

		PowerUp *p_powerUp;

		if (p_event_collision->getObject2()->getType() == "PowerUp")
			p_powerUp = (PowerUp *)(p_event_collision->getObject2());
		else
			p_powerUp = (PowerUp *)(p_event_collision->getObject1());

		//get power up depending on powerup's ability
		if (p_powerUp->getAbility() == WIDE_SHOT){
			wide_shotCD = 500;
			wide_shot = true;
		}
		else if (p_powerUp->getAbility() == CANNON_CDR){
			cannon_CDRCD = 500;
			cannon_CDR = true;
		}
		else if (p_powerUp->getAbility() == ANGLE_CANNON){
			angle_cannonCD = 500;
			angle_cannon = true;
		}
		else if (p_powerUp->getAbility() == HEALTH_GET){
			health++;
		}

		//delete powerup
		df::WorldManager &wm = df::WorldManager::getInstance();
		wm.markForDelete(p_powerUp);
	}

	//1 damage sources
	if (p_event_collision->getObject2()->getType() == "EnemyGunShot" ||
		p_event_collision->getObject1()->getType() == "EnemyGunShot" ||
		p_event_collision->getObject2()->getType() == "SmallRock" ||
		p_event_collision->getObject1()->getType() == "SmallRock" ||
		p_event_collision->getObject2()->getType() == "BarbWire" ||
		p_event_collision->getObject1()->getType() == "BarbWire")
		health--;
	//2 damage sources
	if (p_event_collision->getObject2()->getType() == "EnemyRocketShot" ||
		p_event_collision->getObject1()->getType() == "EnemyRocketShot" ||
		p_event_collision->getObject2()->getType() == "SmallBuilding" ||
		p_event_collision->getObject1()->getType() == "SmallBuilding" ||
		p_event_collision->getObject2()->getType() == "DragonTooth" ||
		p_event_collision->getObject1()->getType() == "DragonTooth")
		health -= 2;
	//3 damage sources
	if (p_event_collision->getObject2()->getType() == "EnemyBombShot" ||
		p_event_collision->getObject1()->getType() == "EnemyBombShot" ||
		p_event_collision->getObject2()->getType() == "MediumRock" ||
		p_event_collision->getObject1()->getType() == "MediumRock" ||
		p_event_collision->getObject2()->getType() == "Trench" ||
		p_event_collision->getObject1()->getType() == "Trench" ||
		p_event_collision->getObject2()->getType() == "Jeep" ||
		p_event_collision->getObject1()->getType() == "Jeep")
		health -= 3;
	//4 damage sources
	if (p_event_collision->getObject2()->getType() == "LargeRock" ||
		p_event_collision->getObject1()->getType() == "LargeRock" ||
		p_event_collision->getObject2()->getType() == "MediumBuilding" ||
		p_event_collision->getObject1()->getType() == "MediumBuilding" ||
		p_event_collision->getObject2()->getType() == "Bunker" ||
		p_event_collision->getObject1()->getType() == "Bunker" ||
		p_event_collision->getObject2()->getType() == "TankTrap" ||
		p_event_collision->getObject1()->getType() == "TankTrap")
		health -= 4;
	//5 damage sources
	if (p_event_collision->getObject2()->getType() == "EnemyCannonShot" ||
		p_event_collision->getObject1()->getType() == "EnemyCannonShot" ||
		p_event_collision->getObject2()->getType() == "LargeBuilding" ||
		p_event_collision->getObject1()->getType() == "LargeBuilding" ||
		p_event_collision->getObject2()->getType() == "Landmine" ||
		p_event_collision->getObject1()->getType() == "Landmine")
		health -= 5;
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
			fireCannon();
			break;

	case df::Keyboard::T: //test enemy bullet
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
			new EnemyGunShot(getPosition());
		break;
	}
}

// Decrease rate restriction counters and send a scroll event to all other game objects if scrolling
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

	//power up cooldowns
	wide_shotCD--;
	if (wide_shotCD < 0){
		wide_shotCD = 0;
		wide_shot = false;
	}
	cannon_CDRCD--;
	if (cannon_CDRCD < 0){
		cannon_CDRCD = 0;
		cannon_CDR = false;
	}
	angle_cannonCD--;
	if (angle_cannonCD < 0){
		angle_cannonCD = 0;
		angle_cannon = false;
	}

	df::WorldManager &wm = df::WorldManager::getInstance();

	//am i dead?
	if (health < 1){
		//did i lose?
		if (lives < 1){
			//call for the game/level to be reset
			EventLevelFailed ev;
			wm.onEvent(&ev);
		}
		else{
			//invincibility frames
			health = 50;
			lives--;
			setSolidness(df::SPECTRAL);
			df::Position pos1(wm.getView().getHorizontal() / 2, wm.getView().getVertical() - 5);
			setPosition(viewToWorld(pos1));
			df::Position pos2;
			df::Position pos3;
			
			for (int i = 0; i <= 5000; i++){
				if (i % 10 == 0 || i <= 300 || (i % 10) + 1 == 0 || (i % 10) + 2 == 0){
					pos3.setXY(getPosition().getX(), getPosition().getY());
					pos2.setXY(-30, 0);
					setPosition(viewToWorld(pos2));
				}
				else if((i % 10) + 3 == 0){
					setPosition(viewToWorld(pos3));
				}
			}

			//make tank solid again
			setSolidness(df::HARD);
			df::Position pos(wm.getView().getHorizontal() / 2, wm.getView().getVertical() - 5);
			setPosition(viewToWorld(pos));
		}
	}

	//send health to the health view object and lives to lives view object
	df::EventView ev1(HEALTH_STRING, health, false);
	df::EventView ev2(LIVES_STRING, lives, false);
	wm.onEvent(&ev1);
	wm.onEvent(&ev2);
}

void Tank::mouse(const df::EventMouse *p_event_mouse){
	if (p_event_mouse->getMouseAction() == df::PRESSED){
		if (gunCD == 0){
			fireGun(p_reticle->getPosition());
		}
	}
}

void Tank::fireCannon(){
	if (cannonCD != 0)
		return;

	if (cannon_CDR)
		cannonCD = 30;
	else
		cannonCD = 60;

	// Play "cannonFire" sound.
	df::Sound *p_sound = df::ResourceManager::getInstance().getSound("cannon-shot");
	p_sound->play();
	
	PlayerCannonShot *p_PlayerCannonShot = new PlayerCannonShot(getPosition());
	PlayerCannonShot *p_PlayerCannonShot2 = new PlayerCannonShot(getPosition());
	PlayerCannonShot *p_PlayerCannonShot3 = new PlayerCannonShot(getPosition());

	if (angle_cannon){
		p_PlayerCannonShot2->setYVelocity(-2);
		p_PlayerCannonShot3->setYVelocity(-2);
		p_PlayerCannonShot2->setXVelocity(-1);
		p_PlayerCannonShot3->setXVelocity(1);
	}
	else{
		df::WorldManager &wm = df::WorldManager::getInstance();
		wm.markForDelete(p_PlayerCannonShot2);
		wm.markForDelete(p_PlayerCannonShot3);
	}

	p_PlayerCannonShot->setYVelocity(-2);
}

void Tank::fireGun(df::Position target){
	if (gunCD != 0)
		return;

	gunCD = 3;

	// Play "gunFire" sound.
	df::Sound *p_sound = df::ResourceManager::getInstance().getSound("gun-shot");
	p_sound->play();

	//create PlayerGunShot and send it flying
	PlayerGunShot *p_PlayerGunShot = new PlayerGunShot(getPosition());
	PlayerGunShot *p_PlayerGunShot2 = new PlayerGunShot(getPosition());
	PlayerGunShot *p_PlayerGunShot3 = new PlayerGunShot(getPosition());
	if (!wide_shot){
		df::WorldManager &wm = df::WorldManager::getInstance();
		wm.markForDelete(p_PlayerGunShot2);
		wm.markForDelete(p_PlayerGunShot3);
	}

	df::Line l(p_PlayerGunShot->getPosition(), target);
	int angle = df::angleBetween(l.getStart(), l.getEnd());
	if (angle >= 45 && angle < 135){
		if (wide_shot){
			df::Position p2(getPosition().getX() - 3, getPosition().getY() - 1);
			df::Position p3(getPosition().getX() + 3, getPosition().getY() - 1);
			p_PlayerGunShot2->setPosition(p2);
			p_PlayerGunShot3->setPosition(p3);
			p_PlayerGunShot2->setYVelocity(1);
			p_PlayerGunShot2->setXVelocity((float)(target.getX() - getPosition().getX()) / (float)(target.getY() - getPosition().getY()));
			p_PlayerGunShot3->setYVelocity(1);
			p_PlayerGunShot3->setXVelocity((float)(target.getX() - getPosition().getX()) / (float)(target.getY() - getPosition().getY()));
		}
		p_PlayerGunShot->setYVelocity(1);
		p_PlayerGunShot->setXVelocity((float)(target.getX() - getPosition().getX()) / (float)(target.getY() - getPosition().getY()));
		return;
	}
	else if (angle >= 135 && angle < 225){
		if (wide_shot){
			df::Position p2(getPosition().getX() + 1, getPosition().getY() - 2);
			df::Position p3(getPosition().getX() + 1, getPosition().getY() + 2);
			p_PlayerGunShot2->setPosition(p2);
			p_PlayerGunShot3->setPosition(p3);
			p_PlayerGunShot2->setXVelocity(-1);
			p_PlayerGunShot2->setYVelocity(-((float)(target.getY() - getPosition().getY()) / (float)(target.getX() - getPosition().getX())));
			p_PlayerGunShot3->setXVelocity(-1);
			p_PlayerGunShot3->setYVelocity(-((float)(target.getY() - getPosition().getY()) / (float)(target.getX() - getPosition().getX())));
		}
		p_PlayerGunShot->setXVelocity(-1);
		p_PlayerGunShot->setYVelocity(-((float)(target.getY() - getPosition().getY()) / (float)(target.getX() - getPosition().getX())));
		return;
	}
	else if (angle >= 225 && angle < 315){
		if (wide_shot){
			df::Position p2(getPosition().getX() - 3, getPosition().getY() + 1);
			df::Position p3(getPosition().getX() + 3, getPosition().getY() + 1);
			p_PlayerGunShot2->setPosition(p2);
			p_PlayerGunShot3->setPosition(p3);
			p_PlayerGunShot2->setYVelocity(-1);
			p_PlayerGunShot2->setXVelocity(-((float)(target.getX() - getPosition().getX()) / (float)(target.getY() - getPosition().getY())));
			p_PlayerGunShot3->setYVelocity(-1);
			p_PlayerGunShot3->setXVelocity(-((float)(target.getX() - getPosition().getX()) / (float)(target.getY() - getPosition().getY())));
		}
		p_PlayerGunShot->setYVelocity(-1);
		p_PlayerGunShot->setXVelocity(-((float)(target.getX() - getPosition().getX()) / (float)(target.getY() - getPosition().getY())));
		return;
	}
	else{
		if (wide_shot){
			df::Position p2(getPosition().getX() - 1, getPosition().getY() - 2);
			df::Position p3(getPosition().getX() - 1, getPosition().getY() + 2);
			p_PlayerGunShot2->setPosition(p2);
			p_PlayerGunShot3->setPosition(p3);
			p_PlayerGunShot2->setXVelocity(1);
			p_PlayerGunShot2->setYVelocity(((float)(target.getY() - getPosition().getY()) / (float)(target.getX() - getPosition().getX())));
			p_PlayerGunShot3->setXVelocity(1);
			p_PlayerGunShot3->setYVelocity(((float)(target.getY() - getPosition().getY()) / (float)(target.getX() - getPosition().getX())));
		}
		p_PlayerGunShot->setXVelocity(1);
		p_PlayerGunShot->setYVelocity((float)(target.getY() - getPosition().getY()) / (float)(target.getX() - getPosition().getX()));
	}
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
	if ((new_pos.getY() > 4) && (new_pos.getY() < world_manager.getView().getVertical() - 4))
		world_manager.moveObject(this, new_pos);
}

// Move left or right
void Tank::moveOnX(int dx) {
	// See if time to move
	if (move_countdown > 0)
		return;
	move_countdown = move_slowdown -1;

	// If stays on window, allow move
	df::Position new_pos(getPosition().getX() + dx, getPosition().getY());
	df::WorldManager &world_manager = df::WorldManager::getInstance();
	if ((new_pos.getX() > world_manager.getView().getCorner().getX() + 4) && 
		(new_pos.getX() < world_manager.getView().getCorner().getX() + world_manager.getView().getHorizontal() - 4))
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

Tank::~Tank(){
	df::GameManager &gm = df::GameManager::getInstance();
	//gm.setGameOver(true);
}

Tank::Tank(){
	df::WorldManager &world_manager = df::WorldManager::getInstance();
	df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
	df::LogManager &log_manager = df::LogManager::getInstance();

	// Link to "player" sprite
	df::Sprite *p_temp_sprite;
	p_temp_sprite = resource_manager.getSprite("playertank");
	if (!p_temp_sprite) {
		log_manager.writeLog("Tank::Tank(): Warning! Sprite '%s' not found", "playertank");
	}
	else {
		setSprite(p_temp_sprite);
		setSpriteSlowdown(0);
		setAltitude(3);
		//setTransparency();	   // Transparent sprite.
	}

	setType("Tank");
	df::Position pos(world_manager.getView().getHorizontal() / 2, world_manager.getView().getVertical() - 5);
	setPosition(viewToWorld(pos));

	registerInterest(df::KEYBOARD_EVENT);
	registerInterest(df::STEP_EVENT);
	registerInterest(df::A_MOUSE_EVENT);
	registerInterest(df::COLLISION_EVENT);

	setSolidness(df::HARD);

	//make aming reticle
	p_reticle = new Reticle();
	p_reticle->draw();

	move_slowdown = 2;
	move_countdown = move_slowdown;
	gunCD = 0;
	cannonCD = 0;
	wide_shot = false;
	cannon_CDR = false;
	angle_cannon = false;
	wide_shotCD = 0;
	cannon_CDRCD = 0;
	angle_cannonCD = 0;
	health = TANK_HEALTH;
	lives = 3;
}