#include "Exit.h"


Exit::Exit(const char* name, const char* desc, Room* origin, Room* destination, const char* direction, bool locked, Item* key) : Entity(name, desc, (Entity*)origin), destination(destination), direction(direction), locked(locked)
{
	type = EXIT;
}

Exit::~Exit()
{
}

void Exit::lookAt() const
{
	cout << "Looking " << direction << " you can see " << desc << "\n";
}

