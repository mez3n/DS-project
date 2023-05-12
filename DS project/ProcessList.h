#pragma once
#include"ListADT.h"
#include"Process.h"
class ProcessList : public ListADT<Process*>
{
public:
	ProcessList() 
	{}
	bool DeleteNode(Process*& value, int p)
	{
		LNode<Process*>* curptr;
		LNode<Process*>* prev = nullptr;
		curptr = Head;
		while (curptr)
		{
			if (curptr->getItem()->getPID() == p)
			{
				if (!prev)
					DeleteFirst(value);
				else
				{
					prev->setNext(curptr->getNext());
					value = curptr->getItem();
					if (curptr == tail)
						tail = prev;
					delete curptr;
					itemcount--;
				}
				return true;
			}
			else
			{
				prev = curptr;
				curptr = curptr->getNext();
			}
		}
		return false;
	}
	ProcessList(const ProcessList& L)
	{
		LNode<Process*>* curptrL = L.Head;
		itemcount = L.itemcount;
		Head = tail = nullptr;
		while (curptrL)
		{
			InsertEnd(curptrL->getItem());
			curptrL = curptrL->getNext();
		}
	}
};
