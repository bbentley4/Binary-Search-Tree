/*
 * File: binarySearchTree.h
 * Author: Brenna Bentley and Kassidi Knight
 * Description: Contains the binary search tree templated class and its function definitions.
 * Necessary files: node.h and position.h
 * Date made: March 30, 2022
 * Last edit: April 25, 2022 by Brenna Bentley
 * 		Added copy constructor, copyTree fx, overloaded operator=, and preorderTraverseAndWrite
 */
#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include "position.h"
using namespace std;
using std::cout;

//TRAVERSE TYPES
const int PREORDER = 1;
const int INORDER = 2;
const int POSTORDER = 3;

//CLASS DEFINITION
template <class T>
class BinarySearchTree {
public:
	//---------------------------------------------------------//
	//THE BASICS
	//CONSTRUCTOR
    BinarySearchTree();
    //COPY CONSTRUCTOR
    BinarySearchTree( const BinarySearchTree& );
    //DESTRUCTOR
    virtual ~BinarySearchTree() { deleteUtility(superRootPtr); }
    //---------------------------------------------------------//
    //PUBLIC FUNCTIONS (in alphabetical order)
    //I'm choosing alphabetical order to make it easier to find fxs in such a long file
    //BEGIN - returns position iterator to first node on tree - the leftmost
    Position<T> begin() const;
    //DEPTH - find the depth of the tree
    int depth( const Position<T>& ) const;
    //EMPTY returns true if tree empty of real nodes
    bool empty() const { return numNodes == 0; }
    //END returns NULL iterator
    Position<T> end() const { return Position<T>( ); }
    //ERASE with parameter T (item w/in the node in the BST)
    bool erase( const T& );
    //ERASE with parameter Position
    bool erase( const Position<T>& );
    //FIND - find a node with the same T (item) information as the parameter
    Position<T> find( const T& ) const;
    //HEIGHT - find the height of the tree
    int height( const Position<T>& ) const;
    //INSERT an item into a node and into the tree
    Position<T> insert( const T& );
    //ROOT superroot right pointer always points to real root node
    Position<T> root() const { return Position<T>( superRootPtr->rightPtr ); }
    //SIZE returns num nodes in tree
    int size() const { return numNodes; }
    //PREORDER TRAVERSE AND WRITE the tree (pre-order) to a binary file
    //***SEE NOTE ON FUNCTION***//
    void preorderTraverseAndWrite( ostream&, const Position<T>& ) const;
    //TRAVERSE AND PRINT the tree (order dictated by type parameter
    void traverseAndPrint( const Position<T>& p, int type ) const;
    //---------------------------------------------------------//
    //FRIEND CLASS DECLARATION(S)
    friend class Position<T>;
    //---------------------------------------------------------//
private:
   //PRIVATE MEMBER VARIABLES
   Node<T>* superRootPtr;
   // number real nodes in tree, not including fake super
   // root and fake ends nodes
   int numNodes;
   //---------------------------------------------------------//
   //PRE-, IN-, POST-ORDER TRAVERSE (AND PRINT) FXS
   void preorderTraverseAndPrint(const Position<T>&) const;
   void inorderTraverseAndPrint( const Position<T>& ) const;
   void postorderTraverseAndPrint( const Position<T>& ) const;
   //---------------------------------------------------------//
   //COPYTREE UTILITY
   Node<T>* copyTree (Node<T>*, Node<T>*);
   //DELETE UTILITY deletes all nodes in the tree
   void deleteUtility( Node<T>* );
   //ERASE UTILITY erases just one node from the tree at position p
   Position<T> eraseUtility( const Position<T>& p);
   //EXPAND EXTERNAL insert item data at position p
   void expandExternal( const T& item, Position<T>& p);
   //FIND UTILITY finds item in tree starting at position
   Position<T> findUtility( const T& item, const Position<T>& ) const;
   //INSERT UTILITY inserts item into tree
   Position<T> insertUtility( const T& item );
   //REMOVE ABOVE EXTERNAL remove node above fake leaf node at position p
   Position<T> removeAboveExternal( const Position<T>& p );
   BinarySearchTree<T>& operator= (const BinarySearchTree&);
};



