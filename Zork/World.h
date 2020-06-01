#ifndef __World__
#define __World__

#include <vector>
#include <string>

class Entity;
class Player;

using namespace std;

class World
{
private: //variables
	Player* player;
	vector<Entity*> gameElements;

public: //functions
	World(); //constructor
	virtual ~World(); //destructor
	void parser(vector<string>& playerQuery);
	void executeCommand(vector<string>& playerQuery);
};

#endif