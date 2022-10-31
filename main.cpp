/*
 * File: main.cpp
 * Description: The main file for the PSCC Fitness Tracker program.
 * 		Reads in a binary file with Participants' first name, last name, height, number of activities, then the activity code and minutes
 * 		for each activity. Gives user the options of removing participant, adding participant, adding an activity to a participant,
 * 		calculating total miles walked, doing a pre-order print, or "exit and save".
 * Necessary files: binarySearchTree.h, participant.h, utility.h
 * Author: Brenna Bentley
 * Date Created: 4/19/22
 * Last Edit: 4/26/22
*/
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include "participant.h"
#include "binarySearchTree.h"
#include "utility.h"
using std::cin;
using std::cout;

int main()
{
	ifstream binIn; //binary file to be read
	BinarySearchTree<Participant> pTree; //tree of Participants
	Participant p; //temporary Participant

	//open & read file
	binIn.open("tracking.bin", std::ios::in | std::ios::binary);

	binIn.read((char*) &p, sizeof(Participant)); //prime read of first Participant
	//while the file exists and isn't empty
	while (!binIn.std::ios::fail() && !binIn.eof())
	{
		//user keys are not imported from file and must be made
		p.createKey();
		//user total miles are not imported and must be calculated and set
		p.setTotalMiles(p.calculateTotalMiles());
		//insert the participant into the tree
		pTree.insert(p);
		//read in next Participant
		binIn.read((char*) &p, sizeof(Participant));
	}
	binIn.close(); //close file

	//pTree.traverseAndPrint(pTree.root(), PREORDER); //print test

	//Welcome the user
	cout << "Welcome to the PSCC Fitness Tracker!" << endl
		<< "Please select an option:";

	char choice;

	 do //print the menu and get choice
	 {
		cout << endl; //for formatting so it's not squished together after each reprint of the menu
		cout << "1 Remove participant" << endl
			 << "2 Add participant" << endl
			 << "3 Add activity" << endl
			 << "4 Calculate total miles walked" << endl
			 << "5 Pre-order print" << endl
			 << "6 Exit and save" << endl
			 << "Option> ";
		cin >> choice;
		getc(stdin);
		cout << endl;
		switch (choice)
		{
       		case '1':
       			//remove a participant from the program
       			removeParticipant(pTree);
        		break;
        	case '2':
        		//add a participant to the program
               	 addParticipant(pTree);
            	break;
        	case '3':
        		//add an activity to a participant
           		 addActivity(pTree);
            	break;
            case '4':
            	//calculate and print total miles by all participants
            	calculateTotalMiles(pTree);
            	break;
        	case '5':
        		//pre-order print list
				pTree.traverseAndPrint(pTree.root(), PREORDER);
            	break;
        	case '6':
        		//user wants to quit
        		break;
        	default:
            	//print invalid choice
				printf("Invalid choice. Try again.\n");
				break;
		}
	} while (choice != '6'); //do-while user chooses not to quit
    // end switch


	 //open binary file to be save edited tree to
	 ofstream binOut;
	 binOut.open ("tracking.bin", std::ios::out | std::ios::binary);
	 //write the items (Participants) from the tree to the file in pre-order,
	 pTree.preorderTraverseAndWrite(binOut, pTree.root());
	 //close the file
	 binOut.close();

	 //thank the user for using the program and end program.
	 cout << "Thank you for using the tracker." << endl;


	return 0;
}