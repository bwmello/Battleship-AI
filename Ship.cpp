/*
 * Ship.cpp
 *
 *  Created on: Mar 13, 2012
 *      Authors:	Joseph DeWilde
 *                  Brent Mello
 *
 *  Last Modified:3/14/12
 */
#include "Ship.h"
#include <string>
using std::string;
#include "Location.h"
#include <memory>
using std::unique_ptr;
using std::move;
#include "Location.h"

Ship::Ship(int length, string name){
	setLength(length);
	setName(name);
	reset();
}

bool Ship::isSunk() const{
	return !_remaining;
}

bool Ship::isPlaced() const{
	return _isPlaced;
}

void Ship::reset(){
	_remaining = _length;
	_isPlaced = false;
}

void Ship::setLocation(Location location){
	_location = move(location);
	_isPlaced = true;
}

void Ship::setVertical(){
	_isVertical = true;
}

void Ship::setHorizontal(){
	_isVertical = false;
}

void Ship::setLength(int length){
	if(length > 0){
		_length = length;
	}
}

void Ship::setName(string name){
	_name = name;
}

bool Ship::isVertical() const{
	return _isVertical;
}

Location Ship::getLocation() const{
	return _location;
}

int Ship::getLength() const{
	return _length;
}

string Ship::getName() const{
	return _name;
}

// Pre: It's up to the user to ensure that the player does not
// attack part of a ship twice in one location.
void Ship::hit(){
	--_remaining;
}
