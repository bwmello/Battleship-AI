/*
 * ConsoleScreen.cpp
 *
 *  Created on: Mar 12, 2012
 *      Authors:	Joseph DeWilde
 *                  Brent Mello
 *
 *  Last Modified:3/14/12
 */
#include "ConsoleScreen.h"
#include "Board.h"
#include <vector>
using std::vector;
#include "Ship.h"
#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::string;
#include "Message.h"
#include "Location.h"

void ConsoleScreen::displayPlayerBoard(const Board & board) const{
	cout << ' ' << ' ';
	for(int col = 0; col < board.getNumCols(); col++) cout << (char)(col + 'a') << ' ';
	cout << endl;
	for(int row = 0; row < board.getNumRows(); row++)
	{
		cout << (char)(row+'a');
		cout << '|';
		for(int col = 0; col < board.getNumCols(); col++)
		{
			if (board.isEmpty(row, col)){ // empty 
				if(board.isHit(row, col)) // missile attack here
					cout << 'm'; // miss
				else // no missile attack here
					cout << '_';
			}
			else{ // has ships
				if(board.isHit(row, col)) // missile attack here
					cout << 'H'; // hit
				else // no missile attack here
					cout << 'S';
			}
			cout << '|';
		}
		cout << endl;
	}
	cout << endl;
}

void ConsoleScreen::displayPlayerSunkenShips(const vector<Ship> & ships) const{
	cout << "The player's sunken ships:" << endl;
	for(auto itr = ships.begin(); itr != ships.end(); ++itr){
		if(itr->isSunk()){
			for(int i = 0; i < itr->getLength(); ++i){
				cout << 'S';
		}
		cout << endl;
		}
	}
	cout << endl;
}

void ConsoleScreen::displayEnemyBoard(const Board & board) const{
	cout << ' ' << ' ';
	for(int col = 0; col < board.getNumCols(); col++) cout << (char)(col + 'a') << ' ';
	cout << endl;
	for(int row = 0; row < board.getNumRows(); row++)
	{
		cout << (char)(row+'a');
		cout << '|';
		for(int col = 0; col < board.getNumCols(); col++)
		{
			if (board.isEmpty(row, col)){ // empty 
				if(board.isHit(row, col)) // missile attack here
					cout << 'm'; // miss
				else // no missile attack here
					cout << '_';
			}
			else{ // has ships
				if(board.isHit(row, col)) // missile attack here
					cout << 'H'; // hit
				else // no missile attack here
					cout << '_';
			}
			cout << '|';
		}
		cout << endl;
	}
	cout << endl;
}

void ConsoleScreen::displayEnemySunkenShips(const vector<Ship> & ships) const{
	cout << "The enemy's sunken ships:" << endl;
	for(auto itr = ships.begin(); itr != ships.end(); ++itr){
		if(itr->isSunk()){
			for(int i = 0; i < itr->getLength(); ++i){
				cout << 'S';
		}
		cout << endl;
		}
	}
	cout << endl;
}

void ConsoleScreen::displayMessage(Message::eventType bsEvent, Location location) const{
	string str = _message->composeMessage(bsEvent, location);
	cout << str << endl;
}

void ConsoleScreen::displayPlayerShips(const vector<Ship> & ships) const{
	cout << "Player's ships:" << endl;
	int num = 0;
	for(auto itr = ships.begin(); itr != ships.end(); ++itr){
		if(!itr->isPlaced()){
			cout << "(" << ++num << ") ";
			for(int i = 0; i < itr->getLength(); ++i){
				cout << 'S';
			}
			cout << endl;
		}
	}
	cout << endl;
}

void ConsoleScreen::display(){
	displayEnemySunkenShips(*_enemyShips);
	displayEnemyBoard(*_enemyBoard);
	displayPlayerSunkenShips(*_playerShips);
	displayPlayerBoard(*_playerBoard);
}