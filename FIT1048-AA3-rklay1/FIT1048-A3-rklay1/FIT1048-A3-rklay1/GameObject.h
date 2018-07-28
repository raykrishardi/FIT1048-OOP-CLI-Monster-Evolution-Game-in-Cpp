#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

enum class ObjectType { Player, Item, Monster, BossMonster, EvolvedMonster };

class GameObject{
protected:
	ObjectType objectType; //variable that represents the object type
public:
	//constructor
	GameObject(ObjectType initObjectType);
	
	//destructor
	virtual ~GameObject() = 0; //declare this class as abstract

	//accessor
	ObjectType getObjectType(); //return the object type
};

#endif