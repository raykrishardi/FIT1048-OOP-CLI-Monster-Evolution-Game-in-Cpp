#include "GameController.h"
#include <iostream>
#include <time.h>
#include <algorithm>

//-------------------------------------
//				Constructor
//-------------------------------------

//game controller default constructor that performs:
//1. allow for random number generation with srand(time(NULL))
//2. create and assign the object for player1 and skeletor
//3. initialise the dungeon and the content of the dungeon
GameController::GameController(){
	srand(time(NULL));
	player1 = new Player("player1");
	skeletor = new BossMonster();
	initialiseDungeon();
	initialiseDungeonContent();
}

//-------------------------------------
//				Destructor
//-------------------------------------

//when the destructor is called:
//1. delete player and skeletor object
//2. delete all monster object in the collection of normal monsters
//3. delete all item object in the collection of items
GameController::~GameController(){
	delete player1;
	delete skeletor;

	for (int i = 0; i < normalMonsters.size(); i++)
		delete normalMonsters[i];

	for (int i = 0; i < items.size(); i++)
		delete items[i];
}

//---------------------------------------
//				Helper functions
//---------------------------------------

//function that prompts for game mode and return the selected game mode as string
string GameController::promptAndGetGameMode(){
	bool validGameMode = false;

	//keep asking for valid game mode if it is not valid
	//game mode must be either "1" or "2"
	//"1" refers to normal mode and "2" refers to test mode
	while (!validGameMode){
		cout << "Monster Evolution!" << endl;
		cout << "Select Mode:" << endl;
		cout << "1. Normal Mode" << endl;
		cout << "2. Test Mode" << endl;
		cout << "Select option: ";
		getline(cin, gameMode);
		if (gameMode == "1" || gameMode == "2")
			validGameMode = true;
		else {
			cout << "Invalid game mode option! Try again...";
			system("timeout 3"); system("cls");
		}
	}

	return gameMode;
}

//response appropriately when the player encounters an item in the dungeon
void GameController::itemPlayer(){
	//downcast the game object pointer to item pointer
	Item* item = static_cast<Item*>(dungeonContent[player1PositionRow][player1PositionCol]);
	//determine the item type
	ItemType itemType = static_cast<ItemType>(item->getType());

	cout << "You found '" << item->getTypeAsString() << "', it will increase your health by " << item->getHealthModifier() << endl;

	//check the item type
	if (itemType == Cherry){
		//if the item type is "Cherry" then increase player health by 1
		player1->setHealth(player1->getHealth() + 1);
	}
	else if (itemType == Apple){
		//if the item type is "Apple" then increase player health by 2
		player1->setHealth(player1->getHealth() + 2);
	}
	else if (itemType == Melon){
		//if the item type is "Melon" then increase player health by 3
		player1->setHealth(player1->getHealth() + 3);
	}

	//delete the item object
	delete dungeonContent[player1PositionRow][player1PositionCol];
	//remove item from collection of items in the dungeon
	items.erase(find(items.begin(), items.end(), item));
	system("pause");
}

//response appropriately when the player encounters a friendly normal monster in the dungeon
void GameController::friendlyMonster(Monster* friendlyMonster){
	//generate player random number between 1 to 6
	int playerRandomNumber = 1 + rand() % 6;

	cout << "Attempting to capture..." << endl;
	cout << "Player random number: " << playerRandomNumber << endl;
	cout << "Monster skill level: " << friendlyMonster->getSkillLevel() << endl;

	//if the player random number is greater than or equal to the friendly monster skill level then the friendly monster is captured
	//else the friendly monster fled
	if (playerRandomNumber >= friendlyMonster->getSkillLevel()){
		cout << "Wild '" << friendlyMonster->getTypeAsString() << "' captured!" << endl;
		player1->addMonster(friendlyMonster); //add monster to player's collection of captured monster
	}
	else{
		cout << "Wild '" << friendlyMonster->getTypeAsString() << "' fled!" << endl;
	}
	//remove monster from collection of normal monsters in the dungeon
	normalMonsters.erase(find(normalMonsters.begin(), normalMonsters.end(), friendlyMonster));
	system("pause");
}

