#ifndef __NPC__
#define __NPC__

#include "Creature.h"

class NPC : public Creature
{
public: //variables
	bool hostile; //boolean that defines if the NPC will attack the Player 

public: //functions
	NPC(const char* name, const char* desc, Room* parent, list<Entity*> inventory, int lifePoints, int baseAttack, bool humanoid, bool hostile); //constructor
	virtual ~NPC(); //destructor
	virtual void updateStatus(); //updates status of this NPC
	virtual void autoEquip(list<Entity*> inventory); //if the NPC has any equipable items and is a humanoid, it equips them when instancing
	bool playerPresent() const; //checks if the player is in the same Room as this NPC
};

#endif