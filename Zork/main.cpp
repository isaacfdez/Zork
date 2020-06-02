#include <iostream>
#include <conio.h>
#include <vector>
#include <string>
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
	playerQuery.reserve(10);
	World game;
	char key;

	playerQuery.push_back("look");

	while(1)
	{
		if (_kbhit() != 0)
		{
			key = _getch();
			if (key == '\b') // backspace
			{
				if (input.length() > 0)
				{
					input.pop_back();
					cout << '\b';
					cout << " ";
					cout << '\b';
				}
			}
			else if (key != '\r') // return
			{
				input += key;
				cout << key;
			}
			else
			{
				const char* str = input.c_str();

				do
				{
					const char* begin = str;

					while (*str != ' ' && *str)
						str++;

					playerQuery.push_back(string(begin, str));
				} while (0 != *str++);
			}
				
		}

		if (playerQuery.size() > 0 && _stricmp(playerQuery[0].c_str(), "quit") == 0)
		{
			break;
		}
				
		game.executeCommand(playerQuery);
		

		if (playerQuery.size() > 0)
		{
			playerQuery.clear();
			input = "";
			cout << "\nNext move: ";			
		}

	}

	cout << "\nThanks for playing, come again soon!\n";
	return 0;
}

