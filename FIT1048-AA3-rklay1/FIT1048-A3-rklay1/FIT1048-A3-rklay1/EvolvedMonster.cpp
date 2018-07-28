#include "EvolvedMonster.h"

//-------------------------------------
//				Constructor
//-------------------------------------

//when creating an evolved monster, initialise the object with the appropriate values for each attributes
EvolvedMonster::EvolvedMonster(int initType, int initSkillLevel, int initHealth) : 
			 HigherRankMonster(initType, initSkillLevel, initHealth, determineSpecialPowerModifier(initType), ObjectType::EvolvedMonster){}

//-------------------------------------
//			 Helper function
//-------------------------------------

//determine the special power modifer based on the monster type
//Bugbear = 1, modifier = 1
//Platypie = 2, modifier = 2
//Emoo = 3, modifier = 3
int EvolvedMonster::determineSpecialPowerModifier(int type){
	int modifier;

	//protect against invalid evolved monster (e.g. evolved Octopod or Skeletor)
	switch (type) {
	case 1:
		modifier = 1;
		break;
	case 2:
		modifier = 2;
		break;
	case 3:
		modifier = 3;
	}

	return modifier;
}