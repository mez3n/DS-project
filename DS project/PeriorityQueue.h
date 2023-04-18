template<typename T>
class HeapNode
{
private:
	T item;	// A data item (can be any complex sturcture)
	int key;
public:

	HeapNode() //default constructor
	{
		item = nullptr;
		key = 0;
	}
	HeapNode(int newkey, T newItem) //non-default constructor
	{
		item = newItem;
		key = newkey;
	}
	void setkey(int newkey)
	{
		key = newkey;
	}
	int getkey()
	{
		return key;
	}
	void setitem(T newItem)
	{
		item = newItem;
	} // end setItem
	T getitem() const
	{
		return item;
	} // end getItem
}; // end Node
#include<iostream>
using namespace std;
// periority Queue implemented by Heap
template<class T>
class PeriorityQueue
{
private:
	int count;
	HeapNode<T>* Heap;
	int Max_Size;
public:
	PeriorityQueue(int MAX_SIZE) :Max_Size(MAX_SIZE)
	{
		count = 0;
		Heap = new HeapNode<T>[MAX_SIZE];
	}
	~PeriorityQueue()
	{
		delete[]Heap;
	}
	PeriorityQueue(const PeriorityQueue<T>& Q)
	{
		count = Q.count;
		Heap = new HeapNode<T>[Q.Max_Size];
		for (int i = 1; i <= Q.count; i++)
		{
			Heap[i] = Q.Heap[i];
		}
	}
	void PrintList()
	{
		for (int i = 1; i <= count; i++)
			cout << Heap[i].getitem()<<" ";
	}
	bool isEmpty() const
	{
		return(count == 0);
	}
	int getparent(int i) { return (i / 2); }
	bool enqueue(T newitem,int newkey)
	{
		if (count == Max_Size - 1)
			return false;
		count++;
		int i = count;
		Heap[i].setitem(newitem);
		Heap[i].setkey(newkey);
		while (i > 1 && (Heap[getparent(i)].getkey() > Heap[i].getkey()))
		{
			HeapNode<T> tmp = Heap[getparent(i)];
			Heap[getparent(i)] = Heap[i];
			Heap[i] = tmp;
			i = getparent(i);
		}
		return true;
	}
	bool dequeue(T& frontitem)
	{
		if (count == 0)
			return false;
		frontitem = Heap[1].getitem();
		Heap[1] = Heap[count];
		count--;
		Min_Heapify(1);
		return true;
	}
	int getleft(int i) { return (2 * i); }
	int getright(int i) { return (2 * i + 1); }
	void Min_Heapify(int i)
	{
		int l = getleft(i);
		int r = getright(i);
		int smallest;
		if ((l <= count) && (Heap[l].getkey() < Heap[i].getkey()))
			smallest = l;
		else
			smallest = i;
		if ((r <= count) && (Heap[r].getkey() < Heap[smallest].getkey()))
			smallest = r;
		if (smallest != i)
		{
			HeapNode<T> tmp = Heap[smallest];
			Heap[smallest] = Heap[i];
			Heap[i] = tmp;
			Min_Heapify(smallest);
		}
	}
	bool peek(T& frontitem) const
	{
		if (count == 0)
			return false;
		frontitem = Heap[1].getitem();
		return true;
	}
	void print(PeriorityQueue q1)
	{
		while (!q1.isEmpty())
		{
			cout << q1.peek() << " ";
			q1.dequeue();
		}
	}
};

