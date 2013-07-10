/*
 * Ship.h
 *
 *  Created on: Mar 4, 2012
 *      Authors:	Joseph DeWilde
 *                  Brent Mello
 *
 *  Last Modified:3/14/12
 */
#pragma once
#include "Location.h"
#include <string>
using std::string;

// class Invariants:
// _length > 0, _name != NULL
class Ship
{
public:
	Ship(int length = 1, string name = "ship");

	bool isSunk() const;
	bool isPlaced() const;
	void reset();
	void setLocation(Location location);
	void setVertical();
	void setHorizontal();
	void setLength(int length);
	void setName(string name);
	bool isVertical() const;
	Location getLocation() const;
	int getLength() const;
	string getName() const;
	void hit();

private:
	bool _isPlaced;
	int _length;
	int _remaining;
	bool _isVertical;
	Location _location;
	string _name;
};