#include "World.h"
#include "Entity.h"
#include "Player.h"
#include "Room.h"
#include "Item.h"
#include "Exit.h"
#include "NPC.h"

World::World()
{
	Room* dungeon = new Room("Dungeon", "An old prision chamber with several torture machines in a corner.");
	Room* clearing = new Room("Clearing", "You find yourself surronded by a forest as soon as you emerge from the dungeon.");
	Room* forest1 = new Room("Forest", "You don't see anything else but trees blocking your view.");
	Room* forest2 = new Room("Forest", "You seem to recognice some of the trees. You cannot help the feeling that you are walking in circles.");
	Room* forest3 = new Room("Forest", "You think this is a new part of the Forest. You think you are close to leave these trees behind.");
	Room* wall = new Room("Wall", "You see a tall wall that expands beyond your sight.");
	Room* armory = new Room("Armory", "You see the ruined remainings of an armory. Maybe there is something usefil here");
	Room* gates = new Room("Gates", "You see the gates that you hope will lead you to freedom.");
	Room* endgame = new Room("Endgame", "Congratulations! You won the game! You can execute quit to exit the game or wander this world for as long as you like.");

	Item* dagger = new Item("dagger", "a rusty old dagger", NULL, 3, 0, 0, WEAPON, true);
	Item* oakShield = new Item("oakshield", "a crumbling wood shield", NULL, 0, 2, 0, SHIELD, true);
	Item* leatherPants = new Item("leatherpants", "a pair of solid leather pants", NULL, 0, 0, 3, PANTS, true);
	Item* dungeonKey = new Item("dungeonkey", "a key to open or close the dungeon", NULL, 0, 0, 0, COMMON, false);

	list<Entity*> inventoryGuard;
	inventoryGuard.push_back(dagger);
	inventoryGuard.push_back(oakShield);
	inventoryGuard.push_back(leatherPants);
	inventoryGuard.push_back(dungeonKey);

	list<Entity*>emptyInventory;

	NPC* deadGuard = new NPC("guard", "a guard of the dungeon you are in", dungeon, inventoryGuard, 0, 0, true, false);

	NPC* bunny = new NPC("bunny", "a white rabbit going through the forest", clearing, emptyInventory, 5, 1, false, false);

	NPC* boar = new NPC("boar", "a wild brown boar searching the ground for truffles", forest1, emptyInventory, 20, 10, false, true);

	Item* leafCrown = new Item("leafcrown", "a crown made of leafs", forest2, 0, 0, 1, HELM, true);
	Item* chest = new Item("chest", "a chest with a broken lock", forest2, 0, 0, 0, COMMON, false);
	Item* leatherVest = new Item("leathervest", "a vest made of thick leather", armory, 0, 0, 5, VEST, true);
	Item* steelSword = new Item("steelsword", "a fine steel sword", armory, 18, 0, 0, WEAPON, true);
	Item* armoryKey = new Item("armorykey", "a key to open or close the armory", chest, 0, 0, 0, COMMON, false);

	Item* ironSword = new Item("ironsword", "a common iron sword", NULL, 10, 0, 0, WEAPON, true);
	Item* bronzeShield = new Item("bronzeshield", "a shiny bronze shield", NULL, 0, 5, 0, SHIELD, true);
	Item* ironVest = new Item("ironvest", "a heavy vest made of iron", NULL, 0, 0, 10, VEST, true);
	Item* gatesKey = new Item("gateskey", "a key to open the iron gates", NULL, 0, 0, 0, COMMON, false);

	list<Entity*> inventoryOgre;
	inventoryOgre.push_back(ironSword);
	inventoryOgre.push_back(bronzeShield);
	inventoryOgre.push_back(ironVest);
	inventoryOgre.push_back(gatesKey);

	NPC* ogre = new NPC("ogre", "a big bad ogre guarding the gates to freedom", gates, inventoryOgre, 32, 5, true, false);

	Exit* dungeonToClearing = new Exit("DungeonToClearing", "a set of old stone stairs", dungeon, clearing, "up", true, dungeonKey);
	Exit* clearingToDungeon = new Exit("ClearingToDungeon", "a set of old stone stairs", clearing, dungeon, "down", false, dungeonKey);

	Exit* clearingToForest1 = new Exit("ClearingToForest1", "a muddy path between the trees", clearing, forest1, "north", false, NULL);
	Exit* forest1ToClearing = new Exit("Forest1ToClearing", "a muddy path between the trees", forest1, clearing, "south", false, NULL);

	Exit* clearingToForest1_2 = new Exit("ClearingToForest1_2", "a dirt road between the trees", clearing, forest1, "west", false, NULL);
	Exit* forest1ToClearin_2 = new Exit("Forest1ToClearing_2", "a dirt road between the trees", forest1, clearing, "west", false, NULL);

	Exit* clearingToForest2 = new Exit("ClearingToForest2", "a road covered with fallen leafs from the trees", clearing, forest2, "east", false, NULL);
	Exit* forest2ToClearing = new Exit("Forest2ToClearing", "a road covered with fallen leafs from the trees", forest2, clearing, "west", false, NULL);

	Exit* clearingToForest2_2 = new Exit("ClearingToForest2_2", "a path blocked by vegetation", clearing, forest2, "south", true, NULL);
	Exit* forest2ToClearing_2 = new Exit("Forest2ToClearing_2", "a path blocked by vegetation", forest2, clearing, "east", true, NULL);

	Exit* forest1ToForest2 = new Exit("Forest1ToForest2", "a long hallway in the middle of the forest made by arching trees", forest1, forest2, "north", false, NULL);
	Exit* forest2ToForest1 = new Exit("Forest2ToForest1", "a long hallway in the middle of the forest made by arching trees", forest2, forest1, "south", false, NULL);

	Exit* forest1ToForest3 = new Exit("Forest1ToForest3", "a path covered by the shadows projected by the trees", forest1, forest3, "east", false, NULL);
	Exit* forest3ToForest1 = new Exit("Forest3ToForest1", "a path covered by the shadows projected by the trees", forest3, forest1, "west", false, NULL);

	Exit* forest2ToForest3 = new Exit("Forest2ToForest3", "a path blocked by thorny vines", forest2, forest3, "north", true, NULL);
	Exit* forest3ToForest2 = new Exit("Forest3ToForest2", "a path blocked by thorny vines", forest3, forest2, "south", true, NULL);;

	Exit* forest3ToWall = new Exit("Forest3ToWall", "a stone road", forest3, wall, "east", false, NULL);
	Exit* wallToForest3 = new Exit("WallToForest3", "a stone road", wall, forest3, "west", false, NULL);

	Exit* forest3ToGates = new Exit("Forest3ToGates", "a clear path", forest3, gates, "north", false, NULL);
	Exit* gatesToForest3 = new Exit("GatesToForest3", "a clear path", gates, forest3, "south", false, NULL);

	Exit* wallToArmory = new Exit("WallToArmory", "a trap door", wall, armory, "down", true, armoryKey);
	Exit* armoryToWall = new Exit("ArmoryToWall", "a trap door", armory, wall, "up", false, armoryKey);

	Exit* gatesToEndgame = new Exit("GatesToEndgame", "a pair of big iron gates", gates, endgame, "north", true, gatesKey);
	Exit* endgameToGates = new Exit("EndgameToGates", "a pair of big iron gates", endgame, gates, "south", false, gatesKey);

	Player* player = new Player("Hero", "an adventurer who travels the world in search of new experiences", dungeon, 50, 5, true);

	gameElements.push_back(dungeon);
	gameElements.push_back(clearing);
	gameElements.push_back(forest1);
	gameElements.push_back(forest2);
	gameElements.push_back(forest3);
	gameElements.push_back(wall);
	gameElements.push_back(armory);
	gameElements.push_back(gates);
	gameElements.push_back(endgame);
	gameElements.push_back(deadGuard);
	gameElements.push_back(bunny);
	gameElements.push_back(boar);
	gameElements.push_back(leafCrown);
	gameElements.push_back(chest);
	gameElements.push_back(leatherVest);
	gameElements.push_back(steelSword);
	gameElements.push_back(ogre);
	gameElements.push_back(dungeonToClearing);
	gameElements.push_back(clearingToDungeon);
	gameElements.push_back(clearingToForest1);
	gameElements.push_back(forest1ToClearing);
	gameElements.push_back(clearingToForest1_2);
	gameElements.push_back(forest1ToClearin_2);
	gameElements.push_back(clearingToForest2);
	gameElements.push_back(forest2ToClearing);
	gameElements.push_back(clearingToForest2_2);
	gameElements.push_back(forest2ToClearing_2);
	gameElements.push_back(forest1ToForest2);
	gameElements.push_back(forest2ToForest1);
	gameElements.push_back(forest1ToForest3);
	gameElements.push_back(forest3ToForest1);
	gameElements.push_back(forest2ToForest3);
	gameElements.push_back(forest3ToForest2);
	gameElements.push_back(forest3ToWall);
	gameElements.push_back(wallToForest3);
	gameElements.push_back(wallToArmory);
	gameElements.push_back(armoryToWall);
	gameElements.push_back(forest3ToGates);
	gameElements.push_back(gatesToForest3);
	gameElements.push_back(gatesToEndgame);
	gameElements.push_back(endgameToGates);
}

