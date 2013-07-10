/*
 * Message.h
 *
 *  Created on: Mar 6, 2012
 *      Authors:	Joseph DeWilde
 *                  Brent Mello
 *
 *  Last Modified:3/14/12
 */
#pragma once
#include "Location.h"
#include <map>
using std::map;
#include <string>
using std::string;
#include <memory>
using std::move;

// Class Invariants:
// _enemyName != NULL, _playerName != NULL
class Message{
public:
	static const enum eventType {PLAYERLAUNCH, ENEMYLAUNCH, // Not passed in by user
							PLAYERHIT, ENEMYHIT,
							PLAYERMISS, ENEMYMISS,
							PLAYERTURN, ENEMYTURN, 
							PLAYERDEPLOY, ENEMYDEPLOY,
							ENEMYSUNK, PLAYERSUNK,
							PLAYERWIN, ENEMYWIN,
							ERRORDIAGONAL, ERRORTAKEN,
							ERRORLENGTH, ERRORHIT};

	Message(string playerName = "player", string enemyName = "the enemy"):
	_playerName(playerName), _enemyName(enemyName){
		constructMessageMap();
	}

	void setEnemyName(string enemyName){
		_enemyName = move(enemyName);
		constructMessageMap();
	}
	void setPlayerName(string playerName){
		_playerName = move(playerName);
		constructMessageMap();
	}

	// composeMessage
	// Takes a function and optional location
	// If the eventType is PLAYERLAUNCH/ENEMYLAUNCH this funciton will call foo with
	// the argument locaiton else it will just call foo.
	// This function will return the composed message as a reference to a string.
	string composeMessage(eventType bsEvent, Location location = Location(-1, -1));

private:

	map<eventType, string> _messages;
	string _playerName;
	string _enemyName;

	void constructMessageMap();
	
	string& capitalizeStr(string & str);

	string locationToString(Location & location);
};
