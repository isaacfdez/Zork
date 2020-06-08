#include "Player.h"
#include "Item.h"
#include "Exit.h"
#include "Room.h"
#include <iostream>

Player::Player(const char* name, const char* desc, Room* parent, int lifePoints, int baseAttack, bool humanoid) : Creature(name, desc, parent, lifePoints, baseAttack, humanoid)
{
	type = PLAYER;
	triggerDeath = true;
}

Player::~Player()
{
}

void Player::updateStatus()
{
	if (lifePoints <= 0)
	{
		isAlive = false;
	}

	if(isAlive)
	{
		if (targetToAttack != NULL)
		{
			if (parent->existsEntity(targetToAttack))
			{
				hit();
			}
		}
	}
	else
	{
		if (triggerDeath) 
		{
			cout << "You died. Better luck next time. Execute command quit to quit the game.\n";
			triggerDeath = false;
		}
	}
}

void Player::showHelp() const
{
	cout << "\nThis is a list of all the commands the player can execute with a brief description:\n";
	cout << "- help: This command will show the list of commands available.\n";
	cout << "- look: This command will show you everything you have in sight.\n";
	cout << "- look X: This command will show you information about X\n";
	cout << "- stats: This command will show you your stats.\n";
	cout << "- stats X: This command will show you target character X's stats.\n";
	cout << "- inventory: This command will show you your inventory.\n";
	cout << "- inventory X: This command will show you target character X's inventory.\n";
	cout << "- go X: This command will take you in the direction X if able. Directions are: north, south, east, west, up and down.\n";
	cout << "- take X: This command will take X item if exists and put it in the inventory.\n";
	cout << "- take X from Y: This command will take X item from inside Y item if both exist and put it in the inventory.\n";
	cout << "- drop X: This command will drop X item from your inventory if it exists.\n";
	cout << "- drop X in Y: This command will drop X item from your inventory in Y item if both exist.\n";
	cout << "- loot X: This command will loot target character X if it is dead.\n";
	cout << "- lock X with Y: This command will lock direction X with item Y from your inventory if able.\n";
	cout << "- unlock X with Y: This command will unlock direction X with item Y from your inventory if able.\n";
	cout << "- equip X: This command will equip X item if it exists in your inventory and is equipable in a free slot.\n";
	cout << "- unequip X: This command will unequip X item and put it in your inventory if it exists and is equipped.\n";
	cout << "- attack X: This command will make you start a combat with target character X.\n";
	cout << "- quit: this command exits the game.\n\n";
}

void Player::lookAt(const vector<string>& targetEntity)
{
	if (isAlive) 
	{
		switch (targetEntity.size())
		{
		case 1:
		{
			Room* room = (Room*)parent;
			room->lookAt();
			break;
		}
		case 2:
		{
			for (list<Entity*>::const_iterator entity = parent->gameElements.begin(); entity != parent->gameElements.cend(); ++entity)
			{
				if (_stricmp((*entity)->name.c_str(), targetEntity[1].c_str()) == 0 || ((*entity)->type == EXIT && _stricmp(targetEntity[1].c_str(), ((Exit*)(*entity))->direction.c_str()) == 0))
				{
					(*entity)->lookAt();
					return;
				}
				if (_stricmp(targetEntity[1].c_str(), name.c_str()) == 0)
				{
					cout << "\n" << name << ", " << desc << "\n";
					return;
				}

			}
			cout << "\n\nYou do not see anything by the name " << targetEntity[1] << "\n";
			break;
		}
		default:
			break;
		}		
	}
	else
	{
		cout << "\n\nDead players can't perform actions. Execute command quit to quit the game.\n";
	}
}

void Player::showStats(const vector<string>& targetEntity) const
{
	if (isAlive)
	{
		switch (targetEntity.size())
		{
		case 1:
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
			break;
		case 2:
		{
			Creature* target = (Creature*)parent->getElement(CREATURE, targetEntity[1]);

			if (target != NULL)
			{
				target->showStats();
				break;
			}
			else
			{
				cout << "\n\nYou do not see anything by the name " << targetEntity[1] << "\n";
				break;
			}
		}
		default:
			cout << "\n\nYou do not see anything by the name " << targetEntity[1] << "\n";
			break;
		}
	}
	else
	{
		cout << "\n\nDead players can't perform actions. Execute command quit to quit the game.\n";
	}
}