//response appropriately when the player encounters an unfriendly normal monster ("Octopod") in the dungeon
void GameController::unfriendlyMonster(Monster* unfriendlyMonster){
	int playerRandomNumber;
	int totalPlayerSkillLevel;

	int monsterRandomNumber;
	int totalMonsterSkillLevel;

	int round = 0;
	bool stop = false;

	cout << "Fighting the 'Octopod'...";
	system("timeout 3"); 

	//keep looping until either player or "Octopod" lose the fight (health = 0)
	while (!stop){
		system("cls");

		playerRandomNumber = 1 + rand() % 6; //generate player random number between 1 to 6
		totalPlayerSkillLevel = player1->getSkillLevel() + playerRandomNumber; //calculate the total skill level for the particular round

		monsterRandomNumber = 1 + rand() % 6; //generate monster random number between 1 to 6
		totalMonsterSkillLevel = unfriendlyMonster->getSkillLevel() + monsterRandomNumber; //calculate the total skill level for the particular round
		
		round++;
		cout << "Round: " << round << endl << endl;
		cout << "Player health: " << player1->getHealth() << endl;
		cout << "Monster health: " << unfriendlyMonster->getHealth() << endl;
		cout << "Total player skill level: " << totalPlayerSkillLevel << endl;
		cout << "Total monster skill level: " << totalMonsterSkillLevel << endl << endl;


		//determine the winner/loser of the round and decrease the health accordingly
		if (totalPlayerSkillLevel == totalMonsterSkillLevel){
			cout << "Draw!" << endl;
		}
		else if (totalPlayerSkillLevel > totalMonsterSkillLevel){
			cout << "'" << player1->getName() << "' wins the round!" << endl;
			unfriendlyMonster->setHealth(unfriendlyMonster->getHealth() - 1);
		}
		else if (totalPlayerSkillLevel < totalMonsterSkillLevel){
			cout << "'" << unfriendlyMonster->getTypeAsString() << "' wins the round!" << endl;
			player1->setHealth(player1->getHealth() - 1);
		}


		//determine the loser of the fight
		if (player1->getHealth() == 0){
			stop = true;
			cout << "'" << player1->getName() << "' lose the fight..." << endl;
			gameOver = true; //if the player lose the fight then the game is over
		}
		else if (unfriendlyMonster->getHealth() == 0){
			stop = true;
			cout << "Wild '" << unfriendlyMonster->getTypeAsString() << "' defeated!" << endl;
			delete dungeonContent[player1PositionRow][player1PositionCol]; //delete the monster object
			//remove monster from collection of normal monsters in the dungeon
			normalMonsters.erase(find(normalMonsters.begin(), normalMonsters.end(), unfriendlyMonster));
		}
		system("pause");
	}
}

//response appropriately when the player encounters a normal monster in the dungeon
void GameController::monsterPlayer(){
	//downcast the game object pointer to monster pointer
	Monster* monster = static_cast<Monster*>(dungeonContent[player1PositionRow][player1PositionCol]);
	//determine the monster type
	MonsterType monsterType = static_cast<MonsterType>(monster->getType());

	cout << "A wild '" << monster->getTypeAsString() << "' appeared!" << endl;

	//check whether the monster type is friendly or unfriendly and call the appropriate function
	if (monsterType == Bugbear || monsterType == Platypie || monsterType == Emoo){
		friendlyMonster(monster);
	}
	else if (monsterType == Octopod){
		unfriendlyMonster(monster);
	}
}

