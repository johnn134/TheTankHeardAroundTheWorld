//
// game.cpp
// 

// Engine includes.
#include "Color.h"
#include "GameManager.h"
#include "GraphicsManager.h"
#include "LogManager.h"
#include "Position.h"
#include "ResourceManager.h"
#include "utility.h"
#include "WorldManager.h"

//Game Headers
#include "Tank.h"
#include "SmallRock.h"
#include "MediumRock.h"
#include "LargeRock.h"

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

	// Set flush of logfile during development (when done, make false).
	log_manager.setFlush(true);

	// Load game resources.
	loadResources();
	
	// Show splash screen.
	//df::splash();

	ghm.setBackgroundColor(df::YELLOW);

	// Populate game world with some objects.
	populateWorld();

	//RUN GAME
	game_manager.run();

	// Shut everything down.
	game_manager.shutDown();
	
	return 0;
}

//loads sprites and other resources
void loadResources(void){
	df::LogManager &log_manager = df::LogManager::getInstance();
	df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
	// Load sprites
	if(!resource_manager.loadSprite("./sprites/player-tank-spr.txt", "player"))
		log_manager.writeLog("Successfully loaded player-tank-spr.txt.");
	if (!resource_manager.loadSprite("./sprites/small-rock-spr.txt", "smallrock"))
		log_manager.writeLog("Successfully loaded small-rock-spr.txt.");
	if (!resource_manager.loadSprite("./sprites/medium-rock-spr.txt", "mediumrock"))
		log_manager.writeLog("Successfully loaded medium-rock-spr.txt.");
	if (!resource_manager.loadSprite("./sprites/large-rock-spr.txt", "largerock"))
		log_manager.writeLog("Successfully loaded large-rock-spr.txt.");
}

// Populate world with some objects.
void populateWorld() {
	new Tank;
	df::Position pos1(df::WorldManager::getInstance().getBoundary().getHorizontal() / 4, df::WorldManager::getInstance().getBoundary().getVertical() / 2);
	df::Position pos2(df::WorldManager::getInstance().getBoundary().getHorizontal() / 2, df::WorldManager::getInstance().getBoundary().getVertical() / 2);
	df::Position pos3(df::WorldManager::getInstance().getBoundary().getHorizontal() * 3 / 4, df::WorldManager::getInstance().getBoundary().getVertical() / 2);
	df::Position pos4(df::WorldManager::getInstance().getBoundary().getHorizontal() / 4, df::WorldManager::getInstance().getBoundary().getVertical() / 4);
	df::Position pos5(df::WorldManager::getInstance().getBoundary().getHorizontal() / 2, df::WorldManager::getInstance().getBoundary().getVertical() / 4);
	df::Position pos6(df::WorldManager::getInstance().getBoundary().getHorizontal() * 3 / 4, df::WorldManager::getInstance().getBoundary().getVertical() / 4);
	new SmallRock(pos1);
	new MediumRock(pos2);
	new LargeRock(pos3);
}