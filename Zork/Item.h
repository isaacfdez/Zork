#ifndef __Item__
#define __Item__

#include "Entity.h"

using namespace std;

enum ItemType //enum that indicates this Item's type
{
	WEAPON, SHIELD, HELM, VEST, PANTS, COMMON
};

class Item : public Entity //The list of Entities inherited from the class Entity for this class will be a list of Items this Item contains. It will be empty otherwise.
{
public: //variables
	bool isEquipped; //boolean that defines if this Item is equipped
	bool canEquip; //boolean that defines if this Item can be equiped
	int valAttack; //value of the amount of damage this Item inflicts
	int valBlock; //value of the amount of damage this Item can block
	int valDefense; //value of the amount of defense this Item provides
	ItemType itemType; //slot in which this Item can be equiped

public: //functions
	Item(const char* name, const char* desc, Entity* parent, const int valAttack, const int valBlock, const int valDefense, ItemType itemType, bool canEquip); //constructor
	virtual ~Item(); //destructor
	void lookAt() const; //function that describes the Item
	bool isEmpty() const; //checks if this Item has an Item inside
};

#endif