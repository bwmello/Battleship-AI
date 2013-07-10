/*
 * Message.cpp
 *
 *  Created on: Mar 8, 2012
 *      Authors:	Joseph DeWilde
 *                  Brent Mello
 *
 *  Last Modified:3/14/12
 */
#include "Message.h"
#include "Location.h"
#include <sstream>
using std::ostringstream;
#include <string>
using std::string;
#include <cctype>
using std::toupper;

string Message::composeMessage(eventType bsEvent, Location location){
	string message;
	if(bsEvent == PLAYERHIT || bsEvent == PLAYERMISS){
		message = _messages[PLAYERLAUNCH] + locationToString(location);
		if(bsEvent == PLAYERHIT){
			message += _messages[PLAYERHIT];
		}
		else{
			message += _messages[PLAYERMISS];
		}
	}
	else if(bsEvent == ENEMYHIT || bsEvent == ENEMYMISS){
		message = _messages[ENEMYLAUNCH] + locationToString(location);
		if(bsEvent == ENEMYHIT){
			message += _messages[ENEMYHIT];
		}
		else{
			message += _messages[ENEMYMISS];
		}
	}
	else{
		message = _messages[bsEvent];
	}
	return message;
}

// constructMessage
// This function constructs messages in the following format:
// "Launching missile at <location>...you have hit one of the enemy's ships!"
// "Launching missile at <location>...you have missed the enemy's ships!"
// "Incoming missile at <location>...the enemy has hit one of your ships!"
// "Incoming missile at <location>...the enemy has missed your ships!"
// "It is your turn..."
// "It is the enemy's turn..."
// "Deploy your fleet..."
// "The enemy is deploying his fleet..."
// "You have sunk one of the enemy's ships!"
// "The enemy has sunk one of your ships!"
// "The enemy has sunk all of your ships! You lose!"
// "You have sunk all of the enemy's ship! You win!"
void Message::constructMessageMap(){
	_messages[PLAYERLAUNCH] = "Launching missile at ";
	_messages[ENEMYLAUNCH] = "Incoming missile at ";
	_messages[PLAYERHIT] = "...you have hit one of " + _enemyName + "'s ships!";
	_messages[ENEMYHIT] = "..." + _enemyName + " has hit one of your ships!";
	_messages[PLAYERMISS] = "...you have missed " + _enemyName + "'s ships!";
	_messages[ENEMYMISS] = "..." + _enemyName + " has missed your ships!";
	_messages[PLAYERTURN] = "It is your turn...";
	_messages[ENEMYTURN] = "It is " + _enemyName + "'s turn...";
	_messages[PLAYERDEPLOY] = "Deploy your fleet...";
	_messages[ENEMYDEPLOY] = capitalizeStr(_enemyName) + " is deploying his fleet...";
	_messages[ENEMYSUNK] = capitalizeStr(_enemyName) + " has sunk one of your ships!";
	_messages[PLAYERSUNK] = "You have sunk one of " + _enemyName + "'s ships!";
	_messages[PLAYERWIN] = "You have sunk all of " + _enemyName + "'s ship! You win!";
	_messages[ENEMYWIN] = capitalizeStr(_enemyName) + " has sunk all of your ships! You lose!";
	_messages[ERRORDIAGONAL] = "The ship must be either vertical or horizontal on the board.";
	_messages[ERRORTAKEN] = "The ship must be placed on locations that are free of ships.";
	_messages[ERRORLENGTH] = "The distance between the locations must be the same as the selected ship.";
	_messages[ERRORHIT] = "You can't attack a location that has already been attacked.";
}

string& Message::capitalizeStr(string & str){
	string * capitalizedStr = new string(str);
	if(str.empty())
		return *capitalizedStr;
	(*capitalizedStr)[0] = toupper(str[0]);
	return *capitalizedStr;
}

string Message::locationToString(Location & location){
	ostringstream iss;
	iss << "(" << (char)(location.getRow() + 'a') << ", " << (char)(location.getCol() + 'a') << ")";
	return iss.str();
}