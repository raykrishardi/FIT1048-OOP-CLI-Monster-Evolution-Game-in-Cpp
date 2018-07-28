#ifndef EVOLVED_MONSTER_H
#define EVOLVED_MONSTER_H

#include "HigherRankMonster.h"

class EvolvedMonster : public HigherRankMonster{
private:
	//helper function
	int determineSpecialPowerModifier(int type); //function that determines the special power modifer based on the monster type
public:
	//constructor
	EvolvedMonster(int initType, int initSkillLevel, int initHealth);
};

#endif