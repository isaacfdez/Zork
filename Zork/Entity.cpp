#include "Entity.h"

Entity::Entity(const char* name, const char* desc, Entity* parent = NULL) : name(name), desc(desc), parent(parent)
{
	type = ENTITY;

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


void Entity::lookAt() const
{
	cout << name << "\n";
	cout << desc << "\n";
}

void Entity::changeParent(Entity* newParent)
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

bool Entity::existsEntity(Entity* otherEntity) const
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

bool Entity::existsType(Type type) const
{
	for (list<Entity*>::const_iterator gameElement = gameElements.begin(); gameElement != gameElements.end(); gameElement++)
	{
		if ((*gameElement)->type == type)
		{
			return true;
		}
	}

	return false;
}

Entity* Entity::getElement(Type type, const string& name) const
{
	for (list<Entity*>::const_iterator gameElement = gameElements.begin(); gameElement != gameElements.end(); gameElement++)
	{
		if ((*gameElement)->type == type && _stricmp((*gameElement)->name.c_str(), name.c_str()) == 0)
		{
			return *gameElement;
		}
	}
	return NULL;
}

Entity* Entity::getPlayer()
{
	for (list<Entity*>::const_iterator gameElement = gameElements.begin(); gameElement != gameElements.end(); gameElement++)
	{
		if ((*gameElement)->type == PLAYER)
		{
			return *gameElement;
		}
	}
	return NULL;
}

void Entity::getAllOf(Type type, list<Entity*>& elementsFound) const
{
	for (list<Entity*>::const_iterator gameElement = gameElements.begin(); gameElement != gameElements.end(); gameElement++)
	{
		if((*gameElement)->type == type)
		{
			elementsFound.push_back(*gameElement);
		}
	}
}
