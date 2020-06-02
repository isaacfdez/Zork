#ifndef __Room__
#define __Room__

#include "Entity.h"

class Exit;
class Item;

using namespace std;

class Room : public Entity //The list of Entities inherited from the class Entity for this class will be all the elements present in the room.
{
public: //variables


public: //functions
	Room(const char* name, const char* desc); //constructor
	virtual ~Room(); //destructor
	void lookAt(); //function that describes the Room
	Exit* getExit(const string& direction) const; //function that returns an exit in the direction of the argument if exists
};

#endif