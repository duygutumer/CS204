#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct coordinate
{
	// x, y are locations to check the matrix

	int x;
	int y;
	/*
	coordinate::coordinate()
		: x(0), y(0) {};

	coordinate::coordinate(int d, int _y)
	{
		x = d;
		y = _y;
	}
	*/
};

bool CheckMatrixChr(ifstream & inputMatrix, string matrixLine, string fileName, bool & checkingAllFactors)
{
	// this fuction will check the matrix's characters

	char chr;

	while(getline(inputMatrix, matrixLine))
	{
		istringstream input_file (matrixLine); // newInput is the matrix's rows
		while(input_file >> chr) // characters are the columns of myMatrix
		{
			if (chr != 'x' && chr != 'o')
			{
				cout << fileName << " includes invalid char(s)" << endl;
				checkingAllFactors = false;
				return checkingAllFactors;
			}
		}
	}
	
	inputMatrix.clear();
	inputMatrix.seekg(0);
}
bool NumOfRowAndColm(ifstream & inputMatrix, string matrixLine, int & row, int & column, string fileName)
{
	//this function will provide number of rows and columns
	char chr; 
	int columnNum = 0; // for first row
	int columnAnum = 0; // for other rows
	bool sameCharEachRow = true; // same amount of char 

	while(getline(inputMatrix, matrixLine))
	{
		row++;
		istringstream newInput (matrixLine); // newInput is the matrix's rows
		while(newInput >> chr) // characters are the columns of myMatrix
		{	
			column++;
			columnNum++; // for the first row number of char
		}
		if(columnAnum == columnNum || columnAnum == 0)
		{
			columnAnum = columnNum;
			sameCharEachRow = true;
			columnNum = 0;
		}
		else
		{
			sameCharEachRow = false;
			break;
		}
	}
	inputMatrix.clear();
	inputMatrix.seekg(0);

	column = column / row;
	
	if(sameCharEachRow)
		return true;
	else
	{
		cout << fileName << " is invalid matrix, does not contain same amount of char" << endl;
		cout << "each row!" << endl;
		return false;
	}
}
void PuttingInMatrix(ifstream & inputMatrix, string matrixLine, vector <vector<char>> & myMatrix)
{
	// this func will provide to put all chars in matrix.txt in to myMatrix
	char characters;
	int horizontal = 0, vertical = 0;

	while (getline(inputMatrix, matrixLine))
	{
		istringstream newInput (matrixLine); // newInput is the matrix's horizontal lines 

		while(newInput >> characters)
		{
			myMatrix[vertical][horizontal] = characters; //I am putting the char in my vector
			horizontal ++;
		}
		horizontal = 0;	// I have to make it zero because it will be out of range for example [0][0] , [0][1] , [0][2] and now [1][0]...
		vertical ++;
	}
	inputMatrix.clear();
	inputMatrix.seekg(0);
}
void PrintingMatrix (vector <vector<char>> myMatrix, int row, int column)
{
	for (int i = 0; i < row; i++) // for row
	{
		for (int k = 0; k < column; k++) // for column
		{
			cout << myMatrix[i][k] << " " ;
		}
		cout << endl;
	}
}
bool AskingCoordinates(int & x, int & y, int row, int column, vector <coordinate> & coordinates, vector <vector<char>> & myMatrix)
{
	bool askAgain = true;
	string a;

	while(askAgain) // ask until good input
	{
		askAgain = false;
		cout << "Please enter starting coordinates, first row X then column Y: " ;
		cin >> x; 
		if (cin.fail()) { //when I try to put a string in integer it will give error
			cin.clear(); //that is why I have to clear the error message
			cin >> a; // then i must put the string in a string
			askAgain = true; // then I can ask it again
		}

		cin >> y;
		if(cin.fail())
		{
			cin.clear();
			cin >> a;
			askAgain = true;
		}

		if (x == -1 && y == -1)
		{
			cout << "Terminating..." << endl;
			return false;
		}

		if (askAgain)
		{
			cout << "Invalid coordinates" << endl;
			cout << endl;

		}
		else if ((x < 0 || x > row-1) || (y > column-1 || y < 0))
		{
			cout << "Invalid coordinates" << endl;
			cout << endl;
			askAgain = true;
		}
		else if( myMatrix[x][y] == 'o')
		{
			cout << "This cell is not occupied!" << endl;
			cout << endl;
			askAgain = true;
		}
	}
	coordinate first;
	first.x = x;
	first.y = y;
	coordinates.push_back(first);
	return true;
}