World::~World()
{
}

void World::executeCommand(vector<string>& playerQuery)
{
	switch (playerQuery.size())
	{
	case 1:
	{
		if ("help" == playerQuery[0].c_str())
		{
			player->showHelp();
			break;
		}
		else if ("look" == playerQuery[0].c_str())
		{
			player->lookAt(playerQuery);
			break;
		}
		else if ("stats" == playerQuery[0].c_str())
		{
			player->showStats(playerQuery);
			break;
		}
		else if ("inventory" == playerQuery[0].c_str())
		{
			player->showInventory(playerQuery);
			break;
		}
		else 
		{
			cout << "You don't seem te be able to perform this action. Try help\n";
			break;
		}
	}
	case 2:
	{
		if ("look" == playerQuery[0].c_str())
		{
			player->lookAt(playerQuery);
			break;
		}
		else if ("stats" == playerQuery[0].c_str())
		{
			player->showStats(playerQuery);
			break;
		}
		else if ("inventory" == playerQuery[0].c_str())
		{
			player->showInventory(playerQuery);
			break;
		}
		else if ("go" == playerQuery[0].c_str())
		{
			player->go(playerQuery);
			break;
		}
		else if ("take" == playerQuery[0].c_str())
		{
			player->take(playerQuery);
			break;
		}
		else if ("drop" == playerQuery[0].c_str())
		{
			player->drop(playerQuery);
			break;
		}
		else if ("loot" == playerQuery[0].c_str())
		{
			player->loot(playerQuery);
			break;
		}
		else if ("equip" == playerQuery[0].c_str())
		{
			player->equip(playerQuery);
			break;
		}
		else if ("unequip" == playerQuery[0].c_str())
		{
			player->unequip(playerQuery);
			break;
		}
		else if ("attack" == playerQuery[0].c_str())
		{
			player->attack(playerQuery);
			break;
		}
		else
		{
			cout << "You don't seem te be able to perform this action. Try help\n";
			break;
		}
	}
	case 3:
	{
		cout << "You don't seem te be able to perform this action. Try help\n";
		break;
	}
	case 4:
	{
		if ("take" == playerQuery[0].c_str())
		{
			player->take(playerQuery);
			break;
		}
		else if ("drop" == playerQuery[0].c_str())
		{
			player->drop(playerQuery);
			break;
		}
		else if ("lock" == playerQuery[0].c_str())
		{
			player->lock(playerQuery);
			break;
		}
		else if ("unlock" == playerQuery[0].c_str())
		{
			player->unlock(playerQuery);
			break;
		}
		else
		{
			cout << "You don't seem te be able to perform this action. Try help\n";
			break;
		}
	}
	default:
		cout << "You don't seem te be able to perform this action. Try help\n";
		break;
	}

	updateStatusOfGameElements();
}

void World::updateStatusOfGameElements()
{
	for (vector<Entity*>::const_iterator element = gameElements.begin(); element != gameElements.end(); ++element)
	{
		(*element)->updateStatus();
	}
}
