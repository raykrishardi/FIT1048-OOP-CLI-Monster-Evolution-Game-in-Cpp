#ifndef HIGHER_RANK_MONSTER_H
#define HIGHER_RANK_MONSTER_H

#include "Monster.h"

class HigherRankMonster : public Monster{
protected:
	int specialPowerModifier; //variable that represents the special power modifier
public:
	//constructor
	HigherRankMonster(int initType, int initSkillLevel, int initHealth, int initSpecialPowerModifier, ObjectType initObjectType);

	//destructor
	virtual ~HigherRankMonster() = 0; //declare this class as abstract

	//accessor
	int getSpecialPowerModifier(); //return the special power modifier

	//mutator
	void setSpecialPowerModifier(int newSpecialPowerModifier); //attempt to set the special power modifier

	//utility function
	std::string toString(); //return the attributes with appropriate formatting
};

#endif