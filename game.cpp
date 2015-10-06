//
// game.cpp
// 

// Engine includes.
#include "GameManager.h"
#include "LogManager.h"
#include "GraphicsManager.h"
#include "ResourceManager.h"
#include "utility.h"
#include "Color.h"

#include "Tank.h"

void loadResources(void);
void populateWorld(void);

int main(int argc, char *argv[]) {
	df::GraphicsManager &ghm = df::GraphicsManager::getInstance();
	df::LogManager &log_manager = df::LogManager::getInstance();

	// Start up Game Manager.
	df::GameManager &game_manager = df::GameManager::getInstance();
	if (game_manager.startUp())  {
		log_manager.writeLog("Error starting game manager!");
		game_manager.shutDown();
		return 0;
	}

	// Load game resources.
	loadResources();

	// Show splash screen.
	//df::splash();

	ghm.setBackgroundColor(df::YELLOW);

	// Populate game world with some objects.
	populateWorld();

	// Enable player to pause game.
	//new df::Pause(df::Keyboard::F10);

	// Set flush of logfile during development (when done, make false).
	log_manager.setFlush(true);

	//RUN GAME
	game_manager.run();

	// Shut everything down.
	game_manager.shutDown();
}

//loads sprites and other resources
void loadResources(void){
	// Load sprites
	df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
	resource_manager.loadSprite("sprites/player-tank-spr.txt", "player");
}

// Populate world with some objects.
void populateWorld() {
	new Tank;
}