/*
 * THE BASICS
*/
/* DEFAULT CONSTRUCTOR sets up an empty tree with two nodes:
 * fake root whose right ptr points to fake end
 */
template <class T>
BinarySearchTree<T>::BinarySearchTree()
 {
	 superRootPtr = new Node<T>();
	 superRootPtr->rightPtr = new Node<T>();
	 superRootPtr->rightPtr->parentPtr = superRootPtr;
     superRootPtr->leftPtr = NULL; //superroot ptr's left ptr is always null
     numNodes = 0;
}

/*
 * COPY CONSTRUCTOR
 */
 template <class T>
 BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree& tree)
 {
	 //numNodes = tree.numNodes
	 numNodes = tree.numNodes;
	 //superRootPtr = new Node
	 superRootPtr = new Node<T>();
	 //if tree is empty (then so will this tree be empty and we only need a fake leaf node)
	 if (tree.empty())
	 {
		 //superRootPtr’s rightPtr = new Node
		 superRootPtr->rightPtr = new Node<T>();
		 //superRootPtr’s rightPtr’s parentPtr = superRootPtr (so the fake leaf points back to its parent)
		 superRootPtr->rightPtr->parentPtr = superRootPtr;
	 }
	 //4.	 else (parameter 'tree' has real nodes in it)
	 else
	 {
	 	 //superRootPtr’s rightPtr = copyTree( superRootPtr, tree.superRootPtr’s rightPtr)
		 superRootPtr->rightPtr = copyTree(superRootPtr, tree.superRootPtr->rightPtr);
	 }
 }

 /*
  * DESTRUCTOR is in-line in the class
  */

 //---------------------------------------------------------//
 //PUBLIC FUNCTIONS (in alphabetical order)

 /*
  * BEGIN: returns position iterator to first node on tree - the leftmost
  */
 template<class T>
 Position<T> BinarySearchTree<T>::begin() const
 {
    if ( numNodes > 0 ) {
       Position<T> p = root();
       while (p.isInternal()) {
          p = p.left();
       }
       return p.parent();
    }
    else return Position<T>( superRootPtr );
 }

 /* DEPTH: returns distance from root to node at parameter position
  * Parameter: p position to compute depth of
  * Returns depth or -1 if position p is superroot
 */
 template<class T>
 int BinarySearchTree<T>::depth( const Position<T>& p ) const
 {
    if ( p.isSuperRoot()) return -1;
    if ( p.isRoot()) return 0;
    else {
       return 1+depth( p.parent() );
    }
 }

 /*
  * EMPTY is in-line in the class
  * END is in-line in the class
  */

 /*
  * ERASE WITH T& ITEM PARAMETER
  * Finds the position pointing to the node with the same item as passed to the fx using the find fx.
  * Then uses the eraseUtility to remove the node from the BST.
  */
 template<class T>
 bool BinarySearchTree<T>::erase(const T& item)
 {
	 //can't remove supperroot or fake external node
	 Position<T> p = find(item);
	 //if superroot, tree is empty, external is fake
	 if (!p.isSuperRoot() && !p.isExternal())
	 {
		 eraseUtility(p);
		 return true;
	 }
	 else
	 {
		 return false;
	 }
 }

 /* ERASE WITH POSITION P PARAMTER: removes a node above Position p
  * Precondition position p is a valid position in tree
  * Returns true if successful
  */
 template<class T>
 bool BinarySearchTree<T>::erase( const Position<T>& p ) {
    // can't remove superroot or fake external node
    if ( !p.isSuperRoot() && !p.isExternal() ) {
       eraseUtility( p );
       return true;
    }
    else
       return false;
 }

 /* FIND: finds a T object in tree
  * Parameters: the object to find
  * Pre-condition: class T has overloaded operator==
  * Returns iterator to object, superroot iterator if tree
  *   is empty, fake leaf postion if not found
  */
 template<class T>
 Position<T> BinarySearchTree<T>::find( const T& item ) const {
    if ( numNodes > 0 ) {
       Position<T> v = findUtility(item, root());
       return v;
    }
    else return Position<T>(superRootPtr);
 }

 /* HEIGHT: returns distance from node at parameter position to
  * lowest leaf
  * Parameter: position to computer height of
 */
 template<class T>
 int BinarySearchTree<T>::height( const Position<T>& p ) const {
    // if leaf
    if ( p.isExternal() ) return 0;
    int h = 0;
    // h = max of 0 and height of left subtree
    h= max( h, height( Position<T>( p.nodePtr->leftPtr )));
    // h = max of height of left subtree and
    // height of right subtree
    h = max( h, height( Position<T>( p.nodePtr->rightPtr )));
    return 1 + h;
 }

 /* INSERT: inserts object T in the binary tree
  * Parameter: the object to insert
  * Pre-condition: class T has overloaded operator<
  * Returns iterator to newly inserted object or superRootPtr if item already in tree
  */
 template<class T>
 Position<T> BinarySearchTree<T>::insert(const T& item) {
    // root() = superroot's right ptr
    Position<T> p = insertUtility( item );
    // return iterator to position where new node inserted
    return p;
 }

 /*
  * ROOT is in-line in the class
  * SIZE is in-line in the class
  */