//response appropriately when the player encounters skeletor in the dungeon
void GameController::skeletorPlayer(){
	//if the player does not have any evolved monster then the player will return to the starting position
	if (player1->getEvolvedMonsterType() == "None"){
		player1PositionRow = initialPlayer1PositionRow;
		player1PositionCol = initialPlayer1PositionCol;
		cout << "You need an evolved monster to fight the 'Skeletor'!" << endl;
		cout << "Going back to the starting position..." << endl;
		system("pause");
	}
	//if the player has an evolved monster
	else{
		int playerRandomNumber;
		int totalEvolvedMonsterSkillLevel;
		EvolvedMonster* playerEvolvedMonster = player1->getPlayerEvolvedMonster(); //get a pointer to the player's evolved monster
		int evolvedMonsterSkillLevel = playerEvolvedMonster->getSkillLevel(); //get the player's evolved monster skill level
		int evolvedMonsterSpecialPowerModifier = playerEvolvedMonster->getSpecialPowerModifier(); //get the player's evolved monster special power modifier

		int monsterRandomNumber;
		int totalMonsterSkillLevel;

		int round = 0;
		bool stop = false;

		cout << "Fighting the 'Skeletor'...";
		system("timeout 3");

		while (!stop){
			system("cls");
			playerRandomNumber = 1 + rand() % 6; //generate player random number between 1 to 6
			totalEvolvedMonsterSkillLevel = evolvedMonsterSkillLevel + playerRandomNumber + evolvedMonsterSpecialPowerModifier; //calculate the total skill level for the particular round

			monsterRandomNumber = 1 + rand() % 6; //generate monster random number between 1 to 6
			totalMonsterSkillLevel = skeletor->getSkillLevel() + monsterRandomNumber + skeletor->getSpecialPowerModifier(); //calculate the total skill level for the particular round

			round++;
			cout << "Round: " << round << endl << endl;
			cout << "Evolved '" << playerEvolvedMonster->getTypeAsString() << "' health: " << playerEvolvedMonster->getHealth() << endl;
			cout << "'Skeletor' health: " << skeletor->getHealth() << endl;
			cout << "Total evolved '" << playerEvolvedMonster->getTypeAsString() << "' skill level: " << totalEvolvedMonsterSkillLevel << endl;
			cout << "Total 'Skeletor' skill level: " << totalMonsterSkillLevel << endl << endl;


			//determine the winner/loser of the round and decrease the health accordingly
			if (totalEvolvedMonsterSkillLevel == totalMonsterSkillLevel){
				cout << "Draw!" << endl;
			}
			else if (totalEvolvedMonsterSkillLevel > totalMonsterSkillLevel){
				cout << "Evolved '" << playerEvolvedMonster->getTypeAsString() << "' wins the round!" << endl;
				skeletor->setHealth(skeletor->getHealth() - 1);
			}
			else if (totalEvolvedMonsterSkillLevel < totalMonsterSkillLevel){
				cout << "'" << skeletor->getTypeAsString() << "' wins the round!" << endl;
				playerEvolvedMonster->setHealth(playerEvolvedMonster->getHealth() - 1);
			}


			//determine the loser of the fight and the game is over
			if (playerEvolvedMonster->getHealth() == 0){
				stop = true;
				cout << "Evolved '" << playerEvolvedMonster->getTypeAsString() << "' lose the fight..." << endl;
				gameOver = true;
			}
			else if (skeletor->getHealth() == 0){
				stop = true;
				cout << "'" << skeletor->getTypeAsString() << "' defeated!" << endl;
				gameOver = true;
			}
			system("pause");
		}
	}

}

//response appropriately when detecting a particular object
void GameController::detectAndResponseToObject(){
	ObjectType dungeonContentObjectType;
	
	//determine whether the spot has an object or not
	if (dungeonContent[player1PositionRow][player1PositionCol] != NULL){
		//get the object type if there is an object
		dungeonContentObjectType = dungeonContent[player1PositionRow][player1PositionCol]->getObjectType();
		//response appropriately to different types of object
		if (dungeonContentObjectType == ObjectType::Item){
			itemPlayer();
		}
		else if (dungeonContentObjectType == ObjectType::Monster){
			monsterPlayer();
		}
		else if (dungeonContentObjectType == ObjectType::BossMonster){
			skeletorPlayer();
		}
	}

	//put player1 in the appropriate spot
	dungeonContent[player1PositionRow][player1PositionCol] = player1;
}

//prompt for movement and return the selected movement as string
string GameController::promptAndGetMovement(){
	bool validMovement = false;
	string movement;

	//keep asking for valid movement if it is not valid
	//movement must be either u/d/l/r (up/down/left/right)
	while (!validMovement){
		cout << "Move[u/d/l/r]: ";
		getline(cin, movement);
		if (movement == "u" || movement == "d" || movement == "l" || movement == "r")
			validMovement = true;
		else
			cout << "Invalid movement! Try again..." << endl;
	}

	return movement;
}

