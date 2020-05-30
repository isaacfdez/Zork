#include "Exit.h"


Exit::Exit(const char* name, const char* desc, Room* origin, Room* destination, const char* direction, bool locked) : Entity(name, desc, (Entity*)origin), destination(destination), direction(direction), locked(locked)
{
	type = EXIT;
}

Exit::~Exit()
{
}

void Exit::lookAt() const
{
	cout << "Looking " << name << "you can see" << desc <<" that leads to the " << destination->name << "\n";
}

