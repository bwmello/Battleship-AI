/*
 * consoleInput.h
 *
 *  Created on: Mar 9, 2012
 *      Authors:	Joseph DeWilde
 *                  Brent Mello
 *
 *  Last Modified:3/14/12
 */
#pragma once

#include "Input.h"
#include "Board.h"
#include "Location.h"
#include "Ship.h"
#include <vector>
using std::vector;

// Class Invariants:
// None
class ConsoleInput : public Input{
public:
	ConsoleInput():Input(){}
	Location& getLocation();
	Ship& getShip();
	bool wantRandomBoard();
	void setShips(vector<Ship> & ships){_ships = &ships;}
	void setBoard(Board & board){_board = &board;}

private:
	string getValidLocation();
	bool inBounds(char, char);
	int howManyShipsToPlace();
	int getDigit();
	int getChoice(int, int);
};