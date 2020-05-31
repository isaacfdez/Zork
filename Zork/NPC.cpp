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
	for (list<Entity*>::const_iterator item = gameElements.begin(); item != gameElements.end(); ++item)
	{
		Item* equipableItem = (Item*)(*item);
		if (equipableItem != NULL)
		{
			if (equipableItem->canEquip)
			{
				switch (equipableItem->type)
				{
				case WEAPON:
					weapon = equipableItem;
					break;
				case SHIELD:
					shield = equipableItem;
					break;
				case HELM:
					helm = equipableItem;
					break;
				case VEST:
					vest = equipableItem;
					break;
				case PANTS:
					pants = equipableItem;
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
