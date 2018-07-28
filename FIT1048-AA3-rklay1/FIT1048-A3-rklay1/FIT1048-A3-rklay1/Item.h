#ifndef ITEM_H
#define ITEM_H

#include "GameObject.h"
#include <string>

enum ItemType { NONE, Cherry, Apple, Melon }; //"NONE" to ignore index 0

class Item : public GameObject{
private:
	int type; //variable that represents the item type
	int healthModifier; //variable that represents the item's health modifier

	//helper function
	int determineHealthModifier(); //function that determines the health modifier based on the item type
public:
	//constructor
	Item(int initType);

	//accessors
	int getType(); //return the item type
	std::string getTypeAsString(); //return the item type as string
	int getHealthModifier(); //return the item's health modifier

	//mutators
	void setType(ItemType newType); //attempt to set the item type
	void setHealthModifier(int newHealthModifier); //attempt to set the item's health modifier

	//utility function
	std::string toString(); //return the attributes with appropriate formatting
};

#endif