void Player::showInventory(const vector<string>& targetEntity) const
{
	if (isAlive)
	{
		switch (targetEntity.size())
		{
		case 1:
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
						if (weapon != NULL && item->isEquipped)
						{
							cout << item->name << " equiped as a weapon.\n";
							break;
						}
						else
						{
							cout << item->name << "\n";
							break;
						}
					case SHIELD:
						if (shield != NULL && item->isEquipped)
						{
							cout << item->name << " equiped as a shield.\n";
							break;
						}
						else
						{
							cout << item->name << "\n";
							break;
						}
					case HELM:
						if (helm != NULL && item->isEquipped)
						{
							cout << item->name << " equiped as a helm.\n";
							break;
						}
						else
						{
							cout << item->name << "\n";
							break;
						}
					case VEST:
						if (vest != NULL && item->isEquipped)
						{
							cout << item->name << " equiped as a vest.\n";
							break;
						}
						else
						{
							cout << item->name << "\n";
							break;
						}
					case PANTS:
						if (pants != NULL && item->isEquipped)
						{
							cout << item->name << " equiped as pants.\n";
							break;
						}
						else
						{
							cout << item->name << "\n";
							break;
						}
					default:
						cout << item->name << "\n";
						break;
					}
				}
				break;
			}
			else
			{
				cout << "\n\nYou do not have any item in your inventory\n";
				break;
			}
		}
		case 2:
		{
			Creature* target = (Creature*)parent->getElement(CREATURE, targetEntity[1]);

			if (target != NULL)
			{
				target->showInventory();
				break;
			}
			else
			{
				cout << "\n\nYou do not see anything by the name " << targetEntity[1] << "\n";
				break;
			}
		}
		default:
			cout << "\n\nYou do not see anything by the name " << targetEntity[1] << "\n";
			break;
		}
	}
	else
	{
		cout << "\n\nDead players can't perform actions. Execute command quit to quit the game.\n";
	}
}

void Player::go(const vector<string>& targetExit)
{
	if (isAlive)
	{
		Exit* exit = getRoom()->getExit(targetExit[1]);

		if (exit != NULL)
		{
			if (!exit->locked) 
			{
				Room* newParent = exit->destination;
				changeParent(newParent);
				cout << "\n\nYou go in directon " << targetExit[1] << " and arrive at the " << exit->destination->name << "\n";
				cout << "---------------------------------------------------\n";
				newParent->lookAt();
			}
			else
			{
				cout << "\n\nYou try to go " << targetExit[1] << ", but it is locked. You need to find something to unlock it\n";
			}
			
		}
		else
		{
			cout << "\n\nYou do not see any path to take when you look " << targetExit[1] << "\n";
		}
	}
	else
	{
		cout << "\n\nDead players can't perform actions. Execute command quit to quit the game.\n";
	}
}

void Player::take(const vector<string>& targetItem)
{
	if (isAlive)
	{
		Item* item = (Item*)parent->getElement(ITEM, targetItem[1]);

		if (item == NULL)
		{
			if (targetItem.size() > 2)
			{
				Item* secondItem = (Item*)parent->getElement(ITEM, targetItem[3]);

				if (secondItem != NULL)
				{
					item = (Item*)secondItem->getElement(ITEM, targetItem[1]);
					
					if (item != NULL)
					{
						item->changeParent(this);
						cout << "\n\nYou take " << item->name << " from inside the " << secondItem->name << " located in the " << parent->name << "\n";
					}
					else
					{
						cout << "\n\nYou do not see " << targetItem[1] << " inside the " << secondItem->name << " located in the " << parent->name << "\n";
					}		
				}
				else
				{
					secondItem = (Item*)getElement(ITEM, targetItem[3]);
					if (secondItem != NULL)
					{
						item = (Item*)secondItem->getElement(ITEM, targetItem[1]);
						
						if(item != NULL)
						{
							item->changeParent(this);
							cout << "\n\nYou take " << item->name << " from inside the " << secondItem->name << " in your inventory\n";
						}
						else
						{
							cout << "\n\nYou do not see " << targetItem[1] << " inside the " << secondItem->name << " in your inventory\n";
						}
						
					}
					else
					{
						cout << "\n\nYou do not have " << targetItem[3] << " in your inventory and you cannot see it in the room\n";
					}
				}
			}
			else
			{
				cout << "\n\nYou do not see " << targetItem[1] << " in this room\n";
			}
		}
		else
		{
			item->changeParent(this);
			cout << "\n\nYou take " << item->name << "\n";
		}

	}
	else
	{
		cout << "\n\nDead players can't perform actions. Execute command quit to quit the game.\n";
	}
}