void PutCoordinates(int & x, int & y, vector <coordinate> & coordinates)
{
	//coordinates.push_back(coordinate(x, y));

	coordinate coo;
	coo.x = x;
	coo.y = y;
	coordinates.push_back(coo);
}

bool IsCooInVector (int x, int y, vector <coordinate> & coordinates) // checks the ( x, y ) point and finds if it is in the coordinate vector
{
	for (int k = 1; k < coordinates.size(); k++)
	{
		if(coordinates[0].x == x && coordinates[0].y == y && coordinates.size() == 2)
			return false;
		if(coordinates[k].x == x && coordinates[k].y == y)
			return false;
	}
	return true;
}

void CheckingPath (int & x, int & y, int row, int column, vector <coordinate> & coordinates, vector <vector<char>> myMatrix, bool & isClosedArea)
{
	bool check = false; // for while loop 

	while(!check)
	{
		// firstly, it must go right and check the values if it is x
		if( !(y >= column-1) && myMatrix[x][y + 1] == 'x' && IsCooInVector (x, y+1, coordinates))
		{
			y ++;
			PutCoordinates(x, y, coordinates);
		}
	
		// secondly it must go down
		else if(!(x >= row-1) && myMatrix[x+1][y] == 'x' && IsCooInVector (x+1, y, coordinates))
		{
			x ++;
			PutCoordinates(x, y, coordinates);
		}

		//thirdly, it must go left
		else if(!(y <=  0) && myMatrix[x][y-1] == 'x' && IsCooInVector (x, y-1, coordinates))
		{
			y -= 1;
			PutCoordinates(x, y, coordinates);
		}
		// at last time, it has to go up and check
		else if(!(x <= 0) && myMatrix[x-1][y] == 'x' && IsCooInVector (x-1, y, coordinates))
		{
			x -= 1;
			PutCoordinates(x, y, coordinates);
		}
		else
		{
			isClosedArea = false;
			break;
		}

		if(coordinates[0].x == x && coordinates[0].y == y )
		{
			isClosedArea = true;
			check = true;
		}
		
	}
	if (!isClosedArea)
	{
		cout << "Cannot found an enclosed area starting with given coordinate. The" << endl;
		cout << "coordinates of the followed path:" << endl;
	}
	else
		cout << "Found an enclosed area. The coordinates of the followed path:" << endl;
}
void PrintCooVector(vector <coordinate> & coordinates, bool & isClosedArea)
{
	if(!isClosedArea)
	{
		for(int i = 0; i <  coordinates.size(); i++)
		{
			cout << coordinates[i].x << " " << coordinates[i].y << endl;
		}
	}
	else
	{
		for(int i = 0; i <  coordinates.size()-1; i++)
		{
			cout << coordinates[i].x << " " << coordinates[i].y << endl;
		}
	}
}
int main()
{
	ifstream inputMatrix;
	string fileName, matrixLine;
	
	int row = 0, column = 0;
	char characters;

	cout << "Please enter file name: ";
	cin >> fileName;
	
	inputMatrix.open(fileName);
	
	while (inputMatrix.fail())
	{
		cout << "Cannot find a file named " << fileName << endl;
		cout << "Please enter file name: ";
		cin >> fileName;
		inputMatrix.open(fileName);
	}	
	
	bool checkingAllFactors = true; // for the checkingAllFactors I need this boolean 
	bool forLoop = false;

	while (!forLoop)
	{
		if(!CheckMatrixChr (inputMatrix, matrixLine, fileName, checkingAllFactors))
			break;
	
		if (!NumOfRowAndColm(inputMatrix, matrixLine, row, column, fileName))
			break;
		
		else
		{
			cout << "Input Matrix: " << endl;
			
			// NumOfRowAndColm(inputMatrix, matrixLine, row, column, fileName);
			vector <vector<char>> myMatrix (row, vector<char> (column));
			PuttingInMatrix(inputMatrix, matrixLine, myMatrix);
			PrintingMatrix (myMatrix, row, column);

			// asking coordinates to user
			int x, y;
			bool isClosedArea = false; // it will check the path is closed or not

			vector <coordinate> coordinates;

			while(AskingCoordinates(x, y, row, column, coordinates, myMatrix) == true)
			{
				CheckingPath (x, y, row, column, coordinates, myMatrix, isClosedArea);
				PrintCooVector(coordinates, isClosedArea);
				cout << endl;
				coordinates.clear();
			}
			forLoop = true;
		}
		
	}
	return 0;
}