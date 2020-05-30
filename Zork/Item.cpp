#include "Item.h"

Item::Item(const char* name, const char* desc, Entity* parent, const int valAttack, const int valBlock, bool canEquip) : Entity(name, desc, parent), valAttack(valAttack), valBlock(valBlock), canEquip(canEquip)
{
	type = ITEM;
}

Item::~Item()
{
}

void Item::lookAt() const
{
	cout << name << "\n";
	cout << desc << "\n";

	if (!gameElements.empty())
	{
		list<Entity*> itemsInside;
		getAllOf(ITEM, itemsInside);
		cout << name << "has inside: " << "\n";
		for (list<Entity*>::const_iterator item = itemsInside.begin(); item != itemsInside.end(); ++item)
		{
			cout << (*item)->name << "\n";
		}
	}
}

int Item::getValAttack()
{
	if (valAttack != NULL)
	{
		return valAttack;
	}

	return 0;
}

int Item::getValBlock()
{
	if (valBlock != NULL)
	{
		return valBlock;
	}
	return 0;
}

void Item::setValAttack(int value)
{
	valAttack = value;
}

void Item::setValBlock(int value)
{
	valBlock = value;
}

bool Item::isEmpty() const
{
	return gameElements.empty();
}