//move the player based on the selected movement
void GameController::move(string movement){
	bool validMove = false;

	//keep asking for valid move if it is not valid
	//player must not move outside the dungeon
	while (!validMove){
		//player chose to move "up"
		if (movement == "u"){
			//check whether player is moving outside the dungeon
			if (player1PositionRow == 1){
				cout << "Moving out of the dungeon! Try another move..." << endl;
				movement = promptAndGetMovement();
			}
			else{
				validMove = true;
				dungeonContent[player1PositionRow][player1PositionCol] = NULL; //mark the current position as "NULL"
				player1PositionRow--; //move to the appropriate position in the dungeon
				detectAndResponseToObject();
			}	
		}
		//player chose to move "down"
		else if (movement == "d"){
			//check whether player is moving outside the dungeon
			if (player1PositionRow == 10){
				cout << "Moving out of the dungeon! Try another move..." << endl;
				movement = promptAndGetMovement();
			}
			else{
				validMove = true;
				dungeonContent[player1PositionRow][player1PositionCol] = NULL; //mark the current position as "NULL"
				player1PositionRow++; //move to the appropriate position in the dungeon
				detectAndResponseToObject();
			}
		}
		//player chose to move "left"
		else if (movement == "l"){
			//check whether player is moving outside the dungeon
			if (player1PositionCol == 1){
				cout << "Moving out of the dungeon! Try another move..." << endl;
				movement = promptAndGetMovement();
			}
			else{
				validMove = true;
				dungeonContent[player1PositionRow][player1PositionCol] = NULL; //mark the current position as "NULL"
				player1PositionCol--; //move to the appropriate position in the dungeon
				detectAndResponseToObject();
			}
		}
		//player chose to move "right"
		else if (movement == "r"){
			//check whether player is moving outside the dungeon
			if (player1PositionCol == 20){
				cout << "Moving out of the dungeon! Try another move..." << endl;
				movement = promptAndGetMovement();
			}
			else{
				validMove = true;
				dungeonContent[player1PositionRow][player1PositionCol] = NULL; //mark the current position as "NULL"
				player1PositionCol++; //move to the appropriate position in the dungeon
				detectAndResponseToObject();
			}
		}
	}
}

//function that prompts and sets player1 name
void GameController::promptAndSetPlayer1Name(){
	bool validPlayer1Name = false;
	string tmpName;

	//keep asking for valid name if it is not valid (name must consist of either upper/lower case alphabet letter)
	while (!validPlayer1Name){
		cout << "Enter Player1 Name: ";
		getline(cin, tmpName);
		if (player1->setName(tmpName))
			validPlayer1Name = true;
		else
			cout << "Invalid player name! Try again..." << endl;
	}
}

//initialise normal monsters in the dungeon
void GameController::initialiseNormalMonsters(int monsterType){
	int numberOfNormalMonster = 0;
	const int MAX_NUMBER_OF_NORMAL_MONSTER = 10;

	int randomRow;
	int randomCol;

	//keep looping until the number of monster for the particular type is 10
	while (numberOfNormalMonster != MAX_NUMBER_OF_NORMAL_MONSTER){
		//generate random row and column for the monster
		randomRow = 1 + rand() % (DUNGEON_ROW - 1);
		randomCol = 1 + rand() % (DUNGEON_COL - 1);

		//if the spot is empty (NULL) then allocate the spot for monster and add the monster to the collection of normal monsters
		//increment the number of monster for the particular type accordingly
		if (dungeonContent[randomRow][randomCol] == NULL){
			Monster* tmpMonster = new Monster(monsterType);
			numberOfNormalMonster++;
			normalMonsters.push_back(tmpMonster);
			dungeonContent[randomRow][randomCol] = tmpMonster;
		}
	}
}

//initialise items in the dungeon
void GameController::initialiseItems(int itemType){
	int numberOfItem = 0;
	const int MAX_NUMBER_OF_ITEM = 2 + rand() % 2; //the max number of item is a random number either 2 or 3

	int randomRow;
	int randomCol;

	//keep looping until the number of item for the particular type is equal to the max number of item (either 2 or 3)
	while (numberOfItem != MAX_NUMBER_OF_ITEM){
		//generate random row and column for the item
		randomRow = 1 + rand() % (DUNGEON_ROW - 1);
		randomCol = 1 + rand() % (DUNGEON_COL - 1);

		//if the spot is empty (NULL) then allocate the spot for item and add the item to the collection of items
		//increment the number of item for the particular type accordingly
		if (dungeonContent[randomRow][randomCol] == NULL){
			Item* tmpItem = new Item(itemType);
			numberOfItem++;
			items.push_back(tmpItem);
			dungeonContent[randomRow][randomCol] = tmpItem;
		}
	}
}

//initialise the dungeon for normal mode
void GameController::initialiseDungeon(){
	//initialise all elements to '-'
	for (int row = 1; row < DUNGEON_ROW; row++){
		for (int col = 1; col < DUNGEON_COL; col++){
			dungeon[row][col] = '-';
		}
	}
}

