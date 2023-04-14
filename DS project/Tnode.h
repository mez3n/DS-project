#pragma once

class Tnode
{
private:
	int data;
	Tnode *left;
	Tnode *right;
public:
	Tnode(int val);
	void setdata(int d);
	int getdata();
	void setright(Tnode* p);
	Tnode*& getright();
	//returns a pointer by reference
	//Reason for that is explained in file BSTree.cpp as a note written
	//inside the body of function BSTree::rec_insertBST

	void setleft(Tnode* p);	
	Tnode*& getleft();



};
