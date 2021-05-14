#include "Duygutumer_Tumer_Duygu_hw6_player.h"
#include "Duygutumer_Tumer_Duygu_hw6_board.h"
#include<iostream>
#include<string>

using namespace std;

void Player::move(int numOfCells)
{
	int count = 0;
	while(count < numOfCells)
	{
		if(direction == 1)
		{
			if(row == 0 && column < 5)
			{
				column++;
				count ++;
			}
			else if(row == 0 && column == 5)
			{
				row++;
				count++;
			}
			else if(row == 1 && column > 0)
			{
				column --;
				count++;
			}
			else if(row == 1 && column == 0)
			{
				row --;
				count++;
			}
		}
		else if(direction == 0)
		{
			if(row == 1 && column < 5)
			{
				column++;
				count ++;
			}
			else if(row == 0 && column == 0)
			{
				row++;
				count++;
			}
			else if(row == 0 && column > 0)
			{
				column --;
				count++;
			}
			else if(row == 1 && column == 5)
			{
				row --;
				count++;
			}
		}
	}
}

void Player::claimOwnership()
{
	if(board.getOwner(row, column) == '-')
	{
		board.setOwner(row, column, identity);
	}
}

bool Player::wins()
{
	if(board.countOwnedCells(identity) > 6)
	{
		return true;
	}
	return false;
}

int Player::getRow()
{
	return row;
}

int Player::getCol()
{
	return column;
}