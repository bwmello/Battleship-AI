/*
 * Location.h
 *
 *  Created on: Mar 8, 2012
 *      Authors:	Joseph DeWilde
 *                  Brent Mello
 *
 *  Last Modified:3/14/12
 */
#pragma once

// Class Invariants:
// None
class Location{
public:
	Location(int row = -1, int col = -1):_row(row), _col(col){}
	int getRow() const {return _row;}
	int getCol() const {return _col;}
	void setRow(int row) {_row = row;}
	void setCol(int col) {_col = col;}
	bool pixelsToEnemyLocation(int x, int y);

private:
	int _row, _col;
};