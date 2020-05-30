#ifndef __Creature__
#define __Creature__

#include "Entity.h"
#include <vector>

class Item;
class Room;

using namespace std;

class Creature : public Entity //The list of Entities inherited from the class Entity for this class will be the creature's inventory. It will be empty if the Creature does not have anything in it's inventory.
{
public: //Variables
	bool isAlive; //boolean that indicates if this creature is alive or dead
	int lifePoints; //number of life points remaining for this creature
	Item* weapon; //Item slot for the weapon
	Item* shield; //Item slot for the shield
	Item* vest; //Item slot for chest protection area
	Item* helm; //Item slot for head protection area
	Item* pants; //Item slor for legs protection area
	Creature* targetToAttack; //target Creature objective of attacks

public: //functions
	Creature(const char* name, const char* desc, Room* parent, int lifePoints); //constructor
	virtual ~Creature(); //destructor
	virtual void lookAt(const vector<string>& targetEntity) const; //describes this Creature
	virtual void updateStatus(); //updates status of this Creature
	virtual void showStats() const; //command that shows the statistics of this Creature
	virtual void showInventory() const; //command that shows the inventory of this Creature
	virtual void go(const vector<string>& targetExit); //command that makes a Creature go elsewhere if able
	virtual void take(const vector<string>& targetItem); //command that makes a Creature take target Item from the Room or another Item if both are there
	virtual void drop(const vector<string>& targetItem); //command that makes a Creature drop target Item from his inventory in the Room or inside another Item
	virtual void loot(const vector<string>& targetDeadCreature); //command that makes a Creature take all the Items in target Creature if the latter is dead
	virtual void lock(const vector<string>& targetExit); //command that makes a Creature lock target Exit
	virtual void unlock(const vector<string>& targetExit); //command that makes a Creature unlock target Exit
	virtual void equip(const vector<string>& targetItem); //command that makes a Creature equip an item from it's inventory in it's slot if it can be equiped
	virtual void unequip(const vector<string>& targetItem); //command that makes a Creature unequip an item already equiped in one of it's slots
	virtual void attack(const vector<string>& targetCreature); //command that sets a Creature to attack another target Creature
	virtual void hit(); //this Creature hits it's target for damage equal to it's weapon stats
	virtual void block(const int damageAmount); //this Creature blocks %amount of damage taken regarding its protections
	virtual int getSumArmor() const; //returns the sum of all pieces of armor
	virtual Room* getRoom() const; // gets the 
};

#endif