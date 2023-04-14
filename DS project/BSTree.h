#pragma once


class Tnode
{
private:
	int data;
	Tnode* left;
	Tnode* right;
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


class BSTree
{
private:
	Tnode* root;

	// Utility Functions - Recursive Functions --------------------------

	// Given functions
	static void rec_insertBST(Tnode *& subRoot, int key);
	static void rec_inorder_traverse(Tnode* subRoot);
	static void rec_preorder_traverse(Tnode* subRoot);
	static void rec_postorder_traverse(Tnode* subRoot);	
	static void rec_destroy_tree(Tnode *& subRoot);

	//Functions to be implemented by student
	static Tnode*  rec_find_max(Tnode* subRoot);
	static Tnode*  rec_find_min(Tnode* subRoot);
	static int rec_max_depth(Tnode* subRoot);

	// [Note]: in the above utility functions:
	// we made them static --
	// because they don't need an object of BSTree to be executed
	// in otherwords, they don't can't with the non-static data members of BSTree (the "root" data member)
	// this is a way that will prevent you from: 
	// using "root" instead of the passed "subRoot" by mistake  -> syntax error

public:
	BSTree(void);
	~BSTree(void);

	// Public Functions --------------------------

	// Given functions
	void insertBST(int key); // not const
	void inorder_traverse() const;
	void preorder_traverse() const;
	void postorder_traverse() const;	
	void destroy_tree(); // not const

	// Functions to be implemented by student
	Tnode*  find_max() const; // return a pointer to the Tnode that hold the maximum value in binary search tree.
	Tnode*  find_min() const; // return a pointer to the Tnode that hold the minimum value in binary search tree.
	int max_depth() const;

	// [Note]: in the above public functions:
	// const functions are const because there is no probibility to change 
	// the root (data member) either directly (root = something) 
	// or by indirectly by passing it (by reference) to another function (utility fn here)
};

