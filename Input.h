/*
 * Input.h
 *
 *  Created on: Mar 9, 2012
 *      Authors:	Joseph DeWilde
 *                  Brent Mello
 *
 *  Last Modified:3/14/12
 */
#pragma once
#include "Location.h"
#include "Ship.h"
#include <vector>
using std::vector;
#include "Board.h"


// Class Invariants:
// None
class Input{
public:
	Input(){}
	Location& getLocation();
	Ship& getShip();
	bool wantRandomBoard();
	void setShips(vector<Ship> & ships);
	void setBoard(Board & board);
protected:
	vector<Ship> * _ships;
	Board * _board;
};