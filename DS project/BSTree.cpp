#include "BSTree.h"

#include <iostream>
using namespace std;

// Utility Functions - Recursive Functions --------------------------

// Given functions

// Insert an integer key in a binary search tree.
// [Note]: subRoot is passed by ref because 
//         the new Tnode may be inserted in the subRoot (if subRoot is empty nullptr)
void BSTree::rec_insertBST(Tnode *& subRoot, int key)
{
	if (subRoot == nullptr)
		subRoot = new Tnode(key); // this line is why we pass subRoot by reference (subRoot = something)
	else if (subRoot->getdata() < key)
	{

		//recursively call insert for the right subtree
		rec_insertBST(subRoot->getright(), key);  

		// ************************   VERY IMPORTANT NOTE  *************************** //

		// Tnode* & Tnode::getright();   VS   Tnode* Tnode::getright();

		// Notice that function rec_insertBST(Tnode *& subRoot, int key);
		// takes it 1st parameter (the pointer) by REFERENCE
		// For the above call for the function to be syntactically correct, 
		// we have declared function Tnode::getright() as:  
		//		Tnode* & Tnode::getright(); (see Tnode class)
		//i.e. it returns a Tnode pointer but by reference (not by value)

		// Why wouldn't it work if it is return by value ???
		//		if Tnode::getright() was declared as  
		//		Tnode* Tnode::getright();			
		//		i.e. it returns "right" pointer (return by value)
		//		in this case, the returned pointer is called rvale (right-value)
		//		rvalue in C++ cannot be passed by ref to a function and
		//		cannot be used at the left of assignment statement		

		// What should I do if function getright must return by value ???
		//		IF for any reason, getright in your code MUST return by value 
		//		so the previous code line  rec_insertBST(subRoot->getright(), key); is a syntax error
		//		To solve the problem is this case 
		//		we should 
		//			1- store it in temp, 
		//			2- pass the temp to the function, 
		//			3- set the right of subRoot with this temp (after calling the fn because it may be changed inside it - by ref)
		//	Here is the code in this case to perform the same task
				/*
				Tnode * tmp = subRoot->getright();
				rec_insertBST(tmp, key);
				subRoot->setright(tmp);
				*/
		//	So to avoid all this mess, all what you need is to declare getright as:
		//		Tnode* & Tnode::getright();
		//	NOT as:
		//		Tnode*  Tnode::getright();

		
		// Remember: rvalue is some expression that is not stored in memory with a specific name
		// hence, you can't reach it by a name beyond the line that contains it 
		// like (x + 9): x is stored in memory, but (x + 9) returns a temp result that is not stored in memory with a name
		// same case for: subRoot->getright() --> if it returns an rvalue (or temp result without a name) of the "right"
	}
	else
	{
		// recursive call on left
		rec_insertBST(subRoot->getleft(), key); 
	}
}

//* print the tree with inorder traversal.
void BSTree::rec_inorder_traverse(Tnode* subRoot)
{
	if (subRoot == nullptr) return;
	rec_inorder_traverse(subRoot->getleft());
	cout << subRoot->getdata() << " ";
	rec_inorder_traverse(subRoot->getright());
}

//* print the tree with preorder traversal.
void BSTree::rec_preorder_traverse(Tnode* subRoot)
{
	if (subRoot == nullptr) return;
	cout << subRoot->getdata() << "  ";
	rec_preorder_traverse(subRoot->getleft());
	rec_preorder_traverse(subRoot->getright());
}

//* print the tree with postorder traversal.
void BSTree::rec_postorder_traverse(Tnode* subRoot)
{
	if (subRoot == nullptr) return;
	rec_postorder_traverse(subRoot->getleft());
	rec_postorder_traverse(subRoot->getright());
	cout << subRoot->getdata() << "  ";
}

//* Deletes all the Tnodes in the tree.
// [Note]: subRoot is passed by ref because 
//         after deleting subRoot Tnode we will make it point to nullptr (change subRoot)
void BSTree::rec_destroy_tree(Tnode *& subRoot)
{
	if (subRoot != nullptr)
	{
		// recursive call on left
		rec_destroy_tree(subRoot->getleft());

		// recursive call on right
		rec_destroy_tree(subRoot->getright());

		delete subRoot;
		subRoot = nullptr; // this line is why we pass subRoot by reference (subRoot = something)
	}
}

//Functions to be implemented by student

//* return a pointer to the Tnode that hold the maximum value in binary search tree of the passed subRoot.
Tnode*  BSTree::rec_find_max(Tnode* subRoot)
{
	//TO DO
	return nullptr; // should be changed
}
//* return a pointer to the Tnode that hold the minimum value in binary search tree of the passed subRoot.
Tnode*  BSTree::rec_find_min(Tnode* subRoot)
{
	//TO DO
	return nullptr; // should be changed
}
//* return the depth of binary search tree of the passed subRoot.
int BSTree::rec_max_depth(Tnode* subRoot)
{
	//TO DO
	return 0; // should be changed
}


BSTree::BSTree()
{
	root = nullptr;
}


BSTree::~BSTree()
{
	destroy_tree();
}

// Public Functions ---------------------------------

// Given functions
void BSTree::insertBST(int key) // not const
{
	// not const because rec_insertBST takes the root by reference, so may change it
	rec_insertBST(root, key);
}
void BSTree::inorder_traverse() const
{
	rec_inorder_traverse(root);
}
void BSTree::preorder_traverse() const
{
	rec_preorder_traverse(root);
}
void BSTree::postorder_traverse() const
{
	rec_postorder_traverse(root);
}
void BSTree::destroy_tree() // not const
{
	// not const because rec_destroy_tree takes the root by reference, so may change it
	rec_destroy_tree(root); 
}

// Functions to be implemented by student
Tnode* BSTree::find_max() const // return a pointer to the Tnode that hold the maximum value in binary search tree.
{
	//TO DO
	return nullptr; // should be changed
}
Tnode* BSTree::find_min() const // return a pointer to the Tnode that hold the minimum value in binary search tree.
{
	//TO DO
	return nullptr; // should be changed
}
int BSTree::max_depth() const
{
	//TO DO
	return 0; // should be changed
}
