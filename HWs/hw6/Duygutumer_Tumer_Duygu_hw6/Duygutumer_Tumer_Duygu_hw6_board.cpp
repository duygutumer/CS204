#include "Duygutumer_Tumer_Duygu_hw6_board.h"
#include <iostream>

using namespace std;


Board::Board() // constructor
{
	for(int i=0; i<2; i++)
	{
		for(int j=0; j<6; j++)
		{
			theBoard[i][j] = '-';
		}
	}
}

char Board::getOwner(int row, int column)
{
	if(theBoard[row][column] == '-')
		return '-';
	else if(theBoard[row][column] == 'A')
		return 'A';
	else if(theBoard[row][column] == 'B')
		return 'B';
}

void Board::displayBoard()const
{
	cout << "Board: " << endl;
	for(int i=0; i<2; i++)
	{
		for(int j=0; j<6; j++)
		{
			cout << theBoard[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void Board::setOwner(int row, int column, char owner)
{
	theBoard[row][column] = owner;
}

bool Board::isFull()const
{
	for(int i=0; i<2; i++)
	{
		for(int j=0; j<6; j++)
		{
			if(theBoard[i][j] == '-')
			{
				return false;
			}
		}
	}
	return true;
}

int Board::countOwnedCells(char owner)
{
	int countCells = 0;
	for(int i=0; i<2; i++)
	{
		for(int j=0; j<6; j++)
		{
			if(theBoard[i][j] == owner)
			{
				countCells ++;
			}
		}
	}
	return countCells;
}