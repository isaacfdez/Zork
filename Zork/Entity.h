#ifndef __Entity__
#define __Entity__

#include <string>
#include <iostream>
#include <list>

using namespace std;

enum Type //enum to set the type for the diferent classes inheriting Entity
{
	creature, entity, exit, item, player, room
};

class Entity //class that defines common variables and functions for all game elements
{
public: //variables
	Type type; //type of the Entity
	std::string name; //name of the Entity
	std::string desc; //description of the Entity
	Entity* parent; //Entity's parent, if it has one
	list<Entity*> gameElements; //List of Entitys contained in this Entity

public: //functions
	Entity(const char* name, const char* desc, Entity* parent); //constructor
	virtual ~Entity(); //destructor
	virtual void updateStatus(); //function that updates the status of the Entity
	virtual void LookAt() const; //function that describes the Entity
	void ChangeParent(Entity* newParent); //function that changes this Entity's parent
	bool exists(Entity* otherEntity) const; //function that checks if another Entity exists in this Entity
	Entity* getElement(const string& name, Type type) const; //function that gets target Entity comparing its name and type
	void getAllOf(Type type, list<Entity*>& elementsFound); //function that fills a list with all the elements of a type the Entity contains.
};

#endif