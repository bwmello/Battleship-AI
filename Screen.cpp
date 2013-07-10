#include "Screen.h"
#include <vector>
using std::vector;
#include "Ship.h"
#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::string;

void Screen::displayPlayerBoard(const Board & board) const{
	//cout << endl;
	cout << ' ' << ' ';
	for(int i = 0; i< board._column; i++) cout << (char)(i + 'a') << ' ';
	//cout << endl << ' ';
	//for(int i = 0; i< (board._column)*2 + 1; i++) cout << '_';
	cout << endl;
	for(int i = 0; i< board._column; i++)
	{
		cout << (char)(i+'a');
		cout << '|';
		for(int j = 0; j<board._row; j++)
		{
			if (board.isEmpty(j, i)){ // empty 
				cout << '_';
			}
			else{ // has ships
				cout << 'S';
			}
			cout << '|';
		}
		cout << endl;
	}
	//cout << ' ';
	//for(int i = 0; i < (board._column)*2 + 1; i++) cout << '-';
	cout << endl;
}

void Screen::displayPlayerSunkenShips(const vector<Ship> & ships) const{
	cout << "Sunken ships:" << endl;
	for(auto itr = ships.begin(); itr != ships.end(); ++itr){
		if(itr->isSunk()){
		for(int i = 0; i < itr->_shipLength; ++i){
			cout << 'S';
		}
		cout << endl;
		}
	}
	cout << endl;
}

void Screen::displayEnemyBoard(const Board & board) const{
}

void Screen::displayEnemySunkenShips(const vector<Ship> & ships) const{
}

void Screen::displayMessage(const string & str) const{
	cout << str << endl;
}