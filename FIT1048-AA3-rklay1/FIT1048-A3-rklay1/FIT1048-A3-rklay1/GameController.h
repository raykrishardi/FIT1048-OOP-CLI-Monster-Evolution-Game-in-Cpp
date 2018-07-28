#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "Player.h"
#include "BossMonster.h"
#include "Item.h"

using namespace std;

class GameController{
private:
	string gameMode; //variable that contains the selected game mode from the user
	bool gameOver; //variable that determines when the game is over
	
	static const int DUNGEON_ROW = 11; //ignore index 0
	static const int DUNGEON_COL = 21; //ignore index 0
	char dungeon[DUNGEON_ROW][DUNGEON_COL]; //2d array that represents the dungeon in normal mode
	GameObject* dungeonContent[DUNGEON_ROW][DUNGEON_COL]; //2d array that represents the content of the dungeon

	Player* player1; //variable that represents player1
	BossMonster* skeletor; //variable that represents boss monster ("skeletor")
	vector<Monster*> normalMonsters; //collection of normal monsters in the dungeon
	vector<Item*> items; //collection of items in the dungeon

	//player1 and skeletor positions in the dungeon
	int initialPlayer1PositionRow; //initial row position of player1 in the dungeon
	int initialPlayer1PositionCol; //initial column position of player1 in the dungeon
	int player1PositionRow; //player1 row position in the dungeon
	int player1PositionCol; //player1 column position in the dungeon
	int skeletorPositionRow; //skeletor row position in the dungeon
	int skeletorPositionCol; //skeletor column position in the dungeon

	string promptAndGetGameMode(); //prompt for game mode and return the selected game mode as string
	void promptAndSetPlayer1Name(); //prompt and set player1 name
	void playGameMode(string selectedGameMode); //play the game based on the selected game mode
	
	//dungeon
	void initialiseDungeon(); //initialise the dungeon for normal mode
	void initialiseDungeonContent(); //initialise the content of the dungeon 
	void displayDungeon(); //display the appropriate dungeon in normal mode
	void displayDungeonContent(); //display the appropriate dungeon in test mode

	//normal monsters
	void initialiseNormalMonsters(int monsterType); //initialise normal monsters in the dungeon

	//items
	void initialiseItems(int itemType); //initialise items in the dungeon

	//player movement
	string promptAndGetMovement(); //prompt for movement and return the selected movement as string
	void move(string movement); //move the player based on the selected movement

	//player interaction and response with different types of object
	void detectAndResponseToObject(); //response appropriately when detecting a particular object
	void itemPlayer(); //response appropriately when the player encounters an item in the dungeon
	void monsterPlayer(); //response appropriately when the player encounters a normal monster in the dungeon
	void friendlyMonster(Monster* friendlyMonster); //response appropriately when the player encounters a friendly normal monster in the dungeon
	void unfriendlyMonster(Monster* unfriendlyMonster); //response appropriately when the player encounters an unfriendly normal monster ("Octopod") in the dungeon
	void skeletorPlayer(); //response appropriately when the player encounters skeletor in the dungeon
public:
	GameController(); //default game controller constructor
	~GameController(); //default game controller destructor
	void playGame(); //function that starts the game
};

#endif