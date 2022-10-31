#include <iostream>
#include <cstring>
#include <iomanip>
#include <cctype>
#include "binarySearchTree.h"
#include "position.h"
#include "node.h"
#include "participant.h"
#include "activity.h"
#include "utility.h"
using std::islower;
using std::endl;


//DECLARATIONS OF VARIABLES FOR FXS
char last_name [MAX_NAME_LENGTH]; //for cin Particpant lastName
char first_name [MAX_NAME_LENGTH]; //for cin Participant firstName
double participant_height; //for cin Participant height
int activity_index; //for cin Activity code
int activity_minutes; //for cin Activity minutes
int i; //loop control
Participant tempP; //temporary Participant

/* REMOVE PARTICIPANT - fx for user option 1, Remove participant - removes a participant from the tree
 * Parameter: the BST which the participant is to be removed from
 */
void removeParticipant (BinarySearchTree<Participant>& tree)
{
	//read in last name, first name, then correct capitalization for both
	cout << "Last name: ";
	cin >> last_name;
	last_name[0] = toupper(last_name[0]);
	i = 1;
	while (last_name[i] != '\0')
	{
		last_name[i] = tolower(last_name[i]);
		i++;
	}

	cout << "First name: ";
	cin >> first_name;
	first_name[0] = toupper(first_name[0]);
	i = 1;
	while (first_name[i] != '\0')
	{
		first_name[i] = tolower(first_name[i]);
		i++;
	}

	//fill in temp Participant
	tempP.setFirstName(first_name);
	tempP.setLastName(last_name);
	tempP.createKey();

	//use find fx to find real participant key that matches our temp participant key
	if (tempP == tree.find(tempP).getItem())
	{
		//assign Participant item from actual node in tree to our tempP
		tempP = tree.find(tempP).getItem();

		//print out the removal message with miles to 2 decimals
		cout << tempP.getFirstName() << " " << tempP.getLastName() << ", " << fixed << setprecision(2) <<
				tempP.getTotalMiles() << " total miles walked removed." << endl;

		//use erase fx to find the node with item identical to tempP and erase
		tree.erase(tempP);
	}
	else //key of tempP did not match any keys in BST -- let the user know.
	{
		cout << "No participant named " << first_name << " " << last_name << " found." << endl;
	}

}

/* ADD PARTICIPANT - fx for user option 2, Add participant - adds a participant to the tree
 * Parameter: the BST which the participant is to be added to
 */
void addParticipant (BinarySearchTree<Participant>& tree)
{
	//read in last name, first name, then correct capitalization for both
	cout << "Last name: ";
	cin >> last_name;
	last_name[0] = toupper(last_name[0]);
	i = 1;
	while (last_name[i] != '\0')
	{
		last_name[i] = tolower(last_name[i]);
		i++;
	}

	cout << "First name: ";
	cin >> first_name;
	first_name[0] = toupper(first_name[0]);
	while (first_name[i] != '\0')
	{
		first_name[i] = tolower(first_name[i]);
		i++;
	}

	//fill in temp Participant to create key to search the tree
	tempP.setFirstName(first_name);
	tempP.setLastName(last_name);
	tempP.createKey();

	//use find fx to find real participant key that matches our temp participant key
	if (tempP == tree.find(tempP).getItem())
	{
		//if they're already a participant, let the user know
		cout << tempP.getFirstName() << " " << tempP.getLastName() << " is already a participant." << endl;
	}
	else
	{
		//if they're not already a participant, ask for their height, set the height for our tempP Participant, and insert tempP into tree
		cout << "Height in inches: ";
		cin >> participant_height;
		tempP.setHeight(participant_height);
		tree.insert(tempP);
		//print message letting user know this was successful
		cout << tempP.getFirstName() << " " << tempP.getLastName() << " has been added." << endl;
	}

}

/* ADD ACTIVITY - fx for user option 3, Add activity - adds an activity to a participant
 * Parameter: the BST which the participant that the fx will add the activity to
 */
void addActivity (BinarySearchTree<Participant>& tree)
{
	//read in last name, first name, then correct capitalization for both
	cout << "Last name: ";
	cin >> last_name;
	last_name[0] = toupper(last_name[0]);
	i = 1;
	while (last_name[i] != '\0')
	{
		last_name[i] = tolower(last_name[i]);
		i++;
	}

	cout << "First name: ";
	cin >> first_name;
	first_name[0] = toupper(first_name[0]);
	while (first_name[i] != '\0')
	{
		first_name[i] = tolower(first_name[i]);
		i++;
	}

	//fill in temp Participant to create key to search the tree
	tempP.setFirstName(first_name);
	tempP.setLastName(last_name);
	tempP.createKey();

	//use find fx to find real participant key that matches our temp participant key
	Participant emptyP;
	if (tempP == tree.find(tempP).getItem())
		{
			//assign Participant item from actual node in tree to our tempP
			//fx can manipulate tempP, not the original Participant in the BST structure
			//getItem only gives a copy of the Participant
			tempP = tree.find(tempP).getItem();

			//get information from user about the Activity (the code and minutes)
			cout << "Activity: ";
			cin >> activity_index;
			cout << "Minutes: ";
			cin >> activity_minutes;

			//add the activity
			tempP.addActivity(activity_index, activity_minutes);

			//calculate miles for this new activity
			//the reason I use numActivities-1 is because my addActivity fx increments numActivity
			double miles = (tempP.getActivity(tempP.getNumActivities()-1)).getMiles(tempP.getHeight());

			//let user know the addition was successful and how many miles were walked from this new activity
			cout << "Added " << tempP.getFirstName() << " " << tempP.getLastName() << ", " << ACTIVITY_NAME [activity_index]
					<< ", " << activity_minutes << " minutes = " << fixed << setprecision(2)
					<< miles << " miles" << endl;

			//since we did not make any changes to Participant in the original node in the tree, delete it
			tree.erase(tree.find(tempP));
			//insert the updated Participant
			tree.insert(tempP);
		}
		else //if the Participant key wasn't found in the tree, tell the user
		{
			cout << tempP.getFirstName() << " " << tempP.getLastName() << " is not a participant." << endl;
		}
}

/*
 * CALCULATE TOTAL MILES - fx for user option 4, Calculate total miles walked
 * Parameter: the BST which holds the Participants to collect and add the totalMiles from
 */
void calculateTotalMiles (BinarySearchTree<Participant>& tree)
{
	double totalClassMiles = 0; //start at 0
	//traverse through tree
	Position<Participant> pos = tree.begin();
	for ( ; pos != tree.end(); ++pos)
	{
		//add each Participant's miles together for TOTAL total
		totalClassMiles += (pos.getItem()).getTotalMiles();
	}
	//print
	cout << "Total miles walked by *everyone* = " << fixed << setprecision(2) << totalClassMiles << "!" << endl;
}