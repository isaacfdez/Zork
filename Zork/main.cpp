#include <iostream>
#include <sstream>
#include "World.h"

using namespace std;

int main()
{
	cout << "This is my Zork Test for accessing UPC's Masters degree in Advanced Programming for AAA videogames!\n";
	cout << "----------------------------------------------------------------------------------------------------\n\n\n";
	cout << "You awake from unconsciousness. You do not remember how you fell unconscious or where you are.\n";
	cout << "You look around and try take in as much as you can from your surroundings...\n\n";
	string input;
	vector<string> playerQuery;
	World game;

	cout << "Next move: ";
	getline(cin, input);
	cout << "\n";

	while(true)
	{
		if (input == "quit") 
		{
			break;
		}

		stringstream check1(input);

		string intermediate;
		while(getline(check1, intermediate, ' '))
		{
			playerQuery.push_back(intermediate);
		}

		if (playerQuery.size() > 0 && playerQuery[0].c_str() != "")
		{
			game.executeCommand(playerQuery);
		}

		if (playerQuery.size() >= 0)
		{
			playerQuery.clear();
			input = "";
			cout << "Next move: ";
			getline(cin, input);
			cout << "\n";
		}

	}

	cout << "Thanks for playing, come again soon!\n";
	return 0;
}

