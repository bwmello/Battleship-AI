/*
 * Location.cpp
 *
 *  Created on: Mar 16, 2012
 *      Authors:	Joseph DeWilde
 *                  Brent Mello
 *
 *  Last Modified:3/17/12
 */

#include "Location.h"

bool Location::pixelsToEnemyLocation(int x, int y){
	//y 24 to 360.  x 396 to 781.2
	if(y < 24 || y > 360 || x < 396 || x > 781.2)
		return false;
	_row = (y-24)/33.6;
	_col = (x-396)/38.52;
	return true;
};