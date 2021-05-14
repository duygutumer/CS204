#ifndef _DUYGUTUMER_TUMER_DUYGU_HW5_HEADER_H
#define _DUYGUTUMER_TUMER_DUYGU_HW5_HEADER_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;



//CLASS:

class IntegerSet
{
	private:
		int size;
		int* set;
		
	public:
		IntegerSet();
		IntegerSet(int);
		IntegerSet(const IntegerSet &); //deep copy constructor
		~IntegerSet();

		IntegerSet operator+(int); // + operator for int and class
		IntegerSet& operator+=(IntegerSet &); // += operator
		IntegerSet operator*(const IntegerSet &);
		const IntegerSet& operator=(const IntegerSet &); // assignment operator (=)
		bool operator!=(const IntegerSet &);
		bool operator<=(const IntegerSet &);

		int getSize() const;
		int getElement(int) const;
		void setElement(int, int) const;	

};
//FREE FUNCTIONS:

// cout
ostream & operator<<(ostream &os, const IntegerSet & lhs);

// + operator for class values
IntegerSet operator+ (const IntegerSet & lhs , const IntegerSet & rhs);

bool operator<=(int num,  const IntegerSet & rhs);

#endif