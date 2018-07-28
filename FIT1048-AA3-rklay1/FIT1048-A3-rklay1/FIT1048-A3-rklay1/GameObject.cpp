#include "GameObject.h"

//-------------------------------------
//				Constructor
//-------------------------------------

//1-parameter constructor that initialises the object type
GameObject::GameObject(ObjectType initObjectType){
	objectType = initObjectType;
}

//-------------------------------------
//				Destructor
//-------------------------------------

GameObject::~GameObject(){}

//-------------------------------------
//				Accessor
//-------------------------------------

ObjectType GameObject::getObjectType(){ return objectType; }