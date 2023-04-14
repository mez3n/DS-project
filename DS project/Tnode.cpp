#include "Tnode.h"

Tnode::Tnode(int val)
{
	data = val;
	left = right = nullptr;
}


void Tnode::setdata(int d)
{
	data = d;
}
int Tnode::getdata()
{
	return data;
}
void Tnode::setleft(Tnode* p)
{
	left = p;
}
Tnode*& Tnode::getleft()
{
	return left;
}
void Tnode::setright(Tnode* p)
{
	right = p;
}
Tnode*& Tnode::getright()
{
	return right;
}
