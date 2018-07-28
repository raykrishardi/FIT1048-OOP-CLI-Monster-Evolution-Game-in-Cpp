#include "Player.h"
#include <sstream>
#include <algorithm>

//-------------------------------------
//				Constructor
//-------------------------------------

static const int INITIAL_SKILL_LEVEL = 6;
static const int INITIAL_HEALTH = 10;

//1-parameter constructor that initialises the appropriate value for player object
Player::Player(std::string initName) : Character(INITIAL_SKILL_LEVEL, INITIAL_HEALTH, ObjectType::Player){
	setName(initName);
}

//-------------------------------------
//				Destructor
//-------------------------------------

//when the destructor is called delete all monster object in the collection of normal monsters and delete the player's evolved monster object
Player::~Player(){
	for (int i = 0; i < capturedMonsters.size(); i++)
		delete capturedMonsters[i];
	delete evolvedMonster;
}

//-------------------------------------
//				Accessors
//-------------------------------------

std::string Player::getName(){ return name; }

//return player's evolved monster type as string
//if there is no evolved monster then return "None"
//if there is an evolved monster then return the appropriate evolved monster type
std::string Player::getEvolvedMonsterType(){
	std::string retVal = "None";

	if (evolvedMonster != NULL)
		retVal = evolvedMonster->getTypeAsString();

	return retVal;
}

EvolvedMonster* Player::getPlayerEvolvedMonster(){ return evolvedMonster; }

//return all captured monsters in the player's collection as string
std::string Player::getCapturedMonsters(){
	std::stringstream retVal;

	for (int i = 0; i < capturedMonsters.size(); i++)
		retVal << capturedMonsters[i]->getTypeAsString() << " ";

	return retVal.str();
}

//-------------------------------------
//				Mutator
//-------------------------------------

//attempt to set the player name
//return true and assign the name if the given name is valid
bool Player::setName(std::string newName){
	bool success = false;

	if (validateName(newName)){
		name = newName;
		success = true;
	}

	return success;
}

//---------------------------------------
//		Helper and Utility functions
//---------------------------------------

//check whether the player name is valid or not (must consist of either upper/lower case alphabet letter)
//return false if it is not either combination of upper/lower case alphabet letter
bool Player::validateName(std::string newName){
	bool valid = true;
	char chr;

	if (newName.length() > 0){
		for (int i = 0; i < newName.length(); i++){
			chr = newName[i];
			if (!(chr >= 65 && chr <= 90 || chr >= 97 && chr <= 122)){
				valid = false;
				break;
			}
		}
	}
	else
		valid = false;

	return valid;
}

void Player::evolveMonster(){
	int monsterType;
	int totalSkillLevel = 0;
	int totalHealth = 0;
	
	//determine which monster is evolving and reset the number of monster appropriately
	if (numberOfBugbear == 5){
		monsterType = 1;
		numberOfBugbear = 0;
	}
	else if (numberOfPlatypie == 5){
		monsterType = 2;
		numberOfPlatypie = 0;
	}
	else if (numberOfEmoo == 5){
		monsterType = 3;
		numberOfEmoo = 0;
	}
	
	//calculate the total skill level and health for the evolved monster
	//delete normal monster object
	//erase the normal monster address from the collection of captured normal monsters
	for (int i = 0; i < capturedMonsters.size(); i++){
		if (capturedMonsters[i]->getType() == monsterType){
			totalSkillLevel += capturedMonsters[i]->getSkillLevel();
			totalHealth += capturedMonsters[i]->getHealth();
			delete capturedMonsters[i];
			capturedMonsters.erase(capturedMonsters.begin()+i);
			i--; //to make sure that all elements are checked properly after erasing an element in the vector
		}
	}

	//delete existing evolved monster if any
	if (evolvedMonster != NULL)
		delete evolvedMonster;

	//assign the player's evolved monster pointer with new evolved monster object with the appropriate type, skill level, and health
	evolvedMonster = new EvolvedMonster(monsterType, totalSkillLevel, totalHealth);
}

void Player::addMonster(Monster* newMonster){
	//add the appropriate normal monster to the collection of captured normal monsters
	//increment the number of normal monster type accordingly
	if (newMonster->getType() == 1 || newMonster->getType() == 2 || newMonster->getType() == 3){
		capturedMonsters.push_back(newMonster);
		switch (newMonster->getType()) {
		case 1:
			numberOfBugbear++;
			break;
		case 2:
			numberOfPlatypie++;
			break;
		case 3:
			numberOfEmoo++;
		}
	}

	//check whether a particular normal monster type is ready to evolve or not
	if (numberOfBugbear == 5 || numberOfPlatypie == 5 || numberOfEmoo == 5)
		evolveMonster();
}

std::string Player::toString(){
	std::stringstream retVal;

	retVal << "Name: " << getName() << std::endl;
	retVal << Character::toString() << std::endl;
	retVal << "Captured Monster: " << "[ " << getCapturedMonsters() << "]" << std::endl;
	retVal << "Bugbear: " << numberOfBugbear << " ";
	retVal << "Platypie: " << numberOfPlatypie << " ";
	retVal << "Emoo: " << numberOfEmoo << std::endl;
	retVal << "Evolved Monster: " << getEvolvedMonsterType() << std::endl;
	//if there is an evolved monster then include the appropriate attributes
	if (evolvedMonster != NULL){
		retVal << "Skill Level: " << evolvedMonster->getSkillLevel() << " | Special power modifier: " << evolvedMonster->getSpecialPowerModifier() << std::endl;
		retVal << "Health: " << evolvedMonster->getHealth() << std::endl;
	}

	return retVal.str();
}