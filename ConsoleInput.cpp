#include "ConsoleInput.h"
#include "Location.h"
#include "Ship.h"
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include "string"
using std::string;
using std::getline;
#include <cctype>
using std::tolower;
#include <algorithm>
using std::remove;

bool ConsoleInput::inBounds(char rowLetter, char colLetter){
	if((int)(rowLetter - 'a') > _board->getNumRows() || (int)(colLetter - 'a') > _board->getNumCols())
		return false;
	return true;
}

string ConsoleInput::getValidLocation(){
	string location;
	getline(cin, location);
	location.erase(remove(location.begin(), location.end(), ' '), location.end());
	while(location.size() != 3 || !isalpha(tolower(location[0])) || !isalpha(tolower(location[2])) || location[1] != ','){
		cout << "Invalid location, try again:";
		getline(cin, location);
		location.erase(remove(location.begin(), location.end(), ' '), location.end());
	}
	return location;
}

Location& ConsoleInput::getLocation(){
	cout << "Enter a location (e.g. \"a,b\"):";
	string input = getValidLocation(); // char,char
	while(!inBounds(input[0], input[2])){
		cout << "Location is not on the board, try again:";
		input = getValidLocation();
	}
	Location * location = new Location((int)(input[0] - 'a'), (int)(input[2] - 'a'));
	return *location;
}

int ConsoleInput::howManyShipsToPlace(){
	int shipsToPlace = 0;
	for(auto itr = _ships->begin(); itr != _ships->end(); ++itr)
		if(!itr->isPlaced())
			++shipsToPlace;
	return shipsToPlace;
}

// Pre: There must be at least one ship that needs to be placed.
Ship& ConsoleInput::getShip(){
	cout << "Choose a ship by number to place on the board:";
	int shipsToPlace = howManyShipsToPlace();
	int choice = getChoice(1, shipsToPlace);
	int index = 0;
	int numChoices = 0;
	for(auto itr = _ships->begin(); itr != _ships->end(); ++itr){
		if(!itr->isPlaced()){
			++numChoices;
		}
		if(numChoices == choice)
			break;
		++index;
	}
	return (*_ships)[index];
}

int ConsoleInput::getDigit(){
	string input;
	getline(cin, input);
	while(input.size() != 1 || (input[0] < '0' || input[0] > '9')){
		cout << "Invalid input, try again:";
		getline(cin, input);
	}
	return (int)(input[0] - '0');
}

int ConsoleInput::getChoice(int startChoice, int endChoice){
	int choice = getDigit();
	while(!(choice >= startChoice && choice <= endChoice)){
		cout << "Invalid choice, try again:";
		choice = getDigit();
	}
	return choice;
}

bool ConsoleInput::wantRandomBoard(){
	cout << "(1) Build your own board\n(2) Randomly generate a board" << endl;
	cout << "Choose an option:";
	return (getChoice(1, 2) == 2);
}