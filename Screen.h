/*
 * Screen.h
 *
 *  Created on: Mar 6, 2012
 *      Authors:	Joseph DeWilde
 *                  Brent Mello
 *
 *  Last Modified:3/14/12
 */
#pragma once
#include "Board.h"
#include "Player.h"
#include "Ship.h"
#include <vector>
using std::vector;
#include <string>
using std::string;
#include "Location.h"
#include "Message.h"
#include "Ship.h"

// This class is responsible for displaying objects to the console by
// having objects be passed into its functions.

// Class Invariants:
// None
class Screen{
public:
	// Displays enemy's board with only hits/misses.
	void displayEnemyBoard(const Board & board) const;

	// Displays the player's sunken ships above their board.
	void displayPlayerSunkenShips(const vector<Ship> & ships) const;

	// Dipslays player's board with hits/misses and ships.
	void displayPlayerBoard(const Board & board) const;

	// Displays the enemy's sunken ships to the left of the 
	// player's board.
	void displayEnemySunkenShips(const vector<Ship> & ships) const;

	void displayMessage(Message::eventType bsEvent, Location location = Location(-1, -1)) const;

	void setMessage(Message & message){_message = &message;}

	// Displays everything except messages
	void display(); // TODO

	void setPlayerShips(vector<Ship> & ships){ _playerShips = &ships;}
	void setPlayerBoard(Board & board){ _playerBoard = &board;}
	void setEnemyShips(vector<Ship> & ships){ _enemyShips = &ships;}
	void setEnemyBoard(Board & board){ _enemyBoard = &board;}
protected:
	Message * _message;
	Board * _playerBoard;
	Board * _enemyBoard;
	vector<Ship> * _playerShips;
	vector<Ship> * _enemyShips;
};