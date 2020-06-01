#include "NPC.h"
#include "Player.h"
#include "Item.h"

NPC::NPC(const char* name, const char* desc, Room* parent, list<Entity*> inventory, int lifePoints, int baseAttack, bool humanoid, bool hostile) : Creature (name, desc, parent, lifePoints, baseAttack, humanoid), hostile(hostile)
{
	gameElements = inventory;
	autoEquip();
}

NPC::~NPC()
{
}

void NPC::updateStatus()
{
	if(playerPresent() && hostile)
	{
		targetToAttack = (Player*)parent->getPlayer();
	}
	
	if (targetToAttack != NULL)
	{
		if (parent->existsEntity(targetToAttack))
		{
			hit();
		}
	}
}

void NPC::autoEquip()
{
	for (list<Entity*>::const_iterator possibleItem = gameElements.begin(); possibleItem != gameElements.end(); ++possibleItem)
	{
		Item* item = (Item*)(*possibleItem);
		if (item != NULL)
		{
			item->changeParent(this);
			if (item->canEquip)
			{
				switch (item->type)
				{
				case WEAPON:
					weapon = item;
					break;
				case SHIELD:
					shield = item;
					break;
				case HELM:
					helm = item;
					break;
				case VEST:
					vest = item;
					break;
				case PANTS:
					pants = item;
					break;
				default:
				}
			}
		}
	}
}

bool NPC::playerPresent() const
{
	return parent->existsType(PLAYER);
}
