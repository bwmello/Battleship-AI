/*
 * Board.h
 *
 *  Created on: Mar 4, 2012
 *      Authors:	Joseph DeWilde
 *                  Brent Mello
 *
 *  Last Modified:3/14/12
 */
#pragma once

#include <vector>
#include <memory>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "Location.h"
#include "Ship.h"
using std::cout;
using std::endl;
using std::vector;

struct Box{
	bool _isHit;
	Ship * _shipPtr;
};

// Class Invariants:
// _row > 0, _column > 0

class Board
{
private:
	int _row;
	int _column;
	int _shipsLeft;
	typedef vector<Box> Row;
	vector<Row> _grid;
	bool _sunkShip; // true == if a ship was sunk with previous attack

public:
	Board(int row=10, int column=10);
	void placeShipsRandomly(vector<Ship> & ships);

	bool tryPlacingShip(Ship & ship);
	bool isEmpty(int rowNum, int colNum) const;

	bool fireMissile(const Location & location);
	bool hasLost(){return (_shipsLeft == 0);}
	bool hasSunkShip(){return _sunkShip;} // determine if last attack sunk a ship
	void reset();
	bool isHit(const Location & location) const;
	bool isHit(int rowNum, int colNum) const;
	int getNumRows() const;
	int getNumCols() const;

private: // Helper functions
	bool inBounds(int rowNum, int colNum) const;
	void placeShipRandomly(Ship & ship);
	void giveRandomLocation(Ship & ship);
};