void Player::drop(const vector<string>& targetItem)
{
	if (isAlive)
	{
		Item* item = (Item*)getElement(ITEM, targetItem[1]);

		if (item != NULL)
		{
			if (item->canEquip && item->isEquipped)
			{
				unequip(targetItem);
			}

			if (targetItem.size() > 2)
			{
				Item* secondItem = (Item*)parent->getElement(ITEM, targetItem[3]);

				if (secondItem != NULL)
				{
					item->changeParent(secondItem);
					cout << "\n\nYou drop " << item->name << " inside " << secondItem->name << "\n";
				}
				else
				{
					secondItem = (Item*)getElement(ITEM, targetItem[3]);

					if (secondItem != NULL)
					{
						item->changeParent(secondItem);
						cout << "\n\nYou drop " << item->name << " inside the " << secondItem->name << "\n";
					}
					else
					{
						cout << "\n\nYou do not have " << targetItem[3] << " in your inventory and you cannot see it the room\n";
					}
				}
			}
			else
			{
				item->changeParent(parent);
				cout << "\n\nYou drop " << item->name << " in the " << parent->name << "\n";
			}
		}
		else
		{
			cout << "\n\nYou do not have " << targetItem[1] << " in your inventory\n";
		}
	}
	else
	{
		cout << "\n\nDead players can't perform actions. Execute command quit to quit the game.\n";
	}
}

void Player::loot(const vector<string>& targetDeadCreature)
{
	Creature* target = (Creature*)parent->getElement(CREATURE, targetDeadCreature[1]);

	if (target != NULL)
	{
		if (!target->isAlive)
		{
			list<Entity*> inventoryOfTarget;
			target->getAllOf(ITEM, inventoryOfTarget);

			if(inventoryOfTarget.size() > 0)
			{
				cout << "\n\nYou loot " << target->name << " and find:\n";

				for (list<Entity*>::const_iterator item = inventoryOfTarget.begin(); item != inventoryOfTarget.end(); ++item)
				{
					Item* temporal = (Item*)(*item);
					cout << "- " << temporal->name << "\n";
					temporal->isEquipped = false;
					temporal->changeParent(this);
				}
			}
			else
			{
				cout << "\n\nYou do not see anything to take from " << target->name << "\n";
			}
		}
		else
		{
			cout << "\n\n" << target->name << " is alive. You have to kill " << target->name << " before looting\n";
		}
	}
	else
	{
		cout << "\n\nYou cannot see " << targetDeadCreature[1] << "\n";
	}
}

void Player::lock(const vector<string>& targetExit)
{
	if (isAlive)
	{
		Exit* exit = getRoom()->getExit(targetExit[1]);

		if (exit != NULL)
		{
			if (!exit->locked)
			{
				Item* key = (Item*)getElement(ITEM, targetExit[3]);

				if (key != NULL)
				{
					if (key == exit->key)
					{
						exit->locked = true;
						cout << "\n\nYou locked " << exit->destination->name << "\n";
					}
				}
			}
			else
			{
				cout << "\n\n" << exit->destination->name << " already locked\n";
			}
		}
		else
		{
			cout << "\n\nYou cannot see anything when you look " << targetExit[1] << "\n";
		}
	}
	else
	{
		cout << "\n\nDead players can't perform actions. Execute command quit to quit the game.\n";
	}
}

void Player::unlock(const vector<string>& targetExit)
{
	if (isAlive)
	{
		Exit* exit = getRoom()->getExit(targetExit[1]);

		if (exit != NULL)
		{
			if (exit->locked)
			{
				Item* key = (Item*)getElement(ITEM, targetExit[3]);

				if (key != NULL)
				{
					if (key == exit->key)
					{
						exit->locked = false;
						cout << "\n\nYou unlocked  " << exit->destination->name << "\n";
					}
				}
				else
				{
					cout << "\n\nYou do not have the key to unlock " << targetExit[1] << ". Look for it first\n";
				}
			}
			else
			{
				cout << "\n\n" << exit->destination->name << " already unlocked\n";
			}
		}
		else
		{
			cout << "\n\nYou cannot see anything when you look " << targetExit[1] << "\n";
		}
	}
	else
	{
		cout << "\n\nDead players can't perform actions. Execute command quit to quit the game.\n";
	}
}

