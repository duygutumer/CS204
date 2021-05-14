#include <iostream>
#include "Duygutumer_Tumer_Duygu_hw4_header.h"

using namespace std;

 
DynIntStack::DynIntStack() // Constructor
{
	top = NULL; 
}
bool DynIntStack::isEmpty(void)
{
	if (top == NULL)
		return true;
	else
		return false;
}
void DynIntStack::push(coordinate co)
{
	StackNode *newNode;
	// Allocate a new node & store Num
	newNode = new StackNode;
	newNode->value = co;

	// If there are no nodes in the list
	// make newNode the first node
	if (isEmpty())
	{
		top = newNode;
		newNode->next = NULL;
	}
	else	// Otherwise, insert NewNode before top
	{
		newNode->next = top;
		top = newNode;
	}
}
coordinate DynIntStack::pop()
{
	StackNode *temp;

	if (isEmpty())
	{
		cout << "The stack is empty." << endl;
	}
	else	// pop value off top of stack
	{
		coordinate co = top->value;
		temp = top->next;
		delete top;
		top = temp;
		return co;
	}
}