//initialise the content of the dungeon 
void GameController::initialiseDungeonContent(){
	//initialise all elements to NULL
	for (int row = 1; row < DUNGEON_ROW; row++){
		for (int col = 1; col < DUNGEON_COL; col++){
			dungeonContent[row][col] = NULL;
		}
	}

	//initialise random position for player1 in the dungeon left hand wall
	player1PositionRow = 1 + rand() % (DUNGEON_ROW - 1);
	initialPlayer1PositionRow = player1PositionRow;
	player1PositionCol = 1;
	initialPlayer1PositionCol = player1PositionCol;
	dungeonContent[player1PositionRow][player1PositionCol] = player1;

	//initialise random position for boss monster ("skeletor") in the dungeon right hand wall
	skeletorPositionRow = 1 + rand() % (DUNGEON_ROW - 1);
	skeletorPositionCol = DUNGEON_COL - 1;
	dungeonContent[skeletorPositionRow][skeletorPositionCol] = skeletor;

	//initialise random position for normal monsters in the dungeon
	//bugbear, platypie, emoo, octopod
	for (int monsterType = 1; monsterType <= 4; monsterType++)
		initialiseNormalMonsters(monsterType);

	//initialise random position for items in the dungeon
	//cherry, apple, melon
	for (int itemType = 1; itemType <= 3; itemType++)
		initialiseItems(itemType);
}

//display the appropriate dungeon in normal mode
//show the position of player1 with "P1"
void GameController::displayDungeon(){
	for (int row = 1; row < DUNGEON_ROW; row++){
		for (int col = 1; col < DUNGEON_COL; col++){
			if (dungeonContent[row][col] == player1)
				cout << "P1" << "  ";
			else
				cout << dungeon[row][col] << "   ";
		}
		cout << endl;
	}
}

//display the appropriate dungeon in test mode
//no object (NULL) is displayed with '-'
//player1 is displayed with "P1"
//skeletor is displayed with "S"
//bugbear is displayed with "B"
//platypie is displayed with "P"
//emoo is displayed with "E"
//octopod is displayed with "O"
//cherry is displayed with "C"
//apple is displayed with "A"
//melon is displayed with "M"
void GameController::displayDungeonContent(){
	for (int row = 1; row < DUNGEON_ROW; row++){
		for (int col = 1; col < DUNGEON_COL; col++){
			if (dungeonContent[row][col] == NULL)
				cout << '-' << "   ";
			else if (dungeonContent[row][col] == player1)
				cout << "P1" << "  ";
			else if (dungeonContent[row][col] == skeletor)
				cout << 'S' << "   ";
			else if (static_cast<Monster*>(dungeonContent[row][col])->getType() == Bugbear)
				cout << 'B' << "   ";
			else if (static_cast<Monster*>(dungeonContent[row][col])->getType() == Platypie)
				cout << 'P' << "   ";
			else if (static_cast<Monster*>(dungeonContent[row][col])->getType() == Emoo)
				cout << 'E' << "   ";
			else if (static_cast<Monster*>(dungeonContent[row][col])->getType() == Octopod)
				cout << 'O' << "   ";
			else if (static_cast<Item*>(dungeonContent[row][col])->getType() == Cherry)
				cout << 'C' << "   ";
			else if (static_cast<Item*>(dungeonContent[row][col])->getType() == Apple)
				cout << 'A' << "   ";
			else if (static_cast<Item*>(dungeonContent[row][col])->getType() == Melon)
				cout << 'M' << "   ";
		}
		cout << endl;
	}
}

//play the game based on the selected game mode
void GameController::playGameMode(string selectedGameMode){
	system("cls");
	cout << "Monster Evolution!" << "\n\n";

	//prompt and set player1 name
	promptAndSetPlayer1Name(); system("cls"); cout << "Monster Evolution!" << "\n\n";

	//keep looping until player/evolved monster/skeletor has been defeated
	while (!gameOver){
		//display player details
		cout << player1->toString() << endl;

		//check the selected game mode
		//"1" = Normal Mode
		//"2" = Test Mode
		if (gameMode == "1")
			displayDungeon();
		else if (gameMode == "2")
			displayDungeonContent();
		
		//prompt for movement and move the player
		move(promptAndGetMovement());

		system("cls"); cout << "Monster Evolution!" << "\n\n";
	}

	//if the player/evolved monster has been defeated
	if (player1->getHealth() == 0 || player1->getPlayerEvolvedMonster()->getHealth() == 0){
		cout << "Game Over!" << endl;
		if (player1->getHealth() == 0)
			cout << "You were eaten by the monster..." << endl;
		else
			cout << "Your evolved monster failed to defeat the 'Skeletor'..." << endl;
	}
	//if skeletor has been defeated
	else{
		cout << "Congratulation!" << endl;
		cout << "You defeated 'Skeletor' and found the exit..." << endl;
	}

	system("pause");
}

//starts the game
void GameController::playGame(){
	//prompt for game mode and play the game based on the selected game mode
	playGameMode(promptAndGetGameMode());
}