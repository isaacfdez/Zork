#ifndef __Exit__
#define __Exit__

#include "Entity.h"
#include "Room.h"

using namespace std;

class Exit : public Entity
{
public: //variables
	Room* destination;
	std::string direction;
	bool locked;

public: //functions
	Exit(const char* name, const char* desc, Room* origin, Room* destination, const char* direction, bool locked); //cosntructor
	~Exit(); //destructor
	void lookAt() const; //function that describes the Exit

};

#endif