/*
 * File: participant.cpp
 * Description: contains function definitions (that are not already defined in-line in the class) for participant.h
 * Necessary files: activity.h, participant.h
 * Author: Brenna Bentley
 * Date Created: 4/19/22
 * Last Edit: 4/26/22
 */

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <cctype>
#include "participant.h"
#include "activity.h"
using std::ostream;
using std::istream;
using std::string;
using std::vector;
using std::endl;
using std::setprecision;
using std::fixed;

//DEFAULT CTOR sets all private members to NULL or 0
Participant::Participant()
{
	firstName[0] = '\0';
	lastName[0] = '\0';
	height = 0;
	numActivities = 0;
	for (int i = 0; i < MAX_ACTIVITIES; i++)
	{
		act[i].setCode(0);
		act[i].setMinutes(0);
	}
	totalMiles = 0;
	key[0] = '\0';
}

//COPY CTOR copies private members of the parameter Participant to the invoking Participant
Participant::Participant(const Participant& p)
{
	strcpy (this->firstName, p.firstName);
	strcpy (this->lastName, p.lastName);
	this->height = p.height;
	this->numActivities = p.numActivities;
	for (int i = 0; i < p.numActivities; i++)
	{

		act[i].setCode(p.act[i].getCode());
		act[i].setMinutes(p.act[i].getMinutes());
	}
	this->totalMiles = p.totalMiles;
	strcpy (this->key, p.key);
}

/*
 * SET FUNCTIONS
 * assigns private member ___ the value of the parameter
 */

//set firstName
void Participant::setFirstName (char* name)
{
	strcpy(firstName, name);
}

//set lastName
void Participant::setLastName (char* name)
{
	strcpy (lastName, name);
}

//set key
void Participant::setKey (char* k)
{
	strcpy (key, k);
}

//set height
void Participant::setHeight (double h)
{
	height = h;
}

//set numActivities
void Participant::setNumActivities (int num)
{
	numActivities = num;
}

//set totalMiles
void Participant::setTotalMiles (double miles)
{
	totalMiles = miles;
}

/*set act[i]
*	Parameters: i is the index in the act array to set
			 c is the code of the activity
			 m is the minutes spent doing the activity
	Useful for setting up an array of activities that already exist (from files or copying)
*/
void Participant::setActivity (int i, int c, int m)
{
	act[i].setCode(c);
	act[i].setMinutes(m);
}

//CREATEKEY - creates a key by concatenating Participants' firstName to lastName in all lowercase
void Participant::createKey()
{
	//make a copy of the first and last name to all lower case
	int i = 0;
	char copyfirstName [MAX_NAME_LENGTH];
	char copylastName [MAX_NAME_LENGTH];

	while (firstName[i] != '\0')
	{
			copyfirstName[i] = tolower(firstName[i]);
			i++;
	}
	i = 0;
	while (lastName[i] != '\0')
	{
		copylastName[i] = tolower(lastName[i]);
		i++;
	}
	//concatenate the copied names
	strcpy (key, copylastName);
	strcat (key, copyfirstName);
	//set the created key to the Participant's key
	setKey(key);
}

//CALCULATE TOTAL MILES - calculates totalMiles done by one Participant from all their activities
double Participant::calculateTotalMiles ()
{
	double miles = 0;
	//loop through all of the Participant's activities in their act index
	for (int i = 0; i < numActivities; i ++)
	{
		miles = miles + act[i].getMiles(height);
		//add together all the miles for each activity using getMiles from the Activity class
	}
	return miles; //return the miles
}

//ADD ACTIVITY - add an activity to the act array in a Participant
//doesn't need index because this will add a *new* activity to an already existing array (even it's empty)
void Participant::addActivity (int c, int m)
{
	//use numActivities as the index because the index is always one less than the numActivities
	//if there's 29 activities, the 30th activity will go in index 29
	act[numActivities].setCode(c);
	act[numActivities].setMinutes(m);
	numActivities++; //increase our numActivities since we just added one
	totalMiles = calculateTotalMiles(); //recalculate totalMiles with our new activity
}

//WRITE - writes a copy of an *entire* Participant to the ostream parameter
ostream& Participant::write (ostream& output)
{
	output.write((char*)this, sizeof(Participant));
	return output;
}

//OPERATOR < and OPERATOR == compares the keys of the invoking Participant and the parameter Participant
//operator <: returns true if invoking Participant's key is less than parameter Participant's key
bool Participant::operator < (const Participant& p) const
{
	int value = strcmp (this->key, p.key);
	return value < 0;
}
//operator ==: returns true if invoking Participant's key is the same as the parameter Participant's key
bool Participant::operator == (const Participant& p) const
{
	return strcmp (this->key, p.key) == 0;
}

//OPERATOR <<: writes the firstName, lastName, and totalMiles (to 2 decimals) of a Participant to the ostream parameter
ostream& operator << (ostream& out, const Participant& p)
{

	out << p.firstName << " " << p.lastName << " " << fixed << setprecision(2) << p.totalMiles << endl;
	return out;
}