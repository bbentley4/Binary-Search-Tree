/*
 * File: participant.h
 * Description: Contains the class definition for Participant. Functions for this class are defined in-line or in participant.cpp.
 * Necessary files: activity.h
 * Author: Brenna Bentley
 * Date Created: 4/19/22
 * Last Edit: 4/26/22
 */

#ifndef PARTICIPANT_H
#define PARTICIPANT_H

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <iomanip>
#include "activity.h"
using std::ostream;
using std::istream;
using std::string;
using std::vector;
using std::endl;

const int MAX_ACTIVITIES = 365; //max activities a Participant can have
const int MAX_NAME_LENGTH = 25; //max length a Participant name can be

class Participant {
public:
	//default constructor
	Participant();
	//copy constructor
	Participant(const Participant&);
	//destructor
	virtual ~Participant() {}

	//assigns private member ___ the value of parameter
	void setFirstName(char*); //firstName
	void setLastName (char*); //lastName
	void setKey (char*); //key
	void setHeight (double);  //height
	void setNumActivities (int); //numActivities
	void setActivity (int, int, int); //act //setActivity is slightly different than others, see fx in cpp file
	void setTotalMiles (double); //totalMiles

	//returns copy of private member ___
	char* getFirstName() {return firstName;} //firstName
	char* getLastName () {return lastName;} //lastName
	char* getKey () {return key;} //key
	double getHeight () const {return height;} //height
	int getNumActivities () const {return numActivities;} //numActivities
	Activity getActivity (int i) {return act[i];} //act at index i
	double getTotalMiles () {return totalMiles;} //totalMiles

	//creates a key by concatenating firstName to lastName in all lowercase
	void createKey();
	//calculates totalMiles done by one Participant from all their activities
	double calculateTotalMiles ();
	//add an activity to the act array in a Participant
	void addActivity (int, int);
	//writes a copy of an *entire* Participant to the ostream parameter
	ostream& write (ostream&);

	//compares the keys of the invoking Participant and the parameter Participant
	//returns true if invoking Participant's key is less than the parameter Participant's key
	bool operator < (const Participant&) const;
	//returns true if they are the same
	bool operator == (const Participant&) const;

	//writes the firstName, lastName, and totalMiles (to 2 decimals) of a Participant to the ostream parameter
	friend ostream& operator << (ostream&, const Participant&);

private:
	char firstName [MAX_NAME_LENGTH]; //a participant's first name
	char lastName [MAX_NAME_LENGTH]; //a participant's last name
	char key [2*MAX_NAME_LENGTH]; //participant's key is their firstname concatenated to their lastname in all lowercase
	double height; //the height of the participant in inches
	int numActivities; // the number of activities one participant did
	Activity act [MAX_ACTIVITIES]; //the participant's array of activities (activity class consists of activity code and minutes)
	double totalMiles; //a single participant's total miles
};

#endif
