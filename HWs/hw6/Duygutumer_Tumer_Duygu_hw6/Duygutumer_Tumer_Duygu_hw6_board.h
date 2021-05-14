#ifndef _BOARD_H
#define _BOARD_H

using namespace std;

class Board
{

private:
	char theBoard[2][6];
public:
	Board();
	void displayBoard()const;
	char getOwner(int row, int column);
	void setOwner(int row, int column, char owner);
	bool isFull()const;
	int countOwnedCells(char owner);

};

#endif
