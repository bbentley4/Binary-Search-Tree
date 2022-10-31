/*
 * File: utility.h
 * Description: Contains functions necessary to run main.cpp but do not belong to any class.
 * Note: This file was is only useful for Lab 4, PSCC tracker. Use in other contexts would require modification.
 * Author: Brenna Bentley
 * Date Created: 4/21/22
 * Last Edit: 4/26/22
 */

#include "binarySearchTree.h"
#include "position.h"
#include "node.h"
#include "participant.h"
#include "activity.h"

//FUNCTION HEADERS
//fx for user option 1, Remove participant - removes a participant from the tree
void removeParticipant (BinarySearchTree<Participant>&);
//fx for user option 2, Add participant - adds a participant to the tree
void addParticipant (BinarySearchTree<Participant>&);
//fx for user option 3, Add activity - adds an activity to a participant
void addActivity (BinarySearchTree<Participant>&);
//fx for user option 4, Calculate total miles walked - calculates the total miles walked by all participants in the tree
void calculateTotalMiles (BinarySearchTree<Participant>&);
