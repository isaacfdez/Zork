#ifndef __Exit__
#define __Exit__

#include "Entity.h"
#include "Room.h"

using namespace std;

class Exit : public Entity //The list of Entities inherited from the class Entity for this class will be empty.
{
public: //variables
	Room* destination; //destination Room of this Exit
	std::string direction; //direction of this Exit
	bool locked; //boolean that indicates whether the exit is locked or unlocked

public: //functions
	Exit(const char* name, const char* desc, Room* origin, Room* destination, const char* direction, bool locked); //cosntructor
	virtual ~Exit(); //destructor
	void lookAt() const; //function that describes the Exit

};

#endif