#ifndef __Item__
#define __Item__

#include "Entity.h"

using namespace std;

enum Slot //enum that indicates in which Item slot of a Creature this Item can be equiped
{
	WEAPON, SHIELD, HELM, VEST, PANTS
};

class Item : public Entity //The list of Entities inherited from the class Entity for this class will be a list of Items this Item contains. It will be empty otherwise.
{
public: //variables
	bool canEquip; //boolean that defines if the item can be equiped
	int valAttack; //value of the amount of damage the item inflicts
	int valBlock; //value of the amount of damage the item can block
	int valDefense; //value of the amount of defense the item provides
	Slot slot; //slot in which this Item can be equiped

public: //functions
	Item(const char* name, const char* desc, Entity* parent, const int valAttack, const int valBlock, const int valDefense, Slot itemSlot); //constructor
	virtual ~Item(); //destructor
	void lookAt() const; //function that describes the Item
	bool isEmpty() const; //checks if this Item has an Item inside
};

#endif