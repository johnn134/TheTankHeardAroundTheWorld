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
#include "GameController.h"

void loadResources(void);

int main(int argc, char *argv[]) {
	df::GraphicsManager &graphics_manager = df::GraphicsManager::getInstance();
	df::LogManager &log_manager = df::LogManager::getInstance();

	//Set the window properties
	//Original:
	//Pixels: 1024 x 768
	//Chars: 80 x 24
	//Char size: 12.8 x 32
	//
	//New: 497 x 915
	//Chars: 71 x 61
	//Char size: 7 x 15
	graphics_manager.setHorizontalPixels(497);
	graphics_manager.setHorizontal(71);
	graphics_manager.setVerticalPixels(915);
	graphics_manager.setVertical(61);

	// Start up Game Manager.
	df::GameManager &game_manager = df::GameManager::getInstance();
	if (game_manager.startUp())  {
		log_manager.writeLog("Error starting game manager!");
		game_manager.shutDown();
		return 0;
	}

	// Set world boundary to slightly overlap on the left, right, and bottom.
	df::WorldManager &world_manager = df::WorldManager::getInstance();
	df::Box boundary = world_manager.getBoundary();
	df::Position corner(0, 0);
	df::Box new_boundary(corner,
		boundary.getHorizontal() + 58,
		boundary.getVertical() + 30);
	world_manager.setBoundary(new_boundary);
	df::Box view = world_manager.getView();
	world_manager.setViewPosition(df::Position(new_boundary.getHorizontal() / 2, view.getVertical() / 2));

	// Set flush of logfile during development (when done, make false).
	log_manager.setFlush(true);

	// Load game resources.
	loadResources();

	// Show splash screen.
	//df::splash();

	graphics_manager.setBackgroundColor(df::YELLOW);

	//Create Game Controller
	new GameController();

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
	//Player
	if (!resource_manager.loadSprite("sprites/player-tank-spr.txt", "playertank"))
		log_manager.writeLog("Successfully loaded player-tank-spr.txt.");
	if (!resource_manager.loadSprite("sprites/player-gun-shot-spr.txt", "playergunshot"))
		log_manager.writeLog("Successfully loaded player-cannon-shot-spr.txt.");
	if (!resource_manager.loadSprite("sprites/player-cannon-shot-spr.txt", "playercannonshot"))
		log_manager.writeLog("Successfully loaded player-gun-shot-spr.txt.");
	//Obstacles
	if (!resource_manager.loadSprite("sprites/small-rock-spr.txt", "smallrock"))
		log_manager.writeLog("Successfully loaded small-rock-spr.txt.");
	if (!resource_manager.loadSprite("sprites/medium-rock-spr.txt", "mediumrock"))
		log_manager.writeLog("Successfully loaded medium-rock-spr.txt.");
	if (!resource_manager.loadSprite("sprites/large-rock-spr.txt", "largerock"))
		log_manager.writeLog("Successfully loaded large-rock-spr.txt.");
	if (!resource_manager.loadSprite("sprites/barb-wire-spr.txt", "barbwire"))
		log_manager.writeLog("Successfully loaded barb-wire-spr.txt.");
	if (!resource_manager.loadSprite("sprites/tank-trap-spr.txt", "tanktrap"))
		log_manager.writeLog("Successfully loaded tank-trap-spr.txt.");
	if (!resource_manager.loadSprite("sprites/dragon-tooth-spr.txt", "dragontooth"))
		log_manager.writeLog("Successfully loaded dragon-tooth-spr.txt.");
	if (!resource_manager.loadSprite("sprites/small-building-spr.txt", "smallbuilding"))
		log_manager.writeLog("Successfully loaded small-building-spr.txt.");
	if (!resource_manager.loadSprite("sprites/medium-building-spr.txt", "mediumbuilding"))
		log_manager.writeLog("Successfully loaded medium-building-spr.txt.");
	if (!resource_manager.loadSprite("sprites/large-building-spr.txt", "largebuilding"))
		log_manager.writeLog("Successfully loaded large-building-spr.txt.");
	//Visual Effects
	if (!resource_manager.loadSprite("sprites/small-explosion-spr.txt", "smallexplosion"))
		log_manager.writeLog("Successfully loaded small-explosion-spr.txt.");
	//Enemies
	if (!resource_manager.loadSprite("sprites/foot-soldier-spr.txt", "footsoldier"))
		log_manager.writeLog("Successfully loaded foot-soldier-spr.txt.");
	if (!resource_manager.loadSprite("sprites/rocket-soldier-spr.txt", "rocketsoldier"))
		log_manager.writeLog("Successfully loaded rocket-soldier-spr.txt.");
	if (!resource_manager.loadSprite("sprites/helicopter-spr.txt", "helicopter"))
		log_manager.writeLog("Successfully loaded helicopter-spr.txt.");
	if (!resource_manager.loadSprite("sprites/bomber-spr.txt", "bomber"))
		log_manager.writeLog("Successfully loaded bomber-spr.txt.");
	if (!resource_manager.loadSprite("sprites/enemy-tank-spr.txt", "enemytank"))
		log_manager.writeLog("Successfully loaded enemy-tank-spr.txt.");
	if (!resource_manager.loadSprite("sprites/jeep-spr.txt", "jeep"))
		log_manager.writeLog("Successfully loaded jeep-spr.txt.");
	if (!resource_manager.loadSprite("sprites/enemy-gun-shot-spr.txt", "enemygunshot"))
		log_manager.writeLog("Successfully loaded enemy-gun-shot-spr.txt.");
	if (!resource_manager.loadSprite("sprites/enemy-cannon-shot-spr.txt", "enemycannonshot"))
		log_manager.writeLog("Successfully loaded enemy-cannon-shot-spr.txt.");
	if (!resource_manager.loadSprite("sprites/enemy-rocket-shot-spr.txt", "enemyrocketshot"))
		log_manager.writeLog("Successfully loaded enemy-rocket-shot-spr.txt.");
	if (!resource_manager.loadSprite("sprites/enemy-bomb-shot-spr.txt", "enemybombshot"))
		log_manager.writeLog("Successfully loaded enemy-bomb-shot-spr.txt.");
	if (!resource_manager.loadSprite("sprites/landmine-spr.txt", "landmine"))
		log_manager.writeLog("Successfully loaded landmine-spr.txt.");
	if (!resource_manager.loadSprite("sprites/ho-chi-minh-spr.txt", "hochiminh"))
		log_manager.writeLog("Successfully loaded ho-chi-minh-spr.txt.");
	//Enemy Placements
	if (!resource_manager.loadSprite("sprites/mortar-spr.txt", "mortar"))
		log_manager.writeLog("Successfully loaded mortar-spr.txt.");

	//Load sounds
	if (!resource_manager.loadSound("sounds/gun-shot.wav", "gun-shot"))
		log_manager.writeLog("Successfully loaded gun-shot.wav.");
	if (!resource_manager.loadSound("sounds/gun-impact.wav", "gun-impact"))
		log_manager.writeLog("Successfully loaded gun-impact.wav.");
	if (!resource_manager.loadSound("sounds/cannon-shot.wav", "cannon-shot"))
		log_manager.writeLog("Successfully loaded cannon-shot.wav.");
	if (!resource_manager.loadSound("sounds/chopper-props.wav", "chopper-props"))
		log_manager.writeLog("Successfully loaded chopper-props.wav.");
}