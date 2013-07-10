/*
 * HumanPlayer.cpp
 *
 *  Created on: Mar 13, 2012
 *      Authors:	Joseph DeWilde
 *                  Brent Mello
 *
 *  Last Modified:3/14/12
 */
#include "HumanPlayer.h"
#include "Location.h"
#include "Ship.h"
#include "Input.h"
#include "ConsoleInput.h"

Location& HumanPlayer::getLocation(){
	return _consoleInput->getLocation();
}

Ship& HumanPlayer::getShip(){
	return _consoleInput->getShip();
}

bool HumanPlayer::wantRandomBoard(){
	return _consoleInput->wantRandomBoard();
}