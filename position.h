/* File: position.h
 * Author: Brenna Bentley and Kassidi Knight
 * Description: Contains the position templated class and its function definitions.
 * Necessary files: binarySearchTree as friend and node.h
 * Date made: March 30, 2022
 * Last edit: April 25, 2022 by Brenna Bentley
 * 		Added overloaded = operator
 * Note: Position constructor will not get called if list is empty
 */
#ifndef POSITION_H
#define POSITION_H

#include "node.h"
//declaration for friend statement below
template<class T> class BinarySearchTree;

template <class T>
class Position {
public:
   Node<T>& operator*() { return *nodePtr; }
   Position parent() const {
      return Position<T>( this->nodePtr->parentPtr ); }
   Position left() const {
      return Position<T>( nodePtr->leftPtr ); }
   Position right() const {
      return Position<T>( nodePtr->rightPtr ); }
    bool isRoot( ) const {
      // does this iterator point to real root?
      return this->nodePtr->parentPtr->parentPtr == NULL; }
   bool isSuperRoot() const{
      // does this iterator point to fake super root?
      return this->nodePtr->parentPtr == NULL; }
   bool isExternal() const {
	   // is it a fake end node?
	   return this->nodePtr->leftPtr == NULL &&
	   this->nodePtr->rightPtr == NULL; }
   bool isInternal() const { return !(isExternal() ); }
   bool operator==( const Position& p ) {
	    return this->nodePtr == p.nodePtr; }
   bool operator!=( const Position& p ) {
	   return this->nodePtr != p.nodePtr; }
   Position& operator=( const Position& p );
   Position& operator++( ); // inorder traversal
   T getItem() const { return nodePtr->item; }
   friend class BinarySearchTree<T>;
private:
   // only friends like BST can create positions from its nodes
	Position(): nodePtr(NULL) { }
	Position( Node<T>* n) {nodePtr = n;}
	Node<T>* nodePtr;
};




/* overloaded ++ operator
 * returns iterator that points to the next node in the tree, IN-ORDER TRAVERSAL
 * returns position with NULL nodePtr if get to end of the tree in an in-order traversal
 */
template <class T>
Position<T>& Position<T>::operator++()
{
	//position w = THIS' right
	Position w = this->right();
	//if w is an internal node (not a fake leaf)
	if (w.isInternal())
	{
		//move left until hit w gets to a leaf
		do
		{
			*this = w; //this = w's nodeptr
			w=w.left(); // w= w's left
		} while (w.isInternal()); //while w is internal
	}
	else //w is external
	{
		w = this->parent(); //w = THIS's parent. THIS will follow w up the tree
		//while w's nodeptr isn't null (ie didn't hit the superroot yet)
		//AND *THIS is w's right
		while (w.nodePtr != NULL && *this == w.right())
		{
			*this = w;
			w = w.parent();
		}
		*this = w;
	}
	return *this;
}

/* overloaded = operator
 * assigns the nodePtr of the parameter Position to the nodePtr of the invoking Position
 * returns the invoking Position ('*this')
 */
template <class T>
Position<T>& Position<T>::operator= (const Position<T>& p)
{
	nodePtr = p.nodePtr;
	return *this;
}


#endif //POSITION_H