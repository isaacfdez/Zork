#ifndef __NPC__
#define __NPC__

#include "Creature.h"

class NPC : public Creature
{
public: //variables

public: //functions
	NPC(const char* name, const char* desc, Room* parent, list<Item*> inventory);

};

#endif