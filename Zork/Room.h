#ifndef __Room__
#define __Room__

#include "Entity.h"

class Exit;

using namespace std;

class Room : public Entity
{
public: //variables


public: //functions
	Room(const char* name, const char* desc); //constructor
	~Room(); //destructor
	void LookAt(); //function that describes the Room
	Exit* getExit(const string& direction) const; //function that returns an exit in the direction of the argument if exists
};

#endif