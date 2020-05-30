#include "Room.h"
#include "Exit.h"
#include "Creature.h"
#include "Item.h"

Room::Room(const char* name, const char* desc) : Entity (name, desc, NULL)
{
	type = ROOM;
}

Room::~Room()
{
}

void Room::lookAt()
{
	cout << "\nYou're at the " << name << "\n";
	cout << desc << "\n";

	for (list<Entity*>::const_iterator gameElement = gameElements.begin(); gameElement != gameElements.end(); ++gameElement)
	{
		if ((*gameElement)->type == CREATURE)
		{
			Creature* creature = (Creature*)(*gameElement);
			cout << "You can see here ";
			if (!creature->isAlive)
			{
				cout << "the corpse of ";
			}
			cout << creature->name << "\n";
		}
	}

	for (list<Entity*>::const_iterator gameElement = gameElements.begin(); gameElement != gameElements.end(); ++gameElement)
	{
		if ((*gameElement)->type == ITEM)
		{
			Item* item = (Item*)(*gameElement);
			cout << "You can see here: " << item->name;
			if (!item->isEmpty())
			{
				cout << ". It looks like it may contain something.";
			}
			cout << "\n";
		}
	}

	for (list<Entity*>::const_iterator gameElement = gameElements.begin(); gameElement != gameElements.end(); ++gameElement)
	{
		if ((*gameElement)->type == EXIT)
		{
			Exit* exit = (Exit*)(*gameElement);
			exit->lookAt();
		}
	}
}

Exit* Room::getExit(const string& direction) const
{
	for (list<Entity*>::const_iterator gameElement= gameElements.begin(); gameElement != gameElements.end(); ++gameElement)
	{
		if ((*gameElement)->type == EXIT)
		{
			Exit* exit = (Exit*)*gameElement;
			if (_stricmp(exit->direction.c_str(), direction.c_str()) == 0)
			{
				return exit;
			}
		}
	}
	return NULL;
}
