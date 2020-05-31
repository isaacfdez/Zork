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
	bool humanoid; //only Creatures that are humanoid will be able to equip Items
	int lifePoints; //number of life points remaining for this creature
	int baseAttack; //number of base Attack Damage of this creature
	Item* weapon; //Item slot for the weapon
	Item* shield; //Item slot for the shield
	Item* vest; //Item slot for chest protection area
	Item* helm; //Item slot for head protection area
	Item* pants; //Item slor for legs protection area
	Creature* targetToAttack; //target Creature objective of attacks

public: //functions
	Creature(const char* name, const char* desc, Room* parent, int lifePoints, int baseAttack, bool humanoid); //constructor
	virtual ~Creature(); //destructor
	virtual void lookAt(const vector<string>& targetEntity) const; //describes this Creature
	virtual void showStats() const; //command that shows the statistics of this Creature
	virtual void showInventory() const; //command that shows the inventory of this Creature
	virtual void hit(); //this Creature hits it's target for damage equal to it's weapon stats
	virtual void block(const int damageAmount); //this Creature blocks %amount of damage taken regarding its protections
	virtual int getSumArmor() const; //returns the sum of all pieces of armor
	virtual Room* getRoom() const; // gets the Room in which this Creature is in
};

#endif