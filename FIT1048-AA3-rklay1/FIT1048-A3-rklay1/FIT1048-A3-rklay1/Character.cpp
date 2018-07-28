#include "Character.h"
#include <sstream>

//-------------------------------------
//				Constructor
//-------------------------------------

//3-parameter constructor that initialises the skill level, health, and object type
Character::Character(int initSkillLevel, int initHealth, ObjectType initObjectType) : GameObject(initObjectType){
	setSkillLevel(initSkillLevel);
	setHealth(initHealth);
}

//-------------------------------------
//				Destructor
//-------------------------------------

Character::~Character(){}

//-------------------------------------
//				Accessors
//-------------------------------------

int Character::getSkillLevel(){ return skillLevel; }
int Character::getHealth(){ return health; }

//-------------------------------------
//				Mutators
//-------------------------------------

void Character::setSkillLevel(int newSkillLevel){
	//min character skill level is 1
	//max character skill level is 15 (3*5)
	if (newSkillLevel >= 1 && newSkillLevel <= 15)
		skillLevel = newSkillLevel;
}
void Character::setHealth(int newHealth){
	//min character health is 0 (i.e. player/monster is dead)
	//max character health is 30 (6*5)
	if (newHealth >= 0 && newHealth <= 30)
		health = newHealth;
}

//-------------------------------------
//			Utility function
//-------------------------------------

//return the skill level and health with appropriate formatting
std::string Character::toString(){
	std::stringstream retVal;

	retVal << "Skill Level: " << getSkillLevel() << std::endl;
	retVal << "Health: " << getHealth() << std::endl;

	return retVal.str();
}