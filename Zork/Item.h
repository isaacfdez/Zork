#ifndef __Item__
#define __Item__

#include "Entity.h"

class Item //class that defines the variables and functions used by the items in the game
{
public: //variables
	bool canEquip; //boolean that defines if the item can be equiped
	const int valAttack; //value of the amount of damage the item inflicts
	const int valBlock; //value of the amount of damage the item can block 

public: //functions
	Item(const char* name, const char* desc, Entity* parent, const int valAttack, const int valBlock, bool canEquip = false); //constructor
	~Item(); //destructor
	void lookAt() const; //function that describes the Entity
};


#endif