void Player::equip(const vector<string>& targetItem)
{
	if (isAlive)
	{
		Item* item = (Item*)getElement(ITEM, targetItem[1]);

		if (item != NULL)
		{
			if (item->canEquip)
			{
				switch (item->itemType)
				{
				case WEAPON:
					if (weapon == NULL)
					{
						weapon = item;
						cout << "\n\nYou equip " << item->name << " in your weapon slot\n";
						weapon->isEquipped = true;
					}
					else
					{
						cout << "\n\nYou already have " << weapon->name << " equipped. Please, unequip " << weapon->name << "\n";
					}					
					break;
				case SHIELD:
					if (shield == NULL)
					{
						shield = item;
						cout << "\n\nYou equip " << item->name << " in your shield slot\n";
						shield->isEquipped = true;
					}
					else
					{
						cout << "\n\nYou already have " << shield->name << " equipped. Please, unequip " << shield->name << "\n";
					}
					break;
				case HELM:
					if (helm == NULL)
					{
						helm = item;
						cout << "\n\nYou equip " << item->name << " in your helm slot\n";
						helm->isEquipped = true;
					}
					else
					{
						cout << "\n\nYou already have " << helm->name << " equipped. Please, unequip " << helm->name << "\n";
					}
					break;
				case VEST:
					if (vest == NULL)
					{
						vest = item;
						cout << "\n\nYou equip " << item->name << " in your vest slot\n";
						vest->isEquipped = true;
					}
					else
					{
						cout << "\n\nYou already have " << vest->name << " equipped. Please, unequip " << vest->name << "\n";
					}
					break;
				case PANTS:
					if (pants == NULL)
					{
						pants = item;
						cout << "\n\nYou equip " << item->name << " in your pants slot\n";
						pants->isEquipped = true;
					}
					else
					{
						cout << "\n\nYou already have " << pants->name << " equipped. Please, unequip " << pants->name << "\n";
					}
					break;
				default:
					break;
				}
			}
			else
			{
				cout << "\n\nYou cannot equip or unequip " << item->name << "\n";
			}
		}
		else
		{
			cout << "\n\nYou do not have " << targetItem[1] << " in your inventory\n";
		}
	}
	else
	{
		cout << "\n\nDead players can't perform actions. Execute command quit to quit the game.\n";
	}
}

void Player::unequip(const vector<string>& targetItem)
{
	if (isAlive)
	{
		Item* item = (Item*)getElement(ITEM, targetItem[1]);

		if (item != NULL)
		{
			if (item->canEquip)
			{
				switch (item->itemType)
				{
				case WEAPON:
					if(weapon == item)
					{
						weapon->isEquipped = false;
						weapon = NULL;
						cout << "\n\nYou unequip " << item->name << " from your weapon slot\n";
					}
					else
					{
						cout << "\n\nYou do not have " << item->name << " equipped\n";
					}
					break;
				case SHIELD:
					if (shield == item)
					{
						shield->isEquipped = false;
						shield = NULL;
						cout << "\n\nYou unequip " << item->name << " from your shield slot\n";
					}
					else
					{
						cout << "\n\nYou do not have " << item->name << " equipped\n";
					}
					break;
				case HELM:
					if (helm == item)
					{
						helm->isEquipped = false;
						helm = NULL;
						cout << "\n\nYou unequip " << item->name << " from your helm slot\n";
					}
					else
					{
						cout << "\n\nYou do not have " << item->name << " equipped\n";
					}
					break;
				case VEST:
					if (vest == item)
					{
						vest->isEquipped = false;
						vest = NULL;
						cout << "\n\nYou unequip " << item->name << " from your vest slot\n";
					}
					else
					{
						cout << "\n\nYou do not have " << item->name << " equipped\n";
					}
					break;
				case PANTS:
					if (pants == item)
					{
						pants->isEquipped = false;
						pants = NULL;
						cout << "\n\nYou unequip " << item->name << " from your pants slot\n";
					}
					else
					{
						cout << "\n\nYou do not have " << item->name << " equipped\n";
					}
					break;
				default:
					cout << "\n\nYou do not have " << item->name << " equipped\n";
				}
			}
			else
			{
				cout << "\n\nYou cannot equip or uneqip " << item->name << "\n";
			}
		}
		else
		{
			cout << "\n\nYou do not have " << targetItem[1] << " in your inventory\n";
		}
	}
	else
	{
		cout << "\n\nDead players can't perform actions. Execute command quit to quit the game.\n";
	}
}

void Player::attack(const vector<string>& targetCreature)
{
	Creature* target = (Creature*)parent->getElement(CREATURE, targetCreature[1]);

	if (target != NULL)
	{
		if (target->isAlive) 
		{
			targetToAttack = target;
			cout << "\n\nYou attack " << targetToAttack->name << "\n";
		}
		else
		{
			cout << "\n\nYou cannot attack a dead character\n";
		}
		
	}
	else
	{
		cout << "\n\nYou cannot see " << targetCreature[1] << "\n";
	}
}
