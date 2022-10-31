* File: activity.h
 * Description: Contains the class definition for Activity. Functions for this class are defined in-line or in activity.cpp.
 * Note: This file was designed with the intent of being used by the Participant class
 * Author: Brenna Bentley
 * Date Created: 4/19/22
 * Last Edit: 4/26/22
 */

#ifndef ACTIVITY_H
#define ACTIVITY_H

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

//The list of available activities by name
typedef enum {
	ASSEMBLY_LINE, BASKETBALL_SHOOTING, BASKETBALL_GAME, BICYCYLING_UNDER10, BICYCLING_OVER10, COOKING, DANCE, FOOTBALL,
	HIKING,HOUSE_CLEANING, GARDENING, MINATURE_GOLF, RACQUETBALL, ROWING, RUNNING_6MPH, RUNNING_7MPH, RUNNING_8MPH, SHOPPING,
	SOCCER, SOFTBALL, STAIRS, SWIMMING_LAPS, TENNIS, WALKING_3MPH, WALKING_4MPH, WEIGHT_LIFTING, YOGA
} activity_t;

/*An array of steps and activity names. Each number in ACTIVITY_STEPS is the number of steps that correspond to the activity
at the same index in ACTIVITY_NAME. For instance, ACTIVITY_NAME[0] = ASSEMBLY_LINE and ACTIVITY_STEPS[0] = 85;
That means there's 85 steps per minute in assembly line work. */
const int ACTIVITY_STEPS [] = {85, 136, 242, 121, 242, 61, 167, 242, 182, 91, 99, 91, 212, 212, 303, 348, 409, 70, 212, 152, 273, 212, 212, 100, 152, 121, 76};
const std::string ACTIVITY_NAME [] = {"assembly line", "basket ball shooting", "basketball game", "bicycling (under 10mph)", "bicycling (over 10mph)", "cooking", "dance",
		"football", "hiking","house cleaning", "gardening", "miniature golf", "racquetball", "rowing", "running (6 mph)", "running (7 mph)", "running (8 mph)",
		"shopping", "soccer", "softball", "stairs", "swimming laps", "tennis", "walking (3 mph)", "walking (4 mph)", "weight lifting", "yoga"};


const double feetPerMile = 5280.0;  //5280 ft in a mile.

class Activity {
public:
	Activity(); // default constructor
	Activity(const Activity&); //copy constructor
	virtual ~Activity() {} // destructor
	void setCode (int); //assigns private member CODE the value of parameter
	int getCode () const {return code;} //returns copy of private member CODE
	void setMinutes (int); //assigns private member MINUTES the value of parameter
	int getMinutes () const {return minutes;} //returns copy of private member MINUTES
	double getMiles (double);  //returns the amount of miles completed by one activity (see activity.cpp for more info)
private:
	int code; //the index of the activity
	int minutes; //the amount of minutes spent doing the activity
};


#endif