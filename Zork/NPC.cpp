#include "NPC.h"
#include "Player.h"
#include "Item.h"

NPC::NPC(const char* name, const char* desc, Room* parent, list<Entity*> inventory, int lifePoints, int baseAttack, bool humanoid, bool hostile) : Creature (name, desc, parent, lifePoints, baseAttack, humanoid), hostile(hostile)
{
	type = CREATURE;
	autoEquip(inventory);

	if (lifePoints<1)
	{
		isAlive = false;
	}
}

NPC::~NPC()
{
}

void NPC::updateStatus()
{
	if (lifePoints <= 0 && isAlive)
	{
		isAlive = false;
	}

	if (isAlive) {
		if (playerPresent() && hostile)
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
}

void NPC::autoEquip(list<Entity*> inventory)
{
	for (list<Entity*>::const_iterator possibleItem = inventory.begin(); possibleItem != inventory.end(); ++possibleItem)
	{
		Item* item = (Item*)(*possibleItem);
		if (item != NULL)
		{
			item->changeParent(this);
			if (item->canEquip)
			{
				switch (item->itemType)
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
					break;
				}
			}
		}
	}
}

bool NPC::playerPresent() const
{
	return parent->existsType(PLAYER);
}
