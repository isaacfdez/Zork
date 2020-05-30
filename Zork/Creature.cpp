#include "Creature.h"
#include "Item.h"
#include "Room.h"
#include "Exit.h"

Creature::Creature(const char* name, const char* desc, Room* parent, int lifePoints) : Entity(name, desc, (Entity*)parent), lifePoints(lifePoints)
{
	type = CREATURE;
	isAlive = true;
	weapon = shield = helm = vest = pants = NULL;
	targetToAttack = NULL;
}

Creature::~Creature()
{
}

void Creature::lookAt(const vector<string>& targetEntity) const
{
	if (!isAlive)
	{
		cout << "This is the corpse of ";
	}
	cout << name << ", " << desc << "\n";	
}

void Creature::updateStatus()
{
	if(targetToAttack != NULL)
	{
		if(parent->existsEntity(targetToAttack))
		{
			hit();
		}
	}
}

void Creature::showStats() const
{
	cout << name << "\n";
	cout << lifePoints << "\n";
	if (weapon != NULL) {
		cout << "Attack = " << weapon->valAttack << "\n";
	}
	else
	{
		cout << "No weapon equiped. Attack = 0\n";
	}
	if (shield != NULL) 
	{
		cout << "Block = " << shield->valBlock << "\n";
	}
	else
	{
		cout << "No shield equiped. Block = 0\n";
	}
	if (helm != NULL || vest != NULL || pants != NULL) 
	{
		cout << "Armor = " << getSumArmor() << "\n";
	}
	else
	{
		cout << "No piece of armor equiped. Armor = 0\n";
	}
}

void Creature::showInventory() const
{
	list<Entity*> inventory;
	getAllOf(ITEM, inventory);

	if (inventory.size() != 0)
	{
		cout << "Inventory of " << name << "\n";
		for (list<Entity*>::const_iterator item = inventory.begin(); item != inventory.end(); ++item)
		{
			switch ((*item)->type)
			{
			case WEAPON:
				cout << (*item)->name << " equiped as a weapon.\n";
				break;
			case SHIELD:
				cout << (*item)->name << " equiped as a shield.\n";
				break;
			case HELM:
				cout << (*item)->name << " equiped as a helm.\n";
				break;
			case VEST:
				cout << (*item)->name << " equiped as a vest.\n";
				break;
			case PANTS:
				cout << (*item)->name << " equiped as pants.\n";
				break;
			default:
				cout << (*item)->name << "\n";
			}


		}
	}
}

void Creature::go(const vector<string>& targetExit)
{
	if (!isAlive)
	{
		return;
	}

	Exit* exit = getRoom()->getExit(targetExit[1]);

	if (exit != NULL)
	{
		changeParent(exit->destination);
	}
}

void Creature::take(const vector<string>& targetItem)
{
	if(!isAlive)
	{
		return;
	}

	Item* item = (Item*)parent->getElement(ITEM, targetItem[1]);

	if (item == NULL)
	{
		if (targetItem.size()>2)
		{
			item = (Item*)parent->getElement(ITEM, targetItem[3]);

			if (item != NULL)
			{
				item->changeParent(this);
			}
		}
	}
	else
	{
		item->changeParent(this);
	}
}

void Creature::drop(const vector<string>& targetItem)
{
	if (!isAlive)
	{
		return;
	}

	Item* item = (Item*)parent->getElement(ITEM, targetItem[1]);

	if (item != NULL)
	{
		if (targetItem.size() > 2)
		{
			Item* secondItem = (Item*)parent->getElement(ITEM, targetItem[3]);

			if (secondItem != NULL)
			{
				item->changeParent(secondItem);
			}
			else
			{
				secondItem = (Item*)getElement(ITEM, targetItem[3]);

				if (secondItem != NULL)
				{
					item->changeParent(secondItem);
				}
			}
		}
		else
		{
			item->changeParent(parent);
		}
	}
	

}

void Creature::loot(const vector<string>& targetDeadCreature)
{
	Creature* target = (Creature*)parent->getElement(CREATURE, targetDeadCreature[1]);

	if(target != NULL)
	{
		if(!target->isAlive)
		{
			list<Entity*> inventoryOfTarget;
			target->getAllOf(ITEM, inventoryOfTarget);

			for (list<Entity*>::const_iterator item = inventoryOfTarget.begin(); item != inventoryOfTarget.end(); ++item)
			{
				Item* temporal = (Item*)(*item);
				temporal->changeParent(this);
			}
		}
	}
}

void Creature::lock(const vector<string>& targetExit)
{
}

void Creature::unlock(const vector<string>& targetExit)
{
}

void Creature::equip(const vector<string>& targetItem)
{
}

void Creature::unequip(const vector<string>& targetItem)
{
}

void Creature::attack(const vector<string>& targetCreature)
{
}

void Creature::hit()
{
}

void Creature::block(const int damageAmount)
{
}

int Creature::getSumArmor() const
{
	int sum = 0;
	if (helm != NULL) 
	{
		sum += helm->valDefense;
	}
	if (vest != NULL)
	{
		sum += vest->valDefense;
	}
	if (pants != NULL)
	{
		sum += pants->valDefense;
	}
	return sum;
}

Room* Creature::getRoom() const
{
	return (Room*)parent;
}
