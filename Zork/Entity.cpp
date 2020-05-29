#include "Entity.h"

Entity::Entity(const char* name, const char* desc, Entity* parent = NULL) : name(name), desc(desc), parent(parent)
{
	type = entity;

	if (parent != NULL)
	{
		parent->gameElements.push_back(this);
	}
}

Entity::~Entity()
{
}

void Entity::updateStatus()
{
}


void Entity::LookAt() const
{
	cout << name << "\n";
	cout << desc << "\n";
}

void Entity::ChangeParent(Entity* newParent)
{
	if (parent != NULL) 
	{
		parent->gameElements.remove(this);
	}

	parent = newParent;

	if (parent != NULL)
	{
		parent->gameElements.push_back(this);
	}
}

bool Entity::exists(Entity* otherEntity) const
{
	for (list<Entity*>::const_iterator gameElement = gameElements.begin(); gameElement != gameElements.end(); gameElement++)
	{
		if ((*gameElement) == otherEntity)
		{
			return true;
		}
	}
	
	return false;
}

Entity* Entity::getElement(const string& name, Type type) const
{
	for (list<Entity*>::const_iterator gameElement = gameElements.begin(); gameElement != gameElements.end(); gameElement++)
	{
		if ((*gameElement)->type == type && _stricmp((*gameElement)->name.c_str(), name.c_str()) == 0)
		{
			return *gameElement;
		}
	}
}

void Entity::getAllOf(Type type, list<Entity*>& elementsFound)
{
	for (list<Entity*>::const_iterator gameElement = gameElements.begin(); gameElement != gameElements.end(); gameElement++)
	{
		if((*gameElement)->type == type)
		{
			elementsFound.push_back(*gameElement);
		}
	}
}
