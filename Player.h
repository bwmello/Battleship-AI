/*
 * Player.h
 *
 *  Created on: Mar 4, 2012
 *      Authors:	Joseph DeWilde
 *                  Brent Mello
 *
 *  Last Modified:3/14/12
 */
#pragma once
#include "Location.h"
#include "Input.h"
#include "ConsoleInput.h"
#include "Board.h"
#include "Ship.h"
#include <vector>
using std::vector;

// Class Invariants:
// None
class Player{
public:
	Player(){
		_consoleInput = nullptr;
		_playerBoard = nullptr;
		_enemyBoard = nullptr;
		_ships = nullptr;
	}
	Location& getLocation();
	Ship& getShip();
	bool wantRandomBoard();


	void setInput(ConsoleInput & input){_consoleInput = &input;}
	void setPlayerBoard(Board & board){_playerBoard = &board;}
	void setEnemyBoard(Board & board){_enemyBoard = &board;}
	void setShips(vector<Ship> & ships){_ships = &ships;}
protected:
	ConsoleInput * _consoleInput;
	Board * _playerBoard;
	Board * _enemyBoard;
	vector<Ship> * _ships;
};