/*
 * File: activity.cpp
 * Description: contains function definitions (that are not already defined in-line in the class) for activity.h
 * Note: This file was designed with the intent to be used by the Participant class
 * Necessary files: activity.h
 * Author: Brenna Bentley
 * Date Created: 4/19/22
 * Last Edit: 4/26/22
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include "activity.h"
using std::ostream;
using std::istream;
using std::string;
using std::vector;
using std::endl;


/*
 * DEFAULT CONSTRUCTOR - creates empty Activity by setting the two private members CODE and MINUTES to 0.
 */
Activity::Activity()
{
	code = 0;
	minutes = 0;
}

/*
 * COPY CONSTRUCTOR - copies Activity a (the parameter) to a new Activity (the invoking object)
 */
Activity::Activity(const Activity& a)
{
	this->code = a.code;
	this->minutes = a.minutes;
}

/*
 * SETCODE - assigns private member CODE the value of parameter c
 */
void Activity::setCode (int c)
{
	code = c;
}

/*
 * SETMINUTES - assigns private member MINUTES the value of parameter m
 */
void Activity::setMinutes (int m)
{
	minutes = m;
}

/* GETMILES: Calculate the miles walked by doing ACTIVITY for MINUTES, then return the miles.
 * Parameters: double height - the height of the person taking the steps, used to calculate feet per step
 * Returns: double miles
 * Note on use: This only gets the miles for one activity by one participant (unknown to the activity class)
 * 		 by being called within the participant class. Example: activity[i].getMiles(height)
 */
double Activity::getMiles (double height)
{
	//int actCode = this->code;
	//int actMin = this->minutes;
	int steps = ACTIVITY_STEPS[code] * minutes;
	double stepSize = (0.413*height) / 12;
	double miles = (steps * stepSize) / feetPerMile;
	return miles;
}
