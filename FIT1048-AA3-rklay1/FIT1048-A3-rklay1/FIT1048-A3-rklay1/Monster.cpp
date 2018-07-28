#include "Monster.h"
#include <sstream>

//lookup array to get the monster type as string
const std::string MONSTER_TYPE[] = { "None", "Bugbear", "Platypie", "Emoo", "Octopod", "Skeletor" };

//-------------------------------------
//				Constructors
//-------------------------------------

//1-parameter constructor that initialises the monster object with the appropriate values based on the monster type
//used in creating normal monsters (bugbear, platypie, emoo, and octopod)
Monster::Monster(int initType) : Character(generateRandomSkillLevel(), generateRandomHealth(), ObjectType::Monster){
	setType(static_cast<MonsterType>(initType));
}

//4-parameter constructor that initialises the monster object with the appropriate values based on the monster type
//used in creating higher rank monster (evolved monster and skeletor)
Monster::Monster(int initType, int initSkillLevel, int initHealth, ObjectType initObjectType) : Character(initSkillLevel, initHealth, initObjectType){
	setType(static_cast<MonsterType>(initType));
}

//-------------------------------------
//				Destructor
//-------------------------------------

Monster::~Monster(){}

//-------------------------------------
//				Accessors
//-------------------------------------

int Monster::getType(){ return type; }
std::string Monster::getTypeAsString(){ return MONSTER_TYPE[type]; }

//-------------------------------------
//				Mutator
//-------------------------------------

void Monster::setType(MonsterType newType){
	//monster type must be either "Bugbear" or "Platypie" or "Emoo" or "Octopod" or "Skeletor"
	if (newType >= Bugbear && newType <= Skeletor)
		type = newType;
}

//-------------------------------------
//			Helper functions
//-------------------------------------

//return random skill level from 1-3
int Monster::generateRandomSkillLevel(){ return (1 + rand() % 3); }
//return random health from 3-6
int Monster::generateRandomHealth(){ return (3 + rand() % 4); }

//-------------------------------------
//			Utility function
//-------------------------------------

std::string Monster::toString(){
	std::stringstream retVal;

	retVal << "Monster Type: " << getTypeAsString() << std::endl;
	retVal << Character::toString();

	return retVal.str();
}