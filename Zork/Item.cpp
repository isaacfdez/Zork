#include "Item.h"

Item::Item(const char* name, const char* desc, Entity* parent, const int valAttack, const int valBlock, const int valDefense, ItemType itemType, bool canEquip) : Entity(name, desc, parent), valAttack(valAttack), valBlock(valBlock), valDefense(valDefense), itemType(itemType), canEquip(canEquip)
{
	type = ITEM;
	isEquipped = false;
}

Item::~Item()
{
}

void Item::lookAt() const
{
	cout << "\n" << name << "\n";
	cout << desc << "\n";

	if (!gameElements.empty())
	{
		list<Entity*> itemsInside;
		getAllOf(ITEM, itemsInside);
		cout << name << " has inside: " << "\n";
		for (list<Entity*>::const_iterator item = itemsInside.begin(); item != itemsInside.end(); ++item)
		{
			cout << (*item)->name << "\n";
		}
	}
}

bool Item::isEmpty() const
{
	return gameElements.empty();
}
