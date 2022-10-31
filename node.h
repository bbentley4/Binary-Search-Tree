/*
 * File: node.h
 * Author: Brenna Bentley and Kassidi Knight
 * Description: Contains the node templated class and its function definitions.
 * Necessary files: binarySearchTree and Position as friends
 * Date made: March 30, 2022
 * Last edit: April 8, 2022
 */
#ifndef NODE_H
#define NODE_H

#include <fstream>
using std::ostream;

// declaration for friend statement below
template<class T> class BinarySearchTree;
template<class T> class Position;

template <class T>
class Node {
public:
   Node(); // default constructor
   //constructor that takes a T item
   Node( const T& );
   // copy constructor.
   Node( const Node<T>& );
   virtual ~Node<T>() {} // destructor
   void setItem( const T& ); //assigns private member ITEM the value of parameter
   T getItem() const { return item; } //returns copy of private member ITEM
   Node<T>& operator=( const Node<T>& ); //overloaded assignment operator makes deep copy of parameter Node<T>
   friend class BinarySearchTree<T>;
   friend class Position<T>; //Position is an iterator class
private:
   Node<T>* leftPtr;
   Node<T>* rightPtr;
   Node<T>* parentPtr;
   T item;
};

/*
 * DEFAULT CONSTRUCTOR - creates empty NODE by setting all ptrs to null
 */
template<class T>
Node<T>::Node() : leftPtr(NULL), rightPtr(NULL), parentPtr(NULL) {}

/*
 * CONSTRUCTOR WITH T ARG - creates NODE with an item (the parameter) and sets all ptrs to null
 */
template<class T>
Node<T>::Node(const T& item)
{
	*this->item = item;
	leftPtr = NULL;
	rightPtr = NULL;
	parentPtr = NULL;
}
/*
 * COPY CONSTRUCTOR - copies Node<T> n (the parameter) to a new Node (the invoking object)
 * Note: makes leftPtr, rightPtr, and parentPtr NULL so it's a copy of the parameter node, but it doesn't have a place in a list or BST
 */
template<class T>
Node<T>::Node(const Node<T>& n)
{
	*this = n;
	leftPtr = NULL;
	rightPtr = NULL;
	parentPtr = NULL;
}
/*
 * SETITEM - assigns private member ITEM the value of parameter i
 */
template <class T>
void Node<T>::setItem(const T& i)
{
	this->item = i;
}

/*
 * OVERLOADED OPERATOR= - assigns the values of Node<T> n (the parameter) to a new Node (the invoking object) by deepcopy
 * Note: makes leftPtr, rightPtr, and parentPtr NULL so it's a copy of the parameter node, but it doesn't have a place in a list or BST
 * Instead of copying n to 'this', n's item is copied to this's item and *this (the new copy) is returned.
 */
template <class T>
Node<T>& Node<T>::operator=(const Node<T>& n)
{
	leftPtr = NULL;
	rightPtr = NULL;
	parentPtr = NULL;
	item = n.item;
	return *this;
}

#endif //NODE_H