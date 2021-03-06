#ifndef __Player__
#define __Player__

#include "Creature.h"

using namespace std;

class Player : public Creature
{
public: //variables
	bool triggerDeath;
public: //functions
	Player(const char* name, const char* desc, Room* parent, int lifePoints, int baseAttack, bool humanoid);
	virtual ~Player();
	virtual void updateStatus(); //updates status of the Player
	virtual void showHelp() const; //command that shows available commands for the Player
	virtual void lookAt(const vector<string>& targetEntity); //command that makes the Player look it's environment or another Entity
	virtual void showStats(const vector<string>& targetEntity) const; //command that shows the statistics of the Player or target Creature
	virtual void showInventory(const vector<string>& targetEntity) const; //command that shows the inventory of the Player or target Creature
	virtual void go(const vector<string>& targetExit); //command that makes the Player go elsewhere if able
	virtual void take(const vector<string>& targetItem); //command that makes the Player take target Item from the Room or another Item if both are there
	virtual void drop(const vector<string>& targetItem); //command that makes the Player drop target Item from his inventory in the Room or inside another Item
	virtual void loot(const vector<string>& targetDeadCreature); //command that makes the Player take all the Items in target Creature if the latter is dead
	virtual void lock(const vector<string>& targetExit); //command that makes the Player lock target Exit
	virtual void unlock(const vector<string>& targetExit); //command that makes the Player unlock target Exit
	virtual void equip(const vector<string>& targetItem); //command that makes the Player equip an item from it's inventory in it's slot if it can be equiped
	virtual void unequip(const vector<string>& targetItem); //command that makes the Player unequip an item already equiped in one of it's slots
	virtual void attack(const vector<string>& targetCreature); //command that sets Player to attack another target Creature
};

#endif