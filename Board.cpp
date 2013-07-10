/*
 * Board.cpp
 *
 *  Created on: Mar 4, 2012
 *      Authors:	Joseph DeWilde
 *                  Brent Mello
 *
 *  Last Modified:3/14/12
 */
#include "Board.h"
#include <vector>
using std::vector;
#include "Ship.h"
#include "Location.h"
#include <stdexcept>
using std::out_of_range;

Board::Board(int row, int col):_row(row),_column(col),_shipsLeft(0){
	for(int i = 0; i < _row; i++){
		Board::Row rowVec;
		for(int j = 0; j < _column; j++){
			Box b = {false, nullptr};
			rowVec.push_back(std::move(b)); 
		}
		_grid.push_back(rowVec);
	}
	_sunkShip = false;
}

void Board::placeShipRandomly(Ship & ship){
	bool isShipPlaced = false;
	while(!isShipPlaced){
		giveRandomLocation(ship);
		isShipPlaced = tryPlacingShip(ship);
	}
}

void Board::giveRandomLocation(Ship & ship){
	int orientation = rand()%2;
	if(orientation == 0)
		ship.setHorizontal();
	else
		ship.setVertical();
	Location shipLocation;
	if(ship.isVertical()){
		shipLocation.setRow(rand()%(_row - ship.getLength()));
		shipLocation.setCol(rand()%(_column));
	}
	else{
		shipLocation.setRow(rand()%(_row));
		shipLocation.setCol(rand()%(_column - ship.getLength()));
	}
	ship.setLocation(shipLocation);
}

// tryPlacingShip
// If the ship is vertical then it tries placing the ship from top to bottom.
// If the ship is horizontal then it tries placing the ship from left to right.
bool Board::tryPlacingShip(Ship & ship){
	Location shipLocation = ship.getLocation();
	int shipRow = shipLocation.getRow();
	int shipCol = shipLocation.getCol();
	if(ship.isVertical()){
		for(int row = shipRow; row < shipRow + ship.getLength(); ++row){
			if(!isEmpty(row, shipCol))
				return false;
		}
		for(int row = shipRow; row < shipRow + ship.getLength(); ++row){
			_grid[row][shipCol]._shipPtr = &ship;
		}
	}
	else{
		for(int col = shipCol; col < shipCol + ship.getLength(); ++col){
			if(!isEmpty(shipRow, col))
				return false;
		}
		for(int col = shipCol; col < shipCol + ship.getLength(); ++col){
			_grid[shipRow][col]._shipPtr = &ship;
		}
	}
	++_shipsLeft;
	return true;
}

bool Board::isEmpty(int rowNum, int colNum) const{
	if(!inBounds(rowNum, colNum))
		throw out_of_range("Error:Out of bounds in accessing _grid in Board.h");
	return (_grid[rowNum][colNum]._shipPtr == nullptr);
}

bool Board::fireMissile(const Location & location){
	int rowNum = location.getRow();
	int colNum = location.getCol();
	if(!inBounds(rowNum, colNum))
		throw out_of_range("Error:Out of bounds in accessing _grid in Board.h");
	if(_grid[rowNum][colNum]._isHit)
		throw ("Error: Already attacked this location.");
	_grid[rowNum][colNum]._isHit = true;
	if(!isEmpty(rowNum, colNum)){
		_grid[rowNum][colNum]._shipPtr->hit();
		if(_grid[rowNum][colNum]._shipPtr->isSunk()){
			_sunkShip = true;
			--_shipsLeft;
		}
		return true;
	}
	_sunkShip = false;
	return false;
}

void Board::placeShipsRandomly(vector<Ship> & ships){
	srand(static_cast<unsigned>(time(0)));
	for(auto ship = begin(ships); ship != end(ships); ++ship){
		try{
			placeShipRandomly(*ship);
		}catch(...){
			// what if board is not big enough
			// give player a message that they need a bigger board

			// what if this current randomization of placing ships is impossible i.e. 
			// the randomization needs redoing
			// resetBoard
			// try placing ships again
		}
	}
}

void Board::reset(){
	for(auto row = _grid.begin(); row != _grid.end(); ++row){
		for(auto col = row->begin(); col != row->end(); ++col){
			col->_isHit = false;
			col->_shipPtr = nullptr;
		}
	}
	_shipsLeft = 0;
	_sunkShip = false;
}

bool Board::isHit(const Location & location) const{
	return isHit(location.getRow(), location.getCol());
}

bool Board::isHit(int rowNum, int colNum) const{
	if(!inBounds(rowNum, colNum))
		throw out_of_range("Error:Out of bounds in accessing _grid in Board.h");
	return _grid[rowNum][colNum]._isHit;
}

int Board::getNumCols() const{
	return _column;
}

int Board::getNumRows() const{
	return _row;
}

bool Board::inBounds(int rowNum, int colNum) const{
	return (rowNum >= 0 && rowNum < _row && colNum >= 0 && colNum < _column);
}