/*
 * PREORDER TRAVERSE AND WRITE
 * !IMPORTANT! Note: This function calls another function from the PARTICIPANT CLASS in participant.h and participant.cpp
 * Function takes an ostream (a binary file in this case) and a position to begin the traversal from
 */
 template<class T>
 void BinarySearchTree<T>::preorderTraverseAndWrite(ostream& output, const Position<T>& p) const
 {
	if (p.isInternal()) //if the position is internal (the tree has real nodes)
	{
		p.getItem().write(output); //write the item from the first to the output
		//call the function again to the left and right to write all the items to the output
		preorderTraverseAndWrite(output, p.left());
		preorderTraverseAndWrite(output, p.right());
	}
 }

 /*
  * TRAVERSE AND PRINT
  * This fx calls one of the private traverse and print function depending on what was passed in the 'type' parameter
  * Parameter Position<T> p is necessary to pass to the private traverse and print fxs
  * Note: p should be 'regular', not pointer
  */
template<class T>
void BinarySearchTree<T>::traverseAndPrint(const Position<T>& p, int type) const
 {
	if(type == PREORDER)
	{
		preorderTraverseAndPrint(p);
	}
	else if(type == INORDER)
	{
		inorderTraverseAndPrint(p);
	}
	else if(type == POSTORDER)
	{
		postorderTraverseAndPrint(p);
	}
 }

//---------------------------------------------------------//
//PRIVATE FUNCTIONS
//traversals first, then utilities in alphabetical order

// *-ORDER TRAVERSE AND PRINT
//all take a position parameter and return nothing
template<class T>
void BinarySearchTree<T>::preorderTraverseAndPrint (const Position<T>& p) const
{
	if (p.isInternal())
	{
		cout << p.getItem();
		preorderTraverseAndPrint(p.left());
		preorderTraverseAndPrint(p.right());
	}
}

template<class T>
void BinarySearchTree<T>::inorderTraverseAndPrint (const Position<T>& p) const
{
	if (p.isInternal())
	{
		inorderTraverseAndPrint(p.left());
		cout << p.getItem();
		inorderTraverseAndPrint(p.right());
	}
}

template<class T>
void BinarySearchTree<T>::postorderTraverseAndPrint (const Position<T>& p) const
{
	if (p.isInternal())
	{
		postorderTraverseAndPrint(p.left());
		postorderTraverseAndPrint(p.right());
		cout << p.getItem();
	}
}

