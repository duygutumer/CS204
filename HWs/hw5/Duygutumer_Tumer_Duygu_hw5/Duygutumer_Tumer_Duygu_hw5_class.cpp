#include "Duygutumer_Tumer_Duygu_hw5_header.h"
#include <iostream>
#include <vector>
#include<string>

using namespace std;

// constructor
IntegerSet::IntegerSet()
{
	size = 0;
	set = NULL;
}

// constructor with vector size
IntegerSet::IntegerSet(int psize)
{
	size = psize;
	set = new int[psize];
	for (int i = 0; i < psize; i++)
	{
		set[i] = i;
	}
	
}

// deep copy constructor
IntegerSet::IntegerSet(const IntegerSet & copy)
{
	size = copy.size; // here we get the size of the Real vector 
	set = new int[size]; // creates a new vector

	for(int i = 0; i < size; i++)
	{
		set[i] = copy.set[i]; // here my new vector takes the same value with the real one
	}
}

// != operator
bool IntegerSet::operator!=(const IntegerSet & rhs)
{
	if(size != rhs.size) //first sizes must be equal
	{
		return true;
	}
	
	for(int i = 0; i < size; i++)
	{
		if(set[i] != rhs.set[i])
		{
			return true;
		}
	}
	return false;
}

// = operator
const IntegerSet& IntegerSet::operator=(const IntegerSet & rhs)
{
	if (this != &rhs) // if they are not already equal
	{
		// first delete left hand side
		size = 0;
		delete[] set;

		// create new vector for left hand side
		size = rhs.size;
		set = new int[size];

		for(int i = 0; i < size; i++)
		{
			set[i] = rhs.set[i]; 
		}
	}

	return *this;
}

// + operator for int value
IntegerSet IntegerSet::operator+(int element)
{
	bool check = true;
	for(int k = 0; k < size; k++)
	{
		if(element == set[k])
			check = false;
	}
	if(check) // if this element is unique
	{
		int newsize = size + 1;
		IntegerSet result(newsize);
		result.set[newsize-1] = element;
		for(int i = 0; i < size; i++)
		{
			result.set[i] = set[i];
		}
		return result; 
	}
	else // if this element has already exist
	{
		IntegerSet result(size);
		for(int i = 0; i < size; i++)
		{
			result.set[i] = set[i];
		}
		return result; 
	}
}

// * operator
IntegerSet IntegerSet::operator*(const IntegerSet & rhs)
{
	vector<int> listy;
	int newsize = 0;
	for(int i = 0; i < size; i++) 
	{
		for(int k = 0; k < rhs.size; k++)
		{
			if(set[i] == rhs.set[k])
			{
				newsize ++;
				listy.push_back(set[i]);
			}
		}
	}
	IntegerSet result(newsize);
	for(int p = 0; p < newsize; p++)
	{
		result.set[p] = listy[p];
	}

	return result; 
}

// += operator for two class values
IntegerSet& IntegerSet::operator+=(IntegerSet & rhs)
{
	vector<int> list2;
	
	bool check = false;
	for(int i = 0; i < size; i++)  
	{
		if(list2.size() == 0)
			list2.push_back(set[i]);

		for(int k = 0; k < list2.size(); k++)
		{
			if(set[i] == list2[k])
				check = true;	
		}
		if(!check)
			list2.push_back(set[i]);
		check = false;
	}
	
	bool check2 = false;
	for(int p = 0; p < rhs.size; p++)  
	{
		if(list2.size() == 0)
			list2.push_back(rhs.set[p]);

		for(int r = 0; r < list2.size(); r++)
		{
			if(rhs.set[p] == list2[r])
				check2 = true;
					
		}
		if(!check2)
			list2.push_back(rhs.set[p]);
		check2 = false;
	}
	size = 0;
	delete[] set;
	size = list2.size();
	set = new int[size];

	for(int i = 0; i < size; i++) 
	{
		set[i] = list2[i];
	}

	return *this;

}

// <= operator for two class values
bool IntegerSet::operator<=(const IntegerSet & rhs)
{
	if (this != &rhs) // if they are not already equal
	{
		if(size > rhs.size)
			return false;
		
		bool check = false;

		for(int i = 0; i < size; i++)
		{
			for(int k = 0; k < size; k++)
			{
				if(set[i] == rhs.set[k])
					check = true;	
			}
			
			if(!check)
				return false;

		}
	}
	return true;
}

int IntegerSet::getSize() const
{
	return size;
}
int IntegerSet::getElement(int i) const
{
	return set[i];
}
void IntegerSet::setElement(int i, int num) const
{
	set[i] = num;
}

// destructor
IntegerSet::~IntegerSet()
{
	size = 0;
	delete[] set;
}

//FREE FUNCTIONS:

// cout
ostream & operator<< (ostream &os, const IntegerSet & lhs)
{
	os << "{";
	for (int i = 0; i < lhs.getSize(); i++)
	{
		os << lhs.getElement(i);
		if(i != lhs.getSize()-1)
		{
			os << ", ";
		}
	}
	os << "}";

	return os;
}

// + operator for class values
IntegerSet operator+ (const IntegerSet & lhs , const IntegerSet & rhs) 
{
	vector<int> list;
	
	bool check = false;
	for(int i = 0; i < lhs.getSize(); i++)  
	{
		if(list.size() == 0)
			list.push_back(lhs.getElement(i));

		for(int k = 0; k < list.size(); k++)
		{
			if(lhs.getElement(i) == list[k])
				check = true;	
		}
		if(!check)
			list.push_back(lhs.getElement(i));
		check = false;
	}
	
	bool check2 = false;

	for(int p = 0; p < rhs.getSize(); p++)  
	{
		if(list.size() == 0)
			list.push_back(rhs.getElement(p));

		for(int r = 0; r < list.size(); r++)
		{
			if(rhs.getElement(p) == list[r])
				check2 = true;
					
		}
		if(!check2)
			list.push_back(rhs.getElement(p));
		check2 = false;
	}
	int newsize = list.size();
	IntegerSet result(newsize);

	for(int i = 0; i < newsize; i++) 
	{
		result.setElement(i, list[i]);
	}

	return result;
}

bool operator<=(int num,  const IntegerSet & rhs)
{
	for(int i = 0; i < rhs.getSize(); i++ )
	{
		if(num == rhs.getElement(i))
			return true;
	}
	return false;
}