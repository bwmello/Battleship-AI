/*
 * ComputerPlayer.cpp
 *
 *  Created on: Mar 12, 2012
 *      Authors:	Joseph DeWilde
 *                  Brent Mello
 *
 *  Last Modified:3/14/12
 */
#include "ComputerPlayer.h"
#include "Location.h"
#include "Ship.h"
#include <cstdlib>
using std::rand;
using std::srand;
#include <ctime>
using std::time;
#include <algorithm>
using std::random_shuffle;
#include <memory>
using std::move;

Location& ComputerPlayer::getLocation(){
	return getSmartRandomLocation();
}

Location& ComputerPlayer::getRandomLocation(){
	srand(time(0));
	Location * randLocation = new Location();
	bool foundAvailableLocation = false;
	while(!foundAvailableLocation){
		randLocation->setRow(rand()%(_enemyBoard->getNumRows()));
		randLocation->setCol(rand()%(_enemyBoard->getNumCols()));
		int rowNum = randLocation->getRow();
		int colNum = randLocation->getCol();
		if(!_enemyBoard->isHit(rowNum, colNum))
			foundAvailableLocation = true;
	}
	return *randLocation;
}

Ship& ComputerPlayer::getShip(){
	for(auto itr = _ships->begin(); itr != _ships->end(); ++itr){
		if(!itr->isPlaced())
			return *itr;
	}
	throw ("Error: no more ships to place");
}


void ComputerPlayer::setResultOfAttack(bool hitShip){
	_hitShip = hitShip;
}

void ComputerPlayer::setTargetStatus(bool sunkShip){
	_sunkShip = sunkShip;
}

// Returns a location adjacent to current location (horizontally or vertically) that is random in its choice
// that is not already hit.
// There is a special case in which there are no available locations to attack around the current location, // TODO
// but 1 or more locations have already been hit (have ships that were hit by the enemy). The computer		// TODO
// must choose a direction to follow (made by current loc & adjacent hit loc) and return the next available loc. // TODO
Location& ComputerPlayer::getRandomAdjacentLocation(){
	vector<Direction> positions;
	positions.push_back(UP);
	positions.push_back(RIGHT);
	positions.push_back(DOWN);
	positions.push_back(LEFT);
	random_shuffle(begin(positions), end(positions));

	int row = _currAttackLoc.getRow();
	int col = _currAttackLoc.getCol();
	bool foundNextLocation = false;
	for(Direction dir : positions){
		int nextRow = row;
		int nextCol = col;
		switch(dir){
		case UP:
			--nextRow;
			break;
		case RIGHT:
			++nextCol;
			break;
		case DOWN:
			++nextRow;
			break;
		case LEFT:
			--nextCol;
		}
		if(inBounds(nextRow, nextCol) && isAvailable(nextRow, nextCol)){
			row = nextRow;
			col = nextCol;
			foundNextLocation = true;
			break;
		}
	}
	//if(!foundNextLocation)
		// TODO Handle Special Case
	Location * location = new Location(row, col);
	return *location;
}

bool ComputerPlayer::isAvailable(int row, int col){
	return (!_enemyBoard->isHit(row, col));
}

bool ComputerPlayer::hitShip(int row, int col){
	return (_enemyBoard->isHit(row, col) && !_enemyBoard->isEmpty(row, col));
}

bool ComputerPlayer::missedShip(int row, int col){
	return (_enemyBoard->isHit(row, col) && _enemyBoard->isEmpty(row, col));
}

Location& ComputerPlayer::getNextAdjacentLocation(){
	int deltaRow = 0;
	int deltaCol = 0;
	switch(_currDirection){
	case UP:
		--deltaRow;
		break;
	case DOWN:
		++deltaRow;
		break;
	case RIGHT:
		++deltaCol;
		break;
	case LEFT:
		--deltaCol;
	}
	int nextRow = _currAttackLoc.getRow() + deltaRow;
	int nextCol = _currAttackLoc.getCol() + deltaCol;
	if(!inBounds(nextRow, nextCol) || missedShip(nextRow, nextCol)){
		return getBacktrackedLocation();
	}
	else if(hitShip(nextRow, nextCol))
		return getFurtherLocation();
	Location * location = new Location(nextRow, nextCol);
	return *location;
}

Location& ComputerPlayer::getBacktrackedLocation(){
	_currDirection = (Direction)(((int)_currDirection + 2)%4);		// Opposite direction
	int nextRow = _currAttackLoc.getRow();
	int nextCol = _currAttackLoc.getCol();
	int deltaRow = 0;
	int deltaCol = 0;
	switch(_currDirection){
	case UP:
		--deltaRow;
		break;
	case DOWN:
		++deltaRow;
		break;
	case RIGHT:
		++deltaCol;
		break;
	case LEFT:
		--deltaCol;
	}
	do{
		nextRow += deltaRow;
		nextCol += deltaCol;
	}while(inBounds(nextRow, nextCol) && !missedShip(nextRow, nextCol) && !isAvailable(nextRow, nextCol));

	if(!inBounds(nextRow, nextCol) || missedShip(nextRow, nextCol)){ // There are multiple ships stacked vertically or horizontally
		setReminders(nextRow - deltaRow, nextCol - deltaCol); 
		return getSmartRandomLocation();
	}	
	Location * location = new Location(nextRow, nextCol);
	return *location;
}