//COPY TREE UTILITY
/* copyTree utility function that copies one tree to this' tree
 * Parameters
 *    p pointer to parent in this' tree that new node's
         parentPtr should point to
 *    n pointer to new node in tree to copy from
 * Returns pointer to node just allocated for this' tree or NULL
 *   (if at the end of a branch) and no new node to copy
 */
template <class T>
Node<T>* BinarySearchTree<T>::copyTree (Node<T>* p, Node<T>* n)
{
	//1.	if n is not NULL then there’s tree to copy
	if (n != NULL)
	{
		//a.	newNode = allocate a node( *n ) // so, new node has n’s data
		Node<T>* newNode = new Node<T> (*n);
		//b.	newNode’s parentPtr = p
		newNode -> parentPtr = p;
		//c.	newNode’s leftPtr = copyTree( newNode, n’s leftPtr )
		newNode -> leftPtr = copyTree (newNode, n -> leftPtr);
		//d.	newNode’s rigthPtr = copyTree( newNode, n’s rightPtr
		newNode -> rightPtr = copyTree (newNode, n -> rightPtr);
		//e.	return newNode
		return newNode;
	}
	else
	{
		return NULL;
	}
}


/*
 * DELETE UTILITY deletes all nodes in the tree
 * recursive, post-order traversal whose parameter is the subroot the traversal is operating on.
 * The destructor can’t be recursive because it can’t have a parameter, so this fx solves that problem.
 */
template <class T>
void BinarySearchTree<T>::deleteUtility(Node<T>* subroot)
{
	 //will delete every node including superroot and fake leaves
	 //base case can't ask if it's external because we want the externals (fakes) deleted too.
	 //base case SHOULD ask if pointer is NULL, if pointer is NULL then there's nothing to delete, move on.
	 //1.	if the subroot isn’t NULL (base case is subroot is NULL)
	 if (subroot != NULL)
	 {
		 //call deleteUtility going left
		 deleteUtility (subroot->leftPtr);
		 //call deleteUtility going right
		 deleteUtility (subroot->rightPtr);
		 //delete the subroot
		 delete subroot;
	 }
	 else //(subroot == NULL)... when we reach the superroot.
	 {
		 delete subroot;
	 }
}

