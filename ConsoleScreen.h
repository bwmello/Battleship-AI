/*
 * ConsoleScreen.cpp
 *
 *  Created on: Mar 12, 2012
 *      Authors:	Joseph DeWilde
 *                  Brent Mello
 *
 *  Last Modified:3/14/12
 */
#pragma once
#include "Screen.h"
#include "Board.h"
#include "Ship.h"
#include <string>
using std::string;
#include <vector>
using std::vector;
#include "Location.h"
#include "Message.h"

// Class Invariants:
// None
class ConsoleScreen : public Screen{
public:
	// Displays enemy's board with only hits/misses.
	void displayEnemyBoard(const Board & board) const; // TODO

	// Displays the player's sunken ships above their board.
	void displayPlayerSunkenShips(const vector<Ship> & ships) const;

	// Displays player's board with hits/misses and ships.
	void displayPlayerBoard(const Board & board) const;

	// Displays the enemy's sunken ships to the left of the 
	// player's board.
	void displayEnemySunkenShips(const vector<Ship> & ships) const; // TODO

	void displayMessage(Message::eventType bsEvent, Location location = Location(-1, -1)) const;

	// Displays the players ships, used when customizing board.
	void displayPlayerShips(const vector<Ship> & ships) const;

	// Displays everything except messages and displayPlayerShips
	void display();
};