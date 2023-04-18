#pragma once
#ifndef NODE_
#define NODE_
template<class T>
class Node {
	T item;
	Node* next;
public:
	Node() {};
	Node(T newItem); //non-default constructor
	void setItem(T a)
	{
		item = a;
	}
	T getItem() const
	{
		if (this == NULL)
		{
			//cout << "0";
			return 0;

		}
		return item;
	}
	void setNext(Node<T>* n)
	{
		next = n;
	}
	Node<T>* getNext() const
	{
		return next;
	}
};
#endif
template<class T>
class LinkedList {
	Node<T>* head;
	Node<T>* current;
	Node<T>* tail;
	int count;
public:
	LinkedList() {
		head = tail = current = NULL;
		count = 0;
	};
	LinkedList(LinkedList& L)
	{
		this = L;
	}
	void DeleteAll()
	{
		Node<T>* P = head;
		while (head)
		{
			P = head->getNext();
			delete head;
			head = P;
		}
	        count = 0;
	}
	void InsertEnd(T item)
	{
		Node<T>* newnode = new Node<T>;
		count++;
		newnode->setItem(item);
		newnode->setNext(NULL);
		if (head == NULL)
		{
			head = tail = current = newnode;
		}
		else
		{
			tail->setNext(newnode);
			tail = newnode;
		}
	}

	void PrintList() const
	{
		if (this == NULL)
		{
			cout << "no list to print\n";
			cout << endl;
		}
		else
		{
			Node<T>* p = head;
			while (p)
			{
				cout << p->getItem()<< " ";
				p = p->getNext();
			}
			
		}
		cout << endl;
	}
	int getcount()
	{
		return count;
	}
	Node<T>* gethead()
	{
		return head;
	}
	Node<T>* gettail()
	{
		return tail;
	}
	Node<T>* getcurrent()
	{
		return current;
	}
	void sethead(Node<T>* n)
	{
		head = n;
	}
	void setcurrent(Node<T>* n)
	{
		current = n;
	}
	void settail(Node<T>* n)
	{
		tail = n;
	}
	bool find(T k, Node<T>*& n)
	{
		if (head != NULL)
		{
			while (current != NULL)
			{
				if (current->getItem() == k)
				{
					n = current;
					return true;
				}
				current = current->getNext();
			}
			n = NULL;
			//cout << "NULL\n";
			return false;
		}
		else
		{
			n = NULL;
			//cout << "NULL\n";
			return false;
		}
	}
	bool deletenode(Node<T>* n)
	{
		Node<T>* ptr = head;
		while (ptr)
		{
			if (ptr->getNext() == n)
			{
				ptr->setNext(n->getNext());
				n->setNext(NULL);
				delete n;
				count--;
				return true;
			}
			ptr = ptr->getNext();
		}
		return false;
	}
};