/*
 * ERASE UTILITY
 * Parameter: a Position (iterator), p, whose node is the node with the key to delete.
 * This function determines a leaf node to swap the node to delete (if necessary), then calls removeAboveExternal
 * to remove the leaf or node with one subtree
 * Returns Position<T> which should be the parameter Position<T> p as p was never changed in the fx.
 */
 template<class T>
 Position<T> BinarySearchTree<T>::eraseUtility (const Position<T>& p)
 {
	Position<T> w, u;
	 //if p has empty left subtree (points to a fake end node)
	 if (p.left().isExternal())
	 {
		 //w = p’s fake/left node (fake leaf below node to erase)
		 w = p.left();
	 }

	 //else if p has empty right subtree (points to a fake end node)
	 else if (p.right().isExternal())
	 {
		 //w = p’s fake/right node
		 w = p.right();
	 }

	 //else (case 3 – p has two, non-empty subtrees)
	 else	//if w is an internal node (not a fake leaf)
		 	//if (w.isInternal())
	 {
		 w = p.right(); //don't want to change position p
		 do {
			 w = w.left();
		 } while (w.isInternal());
		 u = w.parent();
		 p.nodePtr->item = u.getItem();

		 	 	/*MY ATTEMPT USING THE ++ OPERATOR.
		 	 	 w = p; //don't want to change position p
		 		 ++w; //traverse right then left as far as you can
		 		 p.nodePtr->item = w.nodePtr->item; //p’s data = w’s data
		 		 w = w.left(); //move w to the external node ABOVE to call */
	 }
	 //remove w's parent
	 //call removeAboveExternal and pass it w, the fake leaf node that is below the node to delete
	 removeAboveExternal(w);
	 return p;
 }

 /* EXPAND EXTERNAL - inserts item by copying its data to
  *   position p and setting position's left and right ptrs
  *   to end nodes
  * Parameters
  *   item to be inserted
  *   p fake end node where item will be inserted
  * Precondition: p is an external node (a fake leaf) and
  *    class T has overloaded = operator
  */
 template <class T>
 void BinarySearchTree<T>::expandExternal(const T& item, Position<T>& p)
 {
	 //1.	left = new Node
	 Node<T>* leftPtr = new Node<T>();
	 //2.	right = new Node
	 Node<T>* rightPtr = new Node<T>();
	 //3.	p.nodePtr’s leftPtr = left
	 p.nodePtr->leftPtr = leftPtr;
	 //4.	p.nodePtr’s rightPtr = right
	 p.nodePtr->rightPtr = rightPtr;
	 //5.	left’s parent = p.nodePtr
	 leftPtr->parentPtr = p.nodePtr;
	 //6.	right’s parent = p.nodePtr
	 rightPtr->parentPtr = p.nodePtr;
	 //7.	p.nodePtr’s item = item
	 p.nodePtr->item = item;
	 //8.	numNodes++
	 numNodes++;
 }

 /* FIND UTILITY: recursive utility find function
  * Parameters:
  *   item to look for
  *   p position to start looking from
  * Pre-condition: class T has overloaded operator== and
  *   operator<, tree not empty of real nodes
  * Returns position iterator where found or NULL iterator
  */
 template <class T>
 Position<T> BinarySearchTree<T>::findUtility(const T& item, const Position<T>& p) const
 {
	// 1.	If the subroot, the current position, p, is external, then we’ve hit a fake end node without finding the item, we’re not going to find the item, so return the fake end node – a base case to end the recursion.
	if (p.isExternal())
	{
		return p;
	}
	// 2.	If the item we’re looking for is equal to the item in the subroot/position, p, parameter, then we’ve found the item so return this position – another base case for recursion.
	else if (item == p.getItem())
	{
		return p;
	}
	// 3.	If the item we’re looking for is less than the item at p, return what the call to findUtility with a position going left returns
	else if (item < p.getItem())
	{
		return findUtility (item, p.left());
	}
	// 4.	Otherwise return what the call to the findUtility with a position going right returns
	else //(item > p.getItem())
	{
		return findUtility (item, p.right());
	}
 }

 /* INSERT UTILITY: inserts at position for new node
  * Parameters: new node to insert
  * Returns iterator to newly inserted object or to superRoot
  *    fake node if item already in tree
  */
 template <class T>
 Position<T> BinarySearchTree<T>::insertUtility(const T& item)
 {
	 //1.	foundPosition = findUtility( item, root )
	 Position<T> foundPosition;
	 foundPosition = findUtility (item, root());
	 //2.	if foundPosition is a fake end node (then item not already in tree)
	 if (foundPosition.isExternal())
	 {
	 	 // a.	call expandExternal to insert the item in the tree
		 expandExternal(item, foundPosition);
	 	 // b.	return foundPosition which is the node where the item was inserted
		 return foundPosition;
	 }
	//3.	else return superroot Position object because the item is already in the tree
	 else
	 {
		 return Position<T>(superRootPtr); //superroot ptr is a position object, why declare it as a position object in return statement
	 }
 }

 /* REMOVE ABOVE EXTERNAL: removes internal node just above fake leaf node pointed to by p.
  * Decrements number of nodes in tree.
  * Parameter: p leaf node of real node to delete
  * Returns position iterator to sibling of node removed
  */
 template <class T>
 Position<T> BinarySearchTree<T>::removeAboveExternal(const Position<T>& p)
 {
	 Node<T> *siblingPtr, *grandparentPtr;
	 Node<T> *v, *w;
	 //1.	w = p’s nodePtr (so, w is a Node* and points to p’s node)
	 w = p.nodePtr;
	 //2.	v = p’s parent pointer (v points to the real (not external/fake) node to delete)
	 v = w->parentPtr;
	 //3.	if w comes from the left of its parent
	 if (w == v->leftPtr)
	 {
		 //	a.	siblingPtr = v’s rightPtr (to set sibling of w)
		 siblingPtr = v->rightPtr;
	 }
	 //4.	else
	 else
	 {
		 // a.	siblingPtr = v’s leftPtr
		 siblingPtr = v->leftPtr;
	 }
	 //5.	if removing actual root (v is the superroot’s rightPtr)
	 if (v == superRootPtr->rightPtr)
	 {
	 	 // a.	superrootPtr’s rightPtr = siblingPtr
		 superRootPtr->rightPtr = siblingPtr;
	 	 // b.	siblingPtr’s parentPtr = superrootPtr
		 siblingPtr->parentPtr = superRootPtr;
	 }

	 //6.	else // removing a leaf that isn’t the actual root
	 else
	 {
	 	 // a.	grandparentPtr (of w and parent of v) = v’s parent
		 grandparentPtr = v->parentPtr;
	 	 // b.	if v, the real node to remove, is to the left of its parent (if grandparentPtr’s leftPtr == v )
		 if (grandparentPtr->leftPtr == v)
		 {
			 //i.	grandparent’s leftPtr = siblingPtr (put v’s sibling in place of v)
			 grandparentPtr->leftPtr = siblingPtr;
		 }
	 	  //c.	else // v is to the right of its parent
		 else // (grandparentPtr->rightPtr == siblingPtr)
		 {
	 	 	 //i.	grandparent’s rightPtr = siblingPtr
			 grandparentPtr->rightPtr = siblingPtr;
		 }
	 	 //d.	siblingPtr’s parentPtr = grandparentPtr
		{
		siblingPtr->parentPtr = grandparentPtr;
		}
	 }
	 //7.	delete w (fake end node)
	 delete(w);
	 //8.	delete v (real node to delete)
	 delete(v);
	 //9.	numNodes--
	 numNodes--;
	 //10.	return Position of siblingPtr
	 return Position<T>(siblingPtr);

 }

 /*
 * OVERLOADED OPERATOR= - assigns the values of BinarySearchTree<T> tree (the parameter) to a new BST (the invoking object) by deepcopy
 * Note 1: If the BST is empty, the fx simply makes an empty tree by mimicking the code of the default ctor
 * Note 2: If the BST is not empty, the copyTree fx is called to copy the tree to the invoking BST
 */
 template <class T>
 BinarySearchTree<T>& BinarySearchTree<T>::operator= (const BinarySearchTree& tree)
 {
 	 //delete the existing destination BST (the invoking object) before copying from the source BST
	 tree.deleteUtility(superRootPtr);
 	 //numNodes = tree.numNodes
 	 numNodes = tree.numNodes;
 	 //superRootPtr = new Node
 	 superRootPtr = new Node<T>();
 	 //if b is empty (then so will this tree be empty and we only need a fake leaf node)
 	 if (tree.empty())
 	 {
 		 //superRootPtr’s rightPtr = new Node
 		 superRootPtr->rightPtr = new Node<T>();
 		 //superRootPtr’s rightPtr’s parentPtr = superRootPtr (so the fake leaf points back to its parent)
 		 superRootPtr->rightPtr->parentPtr = superRootPtr;
 	 }
 	 //else ('tree' has real nodes in it)
 	 else
 	 {
 	 	 //superRootPtr’s rightPtr = copyTree( superRootPtr, tree.superRootPtr’s rightPtr)
 		 superRootPtr->rightPtr = copyTree(superRootPtr, tree.superRootPtr->rightPtr);
 	 }
 	 return *this;
  }


#endif //BINARYSEARCHTREE_H