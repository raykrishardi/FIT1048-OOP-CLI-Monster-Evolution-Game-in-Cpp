#ifndef CHARACTER_H
#define CHARACTER_H

#include "GameObject.h"
#include <string>

class Character : public GameObject{
protected:
	int skillLevel; //variable that represents the player/monster skill level
	int health; //variable that represents the player/monster health
public:
	//constructor
	Character(int initSkillLevel, int initHealth, ObjectType initObjectType);

	//destructor
	virtual ~Character() = 0; //declare this class as abstract

	//accessors
	int getSkillLevel(); //return the player/monster skill level
	int getHealth(); //return the player/monster health

	//mutators
	void setSkillLevel(int newSkillLevel); //attempt to set the player/monster skill level
	void setHealth(int newHealth); //attempt to set the player/monster health

	//utility function
	std::string toString(); //return the attributes with appropriate formatting
};

#endif