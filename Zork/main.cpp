#include <iostream>
#include <sstream>
#include "World.h"

using namespace std;

int main()
{
	string input;
	vector<string> playerQuery;
	World game;

	cout << "Next move: ";
	getline(cin, input);

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

		game.executeCommand(playerQuery);

		if (playerQuery.size() >= 0)
		{
			playerQuery.clear();
			input = "";
			cout << "Next move: ";
			getline(cin, input);
			cout << "\n";
		}

	}

	cout << "Good bye, come again soon\n";
	return 0;
}

