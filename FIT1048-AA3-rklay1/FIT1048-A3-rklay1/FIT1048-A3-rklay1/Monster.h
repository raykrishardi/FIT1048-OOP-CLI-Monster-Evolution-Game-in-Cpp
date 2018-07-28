#ifndef MONSTER_H
#define MONSTER_H

#include "Character.h"

enum MonsterType { None, Bugbear, Platypie, Emoo, Octopod, Skeletor }; //"None" to ignore index 0

class Monster : public Character{
protected:
	int type; //variable that represents the monster type
private:
	//helper functions
	int generateRandomSkillLevel(); //function that generates random skill level
	int generateRandomHealth(); //function that generates random health
public:
	//constructors
	Monster(int initType);
	Monster(int initType, int initSkillLevel, int initHealth, ObjectType initObjectType);

	//destructor
	virtual ~Monster();

	//accessors
	int getType(); //return the monster type
	std::string getTypeAsString(); //return the monster type as string

	//mutator
	void setType(MonsterType newType); //attempt to set the monster type

	//utility function
	std::string toString(); //return the attributes with appropriate formatting
};

#endif