// Duygu Tumer 24842

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Duygutumer_Tumer_Duygu_hw4_header.h"

using namespace std;

// Algorithm is:
// 1- go with your road algoritm (first north then east then south and at the end west)
// 2- if the cell is not "X" then push the cell coordinate
// 3- if you stack then pop the cells which you went before to continue

int GetDimension(ifstream & text, string & line, char & ch, string whatIwant)
{ 

	// this function will help me to get the size for dynamic array matrix
	int rowNum = 0;
	int columnNum = 0;
	while(getline(text, line))
	{
		//istringstream line2(line); -> not working and also I don't understand it' logic
		for(unsigned int i = 0; i < line.length(); i++)
		{
			rowNum ++;
		}
		columnNum++;
	}
	rowNum = rowNum / columnNum; 
	text.clear();
	text.seekg(0);
	if(whatIwant == "row")
	{
		return rowNum;
	}
	return columnNum;

}
void PuttingMatrix (ifstream & text, string & line, char & ch, char **matrix)
{
	int i = 0, j = 0;
	while(getline(text, line))
	{
		//istringstream input_file(line);
		for(unsigned int k = 0; k < line.length(); k++) //while(input_file >> ch)
		{
			ch = line[k];
			matrix[i][j] = ch;
			j++;
		}
		i ++;
		j = 0;
	}
}
void PrintMatrix (char **matrix, int & row, int & column)
{
	for(int i = 0; i < column; i++)
	{
		for(int j = 0; j < row; j++)
		{
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}
void AskRowAndCol(int & userColumn, int & userRow)
{
	bool askAgain1 = true;
	bool askAgain2 = true;
	string a;
	
	while(askAgain1)
	{
		askAgain1 = false;

		cout << "Enter the number of rows: ";
		cin >> userRow; 
		if (cin.fail()) { 
			cin.clear(); 
			cin >> a; 
			askAgain1 = true;
		}
		if(askAgain1)
			cout <<  a << " is not valid!" << endl;
		
		else if(userRow < 3)
		{
			cout <<  userRow << " is not valid!" << endl; //not true
			askAgain1 = true;
		}
		else
			askAgain1 = false;
	}
	while(askAgain2)
	{
		askAgain2 = false;
		cout << "Enter the number of columns: ";
		cin >> userColumn;
		if(cin.fail())
		{
			cin.clear();
			cin >> a;
			askAgain2 = true;
		}

		if(askAgain2)
			cout <<  a << " is not valid!" << endl;

		else if(userColumn < 3)
		{
			cout <<  userColumn << " is not valid!" << endl; //not true
			askAgain2 = true;
		}
		else
			askAgain2 = false;
	}
		
}
void AskStartPoint(coordinate & coo, int & userRow, int & userColumn, char ** matrix)
{
	bool askAgain = true;
	string a;

	while(askAgain) 
	{
		askAgain = false;
		cout << "Enter the starting point: ";
		cin >> coo.rowC; 
		if (cin.fail()) { 
			cin.clear(); 
			cin >> a; 
			askAgain = true;
		}

		cin >> coo.colC;
		if(cin.fail())
		{
			cin.clear();
			cin >> a;
			askAgain = true;
		}

		if(askAgain)
			cout << "Invalid coordinate!" << endl;
	
		else if((coo.rowC < 0 || coo.rowC > userRow-1) || (coo.colC > userColumn-1 || coo.colC < 0))
		{
			cout << "Invalid coordinate!" << endl;
			askAgain = true;
		}
	}	
}
void IsFillingCharValid(char & userChar)
{
	bool askAgain = true;
	string a;
	while(askAgain)
	{
		askAgain = false;
		cout << "Enter the filling char: ";
		cin >> userChar;
		if(cin.fail()) 
		{ 
			cin.clear(); 
			cin >> a; 
			askAgain = true;
		}
		if(askAgain)
			cout << "Filling char is not valid!" << endl;
		else if(userChar == 'x' || userChar == 'X')
		{
			cout << "Filling char is not valid!" << endl;
			askAgain = true;
		}
	}
}
void CheckingPath(coordinate & coo, int & userRow, int & userColumn, char ** matrix, char & userChar, DynIntStack & stack)
{
	bool check = false; // for while loop 

	while(!check)
	{
		// firstly, it must go right and check the values 
		if( !(coo.colC >= userColumn-1) && matrix[coo.rowC][coo.colC + 1] == ' ')
		{
			coo.colC ++;
			stack.push(coo);
			matrix[coo.rowC][coo.colC] = userChar;
			
		}
	
		// secondly it must go down
		else if(!(coo.rowC >= userRow-1) && matrix[coo.rowC + 1][coo.colC] == ' ')
		{
			coo.rowC ++;
			stack.push(coo);
			matrix[coo.rowC][coo.colC] = userChar;
		}

		//thirdly, it must go left
		else if(!(coo.colC <=  0) && matrix[coo.rowC][coo.colC-1] == ' ')
		{
			coo.colC -= 1;
			stack.push(coo);
			matrix[coo.rowC][coo.colC] = userChar;
		}
		// at last time, it has to go up and check
		else if(!(coo.rowC <= 0) && matrix[coo.rowC-1][coo.colC] == ' ' )
		{
			coo.rowC -= 1;
			stack.push(coo);
			matrix[coo.rowC][coo.colC] = userChar;
		}
	
		else //when I am stuck
		{
			if(!stack.isEmpty())
			{
				coo = stack.pop();
				
			}
			else
			{
				check = true;
			}
		}
	}


}

int main()
{
	ifstream text;
	string fileName, line, whatIwant;
	char ch;

	DynIntStack stack;

	int userColumn, userRow;
	AskRowAndCol(userColumn, userRow);
	
	cout << "Please enter file name: ";
	cin >> fileName;
	//fileName = "22x40.txt";
	
	text.open(fileName);
	
	while (text.fail())
	{
		cout << "Cannot find a file named " << fileName << endl;
		cout << "Please enter file name: ";
		cin >> fileName;
		text.open(fileName);
	}	

	/////////////////////////////////////////////
	//Two dimensional dynamic array creation
	
	int column = GetDimension(text, line, ch, "column");
	int row = GetDimension(text, line, ch, "row");
	 

	char** matrix = new char*[column]; //matrix
	for(int i = 0; i < column; i++) // column
	{
		matrix[i] = new char[row]; // row  
	}
	/////////////////////////////////////////////
	

	PuttingMatrix (text, line, ch, matrix);
	
	//PrintMatrix(matrix, row, column); // I shouldn't do this!!!
	
	
	coordinate coo;
	AskStartPoint(coo, userRow, userColumn, matrix); 
	// Ask user to enter the starting points
	
	if(matrix[coo.rowC][coo.colC] == ' ' )
	{
		char userChar; // takes char from user
		IsFillingCharValid(userChar); // controls it
		
		//////first coordinates///////
		stack.push(coo); // and pushes it into the stack (first coordinates)
		matrix[coo.rowC][coo.colC] = userChar; 
		/////////////////////////////

		CheckingPath(coo, userRow, userColumn, matrix, userChar, stack); // checks path algorithm  
		// and pushes the coordinates into stack
		
		PrintMatrix(matrix, row, column); // finally, it prints dynamic char matrix
		/*for(int i = 0; i < column; i++)
		{
			for(int j = 0; j < row; j++)
			{
				cout << matrix[i][j] << " ";
			}
			cout << endl;
		}*/
	}
	else
	{
		cout << "Starting point is already occupied." << endl;
		cout << "Terminating..." << endl;

	}
	
	for(int i = 0; i < column; i++)
	{
		delete [] matrix[i];
	}
	delete [] matrix;

	return 0;
}