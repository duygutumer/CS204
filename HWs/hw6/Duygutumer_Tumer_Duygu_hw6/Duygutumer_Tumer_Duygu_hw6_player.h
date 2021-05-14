#ifndef _PLAYER_H
#define _PLAYER_H

#include "Duygutumer_Tumer_Duygu_hw6_board.h"
#include<string>
#include<iostream>

using namespace std;

class Player
{

public:
	Player();
	Player::Player(Board &theBoard, char owner, int x)
	: board(theBoard), identity(owner), direction(x)
	
	{ 
		row = 0;
		column = 0;
		
	};

	void move(int numOfCells);
	int getRow();
	int getCol();
	void claimOwnership();
	bool wins();

private:
	Board &board;
	char identity;
	int direction;
	int row;
	int column;
	
};

#endif