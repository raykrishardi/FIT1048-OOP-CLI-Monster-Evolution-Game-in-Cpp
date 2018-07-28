#ifndef PLAYER_H
#define PLAYER_H

#include "EvolvedMonster.h"
#include <vector>

class Player : public Character{
private:
	std::string name; //variable that represents the player name
	std::vector<Monster*> capturedMonsters; //collection of captured normal monsters
	EvolvedMonster* evolvedMonster = NULL; //variable that represents player's evolved monster

	int numberOfBugbear = 0; //variable that represents the number of "Bugbear" in the player's collection
	int numberOfPlatypie = 0; //variable that represents the number of "Platypie" in the player's collection
	int numberOfEmoo = 0; //variable that represents the number of "Emoo" in the player's collection

	//helper function
	bool validateName(std::string newName); //validate the name given by the user
public:
	//constructor
	Player(std::string initName);

	//destructor
	~Player();

	//accessors
	std::string getName(); //return player name
	std::string getEvolvedMonsterType(); //return player's evolved monster type as string
	EvolvedMonster* getPlayerEvolvedMonster(); //return pointer to the player's evolved monster
	std::string getCapturedMonsters(); //return all captured monsters in the player's collection as string

	//mutator
	bool setName(std::string newName); //attempt to set player name

	//utility functions
	std::string toString(); //return the attributes with appropriate formatting
	void addMonster(Monster* newMonster); //add a normal monster to player's collection
	void evolveMonster(); //evolve the captured normal monsters
};

#endif