Location& ComputerPlayer::getFurtherLocation(){
	int nextRow = _currAttackLoc.getRow();
	int nextCol = _currAttackLoc.getCol();
	int deltaRow = 0;
	int deltaCol = 0;
	switch(_currDirection){
	case UP:
		--deltaRow;
		break;
	case DOWN:
		++deltaRow;
		break;
	case RIGHT:
		++deltaCol;
		break;
	case LEFT:
		--deltaCol;
	}
	do{
		nextRow += deltaRow;
		nextCol += deltaCol;
	}while(inBounds(nextRow, nextCol) && !missedShip(nextRow, nextCol) && !isAvailable(nextRow, nextCol));

	if(!inBounds(nextRow, nextCol) || missedShip(nextRow, nextCol)){ // The rest of the ship is the other way
		return getBacktrackedLocation();
	}
	Location * location = new Location(nextRow, nextCol);
	return *location;
}

void ComputerPlayer::setDirection(){
	bool isVertical;
	if(_prevAttackLoc.getCol() == _currAttackLoc.getCol()){
		isVertical = true;
	}
	else{
		isVertical = false;
	}

	if(isVertical){
		if(_prevAttackLoc.getRow() > _currAttackLoc.getRow())
			_currDirection = UP;
		else
			_currDirection = DOWN;
	}
	else{
		if(_prevAttackLoc.getCol() < _currAttackLoc.getCol())
			_currDirection = RIGHT;
		else
			_currDirection = LEFT;
	}
}

Location& ComputerPlayer::getSmartRandomLocation(){
	if(!_reminder.empty() && !_reminded){
		random_shuffle(_reminder.begin(), _reminder.end());
		_prevAttackLoc.setRow(_reminder.back().getRow());
		_prevAttackLoc.setCol(_reminder.back().getCol());
		 _currAttackLoc = _prevAttackLoc; // Probably not needed
		_reminder.pop_back();
		_currentState = FOUNDSHIP;
		_sunkShip = false;
		_hitShip = false;
		_reminded = true;
	}

	switch(_currentState){
	case BEGIN:
		if(_sunkShip){
			_prevAttackLoc = _currAttackLoc;
			_currAttackLoc = getRandomLocation();
			resetState();
		}
		else if(_hitShip){
			_prevAttackLoc = _currAttackLoc;
			_currAttackLoc = getRandomAdjacentLocation(); // TODO: special case
			_currentState = FOUNDSHIP;
		}
		else{ // missed ship
			_prevAttackLoc = _currAttackLoc;
			_currAttackLoc = getRandomLocation();
		}
		break;
	case FOUNDSHIP:
		if(_sunkShip){
			_prevAttackLoc = _currAttackLoc;
			_currAttackLoc = getRandomLocation();
			resetState();
		}
		else if(_hitShip){
			setDirection();
			_prevAttackLoc = _currAttackLoc;
			_currAttackLoc = getNextAdjacentLocation();
			_currentState = FOUNDORIENTATION;
		}
		else{ // missed ship
			_currAttackLoc = _prevAttackLoc;
			_currAttackLoc = getRandomAdjacentLocation();
		}
		break;
	case FOUNDORIENTATION:
		setDirection();
		if(_sunkShip){
			_prevAttackLoc = _currAttackLoc;
			_currAttackLoc = getRandomLocation();
			resetState();
		}
		else if(_hitShip){
			_prevAttackLoc = _currAttackLoc;
			_currAttackLoc = getNextAdjacentLocation();
		}
		else{ // missed ship
			_startOfStack = _prevAttackLoc; // Might be ships placed in parallel
			_prevAttackLoc = _currAttackLoc;
			_currAttackLoc = getBacktrackedLocation();
			_currentState = DAMAGEDHALF;
		}
		break;
	case DAMAGEDHALF:
		setDirection();
		if(_sunkShip){
			_prevAttackLoc = _currAttackLoc;
			_currAttackLoc = getRandomLocation();
			resetState();
		}
		else if(_hitShip){
			_prevAttackLoc = _currAttackLoc;
			_currAttackLoc = getNextAdjacentLocation();
		}
		else{ // missed ship, dealing with multiple ships
			setReminders(_prevAttackLoc.getRow(), _prevAttackLoc.getCol());
			return getSmartRandomLocation();
		}
	}
	Location * location = new Location(_currAttackLoc.getRow(), _currAttackLoc.getCol());
	return *location;
}

// TODO Still doesn't add all of the intended locations that the cp should attack around
void ComputerPlayer::setReminders(int row, int col){
	_currDirection = (Direction)(((int)_currDirection + 2)%4);		// Opposite direction
	int deltaRow = 0;
	int deltaCol = 0;
	switch(_currDirection){
	case UP:
		--deltaRow;
		break;
	case DOWN:
		++deltaRow;
		break;
	case RIGHT:
		++deltaCol;
		break;
	case LEFT:
		--deltaCol;
	}
	while(row != _startOfStack.getRow() && col != _startOfStack.getCol()){
		Location * loc = new Location(row, col);
		_reminder.push_back(*loc);
		row += deltaRow;
		col += deltaCol;
	}
	Location * loc2 = new Location(_startOfStack.getRow(), _startOfStack.getCol());
	_reminder.push_back(*loc2);
}

void ComputerPlayer::resetState(){
	_currentState = BEGIN;
	_hitShip = false;
	_sunkShip = false;
	_reminded = false;
}

bool ComputerPlayer::inBounds(int row, int col){
	return (row >= 0 && row < _enemyBoard->getNumRows() && col >= 0 && col < _enemyBoard->getNumCols());
}