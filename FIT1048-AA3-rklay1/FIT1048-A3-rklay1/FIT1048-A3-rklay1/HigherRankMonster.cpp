#include "HigherRankMonster.h"
#include <sstream>

//-------------------------------------
//				Constructor
//-------------------------------------

//5-parameter constructor that initialises the appropriate value for boss/evolved monster
HigherRankMonster::HigherRankMonster(int initType, int initSkillLevel, int initHealth, int initSpecialPowerModifier, ObjectType initObjectType) :
							 Monster(initType, initSkillLevel, initHealth, initObjectType){
	setSpecialPowerModifier(initSpecialPowerModifier);
}

//-------------------------------------
//				Destructor
//-------------------------------------

HigherRankMonster::~HigherRankMonster(){}

//-------------------------------------
//				Accessor
//-------------------------------------

int HigherRankMonster::getSpecialPowerModifier(){ return specialPowerModifier; }

//-------------------------------------
//				Mutator
//-------------------------------------

void HigherRankMonster::setSpecialPowerModifier(int newSpecialPowerModifier){
	//special power modifier must be between 1 and 3
	//evolved bugbear = 1
	//evolved platypie and skeletor = 2
	//evolved emoo = 3
	if (newSpecialPowerModifier >= 1 && newSpecialPowerModifier <= 3)
		specialPowerModifier = newSpecialPowerModifier;
}

//-------------------------------------
//			Utility function
//-------------------------------------

std::string HigherRankMonster::toString(){
	std::stringstream retVal;

	retVal << Monster::toString();
	retVal << "Special power modifier: " << getSpecialPowerModifier() << std::endl;

	return retVal.str();
}