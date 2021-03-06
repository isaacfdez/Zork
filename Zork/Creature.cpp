#include "Creature.h"
#include "Item.h"
#include "Room.h"
#include "Exit.h"

Creature::Creature(const char* name, const char* desc, Room* parent, int lifePoints, int baseAttack, bool humanoid) : Entity(name, desc, (Entity*)parent), lifePoints(lifePoints), baseAttack(baseAttack), humanoid(humanoid)
{
	type = CREATURE;
	isAlive = true;
	weapon = shield = helm = vest = pants = NULL;
	targetToAttack = NULL;
}

Creature::~Creature()
{
}

void Creature::lookAt() const
{
	if (!isAlive)
	{
		cout << "\n\nThis is the corpse of ";
	}
	cout << name << ", " << desc << "\n";
}

void Creature::showStats() const
{
	cout << "\n\nName: " << name << "\n";
	cout << "Lifepoints: " << lifePoints << "\n";
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
		cout << "\n\nInventory of " << name << "\n";
		for (list<Entity*>::const_iterator element = inventory.begin(); element != inventory.end(); ++element)
		{
			Item* item = (Item*)(*element);
			switch (item->itemType)
			{
			case WEAPON:
				cout << item->name << " equiped as a weapon.\n";
				break;
			case SHIELD:
				cout << item->name << " equiped as a shield.\n";
				break;
			case HELM:
				cout << item->name << " equiped as a helm.\n";
				break;
			case VEST:
				cout << item->name << " equiped as a vest.\n";
				break;
			case PANTS:
				cout << item->name << " equiped as pants.\n";
				break;
			default:
				cout << item->name << "\n";
				break;
			}
		}
	}
	else 
	{
		cout << "\n\n"<< name<< " does not have any item in its inventory\n";
	}
}

void Creature::hit()
{
	if(isAlive)
	{
		if (targetToAttack != NULL)
		{
			if (targetToAttack->isAlive)
			{
				if(weapon != NULL)
				{
					cout << "\n" << name << " attacks " << targetToAttack->name << " with a " << weapon->name << " for a value of " << baseAttack + weapon->valAttack << "\n";
					targetToAttack->block(baseAttack + weapon->valAttack);
				}
				else
				{
					cout << "\n" << name << " attacks " << targetToAttack->name << " with its body for a value of " << baseAttack << "\n";
					targetToAttack->block(baseAttack);
				}
				
				if (targetToAttack->targetToAttack == NULL)
				{
					targetToAttack->targetToAttack = this;
				}
			}
			else
			{
				targetToAttack = NULL;
			}
		}
	}
}

void Creature::block(const int damageAmount)
{
	int damageReceived = damageAmount - getSumArmor();

	if (damageReceived > 0)
	{
		lifePoints -= damageReceived;
		cout << "\n" << name << " blocks " << getSumArmor() << " points of damage, losing " << damageReceived << " life points\n";
		if (lifePoints <= 0) {

			cout << "\n" << name << " has died from a fatal hit\n";
		}
	}
	else
	{
		cout << "\n" << name << " blocks all the damage and does not lose any life points\n";
	}
}

int Creature::getSumArmor() const
{
	int sum = 0;
	if (shield != NULL) 
	{
		sum += shield->valBlock;
	}
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
