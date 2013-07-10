/*
 * HumanPlayer.h
 *
 *  Created on: Mar 4, 2012
 *      Authors:	Joseph DeWilde
 *                  Brent Mello
 *
 *  Last Modified:3/14/12
 */
#pragma once
#include "Player.h"
#include "Location.h"
#include "Ship.h"
#include "Board.h"

// Class Invariants:
// None
class HumanPlayer : public Player
{
public:
	HumanPlayer() : Player(){}
	Location& getLocation(); // Calls getLocation of input, lets it handle input
	Ship& getShip(); // Calls getLocation of input, lets it handle input
	bool wantRandomBoard(); // Calls wantRandomBoard of input to let it handle input
};