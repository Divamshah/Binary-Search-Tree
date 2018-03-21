/*
This program creates a BST(L<=root<R. It uses header file given, all the cases and functions are tested by the main 
*/
#include "tree.h"
#include<iostream>
using namespace std;


//Constructor
Tree::Tree() {
	start = NULL;
}
//Copy Constructor
Tree::Tree(const Tree& other) {

	start = NULL;
	copyOther(other);
}
//Destructor
Tree::~Tree() {
	
		clear();
		cout << "In destructor" << endl;
	

}

//Overload assignment
Tree& Tree::operator=(const Tree& other) {

	if (this->start != NULL)
	{
		this->clear();
		this->start = NULL;
	}
	copyOther(other);
	return *this;
}

//Helper function to print 
int depth(TreeNode* startingPoint, TreeNode* end) {
	int count = 0;
	while (startingPoint != end) {
		if (startingPoint == NULL) {
			break;
		}
		else if (end->value > startingPoint->value) {
			count++;
			startingPoint = startingPoint->right;
		}
		else {
			count++;
			startingPoint = startingPoint->left;
		}
	}
	return count;
}
//Helper function for Delete
TreeNode* findMax(TreeNode* root) {
	if (root == NULL)
		return root;
	while (root->right != NULL)
		root = root->right;
	return root;
}

//Helper function for DeleteNode
TreeNode* delhelp(TreeNode** startintPoint, int value)
{
	TreeNode* delnode = *startintPoint;
	if (value > delnode->value) {
		delnode->right = delhelp(&delnode->right, value);
		return delnode;
	}
	else if (value < delnode->value) {
		delnode->left = delhelp(&delnode->left, value);
		return delnode;
	}
	else {
		// we found it ;
		// leaf node;
		if (delnode->left == NULL && delnode->right == NULL) {
			delete delnode;
			delnode = NULL;
			return delnode;
		}
		else if (delnode->left == NULL) {
			TreeNode* temp = delnode;
			delnode = delnode->right;
			delete temp;
			return delnode;
		}
		else if (delnode->right == NULL) {
			TreeNode* temp = delnode;
			delnode = delnode->left;
			delete temp;
			return delnode;
		}
		else {

			TreeNode* temp = findMax(delnode->left);
			delnode->value = temp->value;
			delnode->left = delhelp(&delnode->left, temp->value);
			return delnode;
		}
	}
}
//helperfucntion and inserton
void Tree::push(int value) {

	TreeNode* node = new TreeNode();
	node->value = value;
	if (start == NULL)
		start = node;
	else
		pushFrom(start, node);
}
//Find Function
TreeNode* Tree::find(int value) const {

	return findFrom(start, value);
}

//Print Function
void Tree::print() const {

	if (start == NULL)
		return;
	else {
		printFrom(start, depth(start, start));
	}
}
//Delete Function
void Tree::deleteNode(int value) {

	if (start == NULL)
		cout << "Value not Found";
	else
	{
		deleteFrom(start, value);
	}
}

//Used in Copy Constructor
void Tree::copyOther(const Tree& other) {

	if (other.start == NULL)
		return;
	this->copyFrom(other.start);	
}
//Used in Destructor
void Tree::clear() {

	if (start == NULL)
		return;
	else
	{
		clearFrom(start);
	}
}
//Used in Push
void Tree::pushFrom(TreeNode*startingPoint, TreeNode* nodeToPush) {

	if ( startingPoint->value<= nodeToPush->value)
	{
		if (startingPoint->right == NULL)
			startingPoint->right = nodeToPush;
		else
			pushFrom(startingPoint->right, nodeToPush);
	}
	else
	{
		if (startingPoint->left == NULL)
			startingPoint->left = nodeToPush;
		else
			pushFrom(startingPoint->left, nodeToPush);
	}
}
//Used by Find
TreeNode* Tree::findFrom(TreeNode* startingPoint, int value) const {

	if (startingPoint == NULL)
		return NULL;
	if (value == startingPoint->value)
		return startingPoint;
	else if (value > startingPoint->value)
		return findFrom(startingPoint->right, value);
	else
		return findFrom(startingPoint->left, value);
}
//Used by Print
void Tree::printFrom(TreeNode* startintPoint, int numSpaces) const {
	if (startintPoint == NULL) {
		return;
	}
	for (int i = 0; i < numSpaces; i++)
		cout << " ";
	cout << startintPoint->value << endl;
	printFrom(startintPoint->left, depth(start, startintPoint) + 1);
	printFrom(startintPoint->right, depth(start, startintPoint) + 1);
}
//Called by CopyOther
void Tree::copyFrom(TreeNode* startintPoint) {

	if (startintPoint == NULL)
		return;
	push(startintPoint->value);
	copyFrom(startintPoint->left);
	copyFrom(startintPoint->right);
}
//Called by DeleteNode
void Tree::deleteFrom(TreeNode*startintPoint, int value) {

	if (startintPoint == NULL)
		cout << "Value not found";
	else
		startintPoint = delhelp(&startintPoint, value);
}

//Called by Clear Function
void Tree::clearFrom(TreeNode* startingPoint) {

	if (startingPoint == NULL)
		return;
	clearFrom(startingPoint->left);
	clearFrom(startingPoint->right);
	deleteNode(startingPoint->value);

}






