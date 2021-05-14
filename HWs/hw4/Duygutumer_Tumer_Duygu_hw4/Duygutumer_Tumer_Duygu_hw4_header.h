#ifndef _DUYGUTUMER_TUMER_DUYGU_HW4_HEADER_H
#define _DUYGUTUMER_TUMER_DUYGU_HW4_HEADER_H
struct coordinate
{
	int rowC;
	int colC;
};

struct StackNode
{
	coordinate value;
	StackNode *next;
};

class DynIntStack
{
private:
	StackNode *top;

public:
	DynIntStack(void);
	void push(coordinate);
	coordinate pop();
	bool isEmpty(void);
};
	
#endif