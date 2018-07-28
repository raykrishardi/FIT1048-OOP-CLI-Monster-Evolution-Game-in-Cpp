#include "Item.h"
#include <sstream>

//lookup array to get the item type as string
const std::string ITEM_TYPE[] = { "None", "Cherry", "Apple", "Melon" };

//-------------------------------------
//				Constructor
//-------------------------------------

//1-parameter constructor that initialises the item object with the appropriate values based on the item type
Item::Item(int initType) : GameObject(ObjectType::Item){
	setType(static_cast<ItemType>(initType));
	setHealthModifier(determineHealthModifier());
}

//-------------------------------------
//				Accessors
//-------------------------------------

int Item::getType() { return type; }
std::string Item::getTypeAsString(){ return ITEM_TYPE[type]; }
int Item::getHealthModifier(){ return healthModifier; }

//-------------------------------------
//				Mutators
//-------------------------------------

void Item::setType(ItemType newType){
	//item type must be either "Cherry" or "Apple" or "Melon"
	if (newType >= Cherry && newType <= Melon)
		type = newType;
}

void Item::setHealthModifier(int newHealthModifier){
	//health modifier must be between 1 and 3
	if (newHealthModifier >= 1 && newHealthModifier <= 3)
		healthModifier = newHealthModifier;
}

//-------------------------------------
//			 Helper function
//-------------------------------------

//determine the health modifer based on the item type
//Cherry = 1, modifier = 1
//Apple = 2, modifier = 2
//Melon = 3, modifier = 3
int Item::determineHealthModifier(){
	int modifier;

	//protect against invalid item type
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

//-------------------------------------
//			Utility function
//-------------------------------------

std::string Item::toString(){
	std::stringstream retVal;

	retVal << "Item type: " << getTypeAsString() << std::endl;
	retVal << "Health modifier: " << getHealthModifier() << std::endl;

	return retVal.str();
}