#include<iostream>
using namespace std;
template<typename T>
class LNode
{
private:
	T item;	// A data item (can be any complex sturcture)
	LNode<T>* next;	// Pointer to next node
public:

	LNode() //default constructor
	{
		next = nullptr;
	}

	LNode(T newItem) //non-default constructor
	{
		item = newItem;
		next = nullptr;

	}
	void setItem(T newItem)
	{
		item = newItem;
	} // end setItem

	void setNext(LNode<T>* nextNodePtr)
	{
		next = nextNodePtr;
	} // end setNext

	T getItem() const
	{
		return item;
	} // end getItem

	LNode<T>* getNext() const
	{
		return next;
	}
}; // end Node
template <typename T>
class ListADT
{
private:
	LNode<T>* Head;	//Pointer to the head of the list
	LNode<T>* tail;// pointer to the tail of the list
	int itemcount;// number of nodes
public:


	ListADT() :itemcount(0)
	{
		Head = tail = nullptr;
	}
	//List is being desturcted ==> delete all items in the list
	~ListADT()
	{
		DeleteAll();
	}
	ListADT(const ListADT<T>& L)
	{
		LNode<T>* curptrL = L.Head;
		itemcount = L.itemcount;
		Head = tail = nullptr;
		while (curptrL)
		{
			InsertEnd(curptrL->getItem());
			curptrL = curptrL->getNext();
		}
	}
	int getitemcount() {
		return itemcount;
	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: PrintList.
	* prints the values of all nodes in a linked list.
	*/
	void PrintList()	const
	{
		LNode<T>* p = Head;
		while (p)
		{
			cout << p->getItem() << ",";
			p = p->getNext();
		}
	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: InsertBeg.
	* Creates a new node and adds it to the beginning of a linked list.
	*
	* Parameters:
	*	- data : The value to be stored in the new node.
	*/
	void InsertBeg(const T& data)
	{
		LNode<T>* R = new LNode<T>(data);
		R->setNext(Head);
		Head = R;
		if (!tail)
			tail = R;
		itemcount++;

	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: DeleteAll.
	* Deletes all nodes of the list.
	*/
	void DeleteAll()
	{
		LNode<T>* P = Head;
		while (Head)
		{
			P = Head->getNext();
			delete Head;
			Head = P;
		}
		itemcount = 0;
		tail = nullptr;
	}
	//inserts a new node at end if the list
	void InsertEnd(const T& data)
	{
		itemcount++;
		LNode<T>* newptr = new LNode<T>(data);
		if (!tail)
		{
			tail = newptr;
			Head = newptr;
		}
		else
		{
			tail->setNext(newptr);
			tail = newptr;
		}
	}
	//Deletes the first node in the list
	void DeleteFirst(T& value)
	{
		if (Head == nullptr)
			return;
		LNode<T>* ptr = Head;
		if (tail == Head)
			tail = tail->getNext();
		Head = Head->getNext();
		value = ptr->getItem();
		delete ptr;
		itemcount--;
	}
	bool isEmpty() { return (itemcount == 0); }
	bool DeleteNode(T& value, int p)
	{
		LNode<T>* curptr;
		LNode<T>* prev = nullptr;
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
};
