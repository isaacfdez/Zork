#ifndef __World__
#define __World__

#include <vector>
#include <string>
#include <list>
#include <time.h>

#define timeLoop 0.0f

class Entity;
class Player;

using namespace std;

class World
{
private: //variables
	Player* player;
	list<Entity*> gameElements;
	clock_t loopClock;

public: //functions
	World(); //constructor
	virtual ~World(); //destructor
	void executeCommand(vector<string>& playerQuery); //function that will execute the command prompted by the player
	void updateStatusOfGameElements(); //fucntion called by executeCommand function that updates the status of all game elements
};

#endif