#ifndef __Item__
#define __Item__

#include "Entity.h"

class Item : public Entity//class that defines the variables and functions used by the items in the game
{
public: //variables
	bool canEquip; //boolean that defines if the item can be equiped
	int valAttack; //value of the amount of damage the item inflicts
	int valBlock; //value of the amount of damage the item can block 

public: //functions
	Item(const char* name, const char* desc, Entity* parent, const int valAttack, const int valBlock, bool canEquip = false); //constructor
	~Item(); //destructor
	void lookAt() const; //function that describes the Entity
	int getValAttack(); //function that returns the value of attack
	int getValBlock(); //function that returns the value of block
	void setValAttack(int value); //function that set the value for attacking
	void setValBlock(int value); //function that set the value for blocking
};


#endif