/*
 * ComputerPlayer.cpp
 *
 *  Created on: Mar 12, 2012
 *      Authors:	Joseph DeWilde
 *                  Brent Mello
 *
 *  Last Modified:3/14/12
 */
#pragma once
#include "Player.h"
#include "Board.h"
#include "Location.h"
#include "Ship.h"
#include <vector>
using std::vector;




// Class Invariants:
// None
class ComputerPlayer : public Player
{
public:
	ComputerPlayer() : Player(){
		_currentState = BEGIN;
		_hitShip = false;
		_sunkShip = false;
		_reminded = false;
	}
	Location& getLocation(); // Calls getRandomLocation()
	Ship& getShip();
	bool wantRandomBoard() { return true;} // Will randomly generate their board.
	int getNumShips(){return _ships->size();}
	void setResultOfAttack(bool hitShip);
	void setTargetStatus(bool isSunk);
	enum Direction {UP, RIGHT, DOWN, LEFT};

private:
	Location& getRandomAdjacentLocation(); // Get a location up,down,left, or right of last location
	Location& getNextAdjacentLocation(); // Go in currunt direction to find next available location
	Location& getBacktrackedLocation(); // Go the other direction to find available location
	Location& getFurtherLocation(); // Go over location that was hit & ship was there
	Location& getRandomLocation(); // Called by getLocation
	Location& getSmartRandomLocation(); // Called by getLocation 

	void setDirection(); // set current direction based on previous and current attacks
	Direction _currDirection;
	bool _sunkShip;
	bool _hitShip;
	void resetState();
	Location _prevAttackLoc;
	Location _currAttackLoc;

	bool isAvailable(int,int); // is location availabe to attack
	bool hitShip(int,int); // was location hit & if so was there a ship there
	bool missedShip(int,int); // was location hit & if so was there no ship there
	bool inBounds(int,int); // is passed coordinates of location on the board

	void setReminders(int row, int col); // Set reminders to attack passed location to _startOfStack
	Location _startOfStack; // stack refers to multiple ships placed in parallel and adjacent to each other
	vector<Location> _reminder; // Holds all of the locations that the cp should attack
	bool _reminded; // true if cp is currently attack around a location that it was reminded to attack

	enum attackState {BEGIN, FOUNDSHIP, FOUNDORIENTATION, DAMAGEDHALF}; 
	attackState _currentState;
};