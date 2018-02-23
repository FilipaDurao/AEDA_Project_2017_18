#include <climits>
#include "Time.h"
#include "utilities.h"

/**
 * @param hours, minutes, day, month, year
 *
 * \brief Creates an object of the class Time.
 *
 */
Time::Time(int hours, int minutes, int day, int month, int year) {

date.day = day-1;
date.month = month-1;
date.year = year;

this->hours.minutes = minutes;
this->hours.hours = hours;

validateTime();

}

/**
 * @param hours, minutes
 *
 * \brief Creates an object of the class Time.
 *
 */
Time::Time(int hours, int minutes) {

	this->hours.minutes = minutes;
	this->hours.hours = hours;

	validateTime();
}

/**
* @param total minutes
*
* \brief Creates an object of the class Time.
*
*/
Time::Time(int totalMinutes) {
	this->hours.minutes = totalMinutes;
	this->hours.hours = 0;
	validateTime();
}

/**
 * @param day, month, year
 *
 * \brief Creates an object of the class Time.
 *
 */
Time::Time(int day, int month, int year) {

	date.day = day;
	date.month = month;
	date.year = year;

	validateTime();
}

/**
 * @param Hours(hour and minute)
 *
 * \brief Creates an object of the class Time.
 *
 */
Time::Time(Hours hours) : hours(hours) { validateTime();  }

/**
 * @param Date(day, month and year)
 *
 * \brief Creates an object of the class Time.
 *
 */
Time::Time(Date date) : date(date) {validateTime(); }

/**
 * @param Hours, Date
 *
 * \brief Creates an object of the class Time.
 *
 */
Time::Time(Hours hours, Date date) : hours(hours), date(date) { validateTime(); }

Time::Time(){
	date.day = -1;
	date.month=-1;
	date.year=-1;
	hours.hours=-1;
	hours.minutes=-1;
}

/**
 * @param None
 *
 * \brief Returns the hour of the Time
 *
 * @return hour
 */
int Time::getHours() {
	return this->hours.hours;
}

/**
 * @param None
 *
 * \brief Returns the minute of the Time
 *
 * @return minute
 */
int Time::getMinutes() {
	return this->hours.minutes;
}

/**
 * @param None
 *
 * \brief Returns the day of the Time
 *
 * @return day
 */
int Time::getDay() {
	return this->date.day;
}

/**
 * @param None
 *
 * \brief Returns the month of the Time
 *
 * @return month
 */
int Time::getMonth() {
	return this->date.month;
}

/**
 * @param None
 *
 * \brief Returns the year of the Time
 *
 * @return year
 */
int Time::getYear() {
	return this->date.year;
}

/**
 * @param None
 *
 * \brief Returns the Date of the Time
 *
 * @return Date
 */
Date Time::getDate() {
	return this->date;
}

/**
 * @param month, year
 *
 * \brief Returns the number of days in a given month
 *
 * @return numberOfDays
 */
int Time::getMonthDays(int month, int year) {
	int numberOfDaysInMonth;
	month++;

	switch (month) {
	case 1: case 3: case 5: case 7: case 8: case 10: case 12:
		numberOfDaysInMonth = 31;
		break;

	case 4: case 6: case 9: case 11:
		numberOfDaysInMonth = 30;
		break;

	case 2:
		if (isLeap(year)) numberOfDaysInMonth = 29;
		else numberOfDaysInMonth = 28;
		break;

	default:
		numberOfDaysInMonth = 30;
	}

	return numberOfDaysInMonth;
}

/**
 * @param year
 *
 * \brief Returns if its a leap year or not
 *
 * @return isLeap
 */
bool Time::isLeap(int year) {
	return year % 4 == 0 && (year % 400 == 0 || year % 100 != 0);
}

bool Time::operator>(Time time2) {

	if (date.year > time2.getYear())
		return true;

	else if (date.year == time2.getYear() && date.month > time2.getMonth())
		return true;

	else if (date.year == time2.getYear() && date.month == time2.getMonth() && date.day > time2.getDay())
		return true;

	else if (date.year == time2.getYear() && date.month == time2.getMonth() && date.day == time2.getDay() && hours.hours > time2.getHours())
		return true;

	else if (date.year == time2.getYear() && date.month == time2.getMonth() && date.day == time2.getDay() && hours.hours == time2.getHours() && hours.minutes > time2.getMinutes())
		return true;

	return false;
}

/**
 * @param time2
 *
 * \brief Returns the sum of two times
 *
 * @return Time
 */
Time Time::operator+(Time time2) {
	return Time(this->getTotalMinutes() + time2.getTotalMinutes());
}

/**
* @param time
*
* \brief Returns the subtraction of two times
*
* @return Time
*/

Time Time::operator-(Time time2) {
	if (!(*this > time2)) throw TimeOperationException("Time subtraction values make for a negative result. Can't calculate");
	return Time(this->getTotalMinutes() - time2.getTotalMinutes());
}

/**
* @param days
*
* \brief convert number of days since year 0 to date
*
* @return Date
*/
Date Time::daysToDate(int days) {

	int fullYears = 0;
	int daysInFullYears;

	for (daysInFullYears = 0; daysInFullYears + 365 < days; daysInFullYears += isLeap(fullYears - 1) ? 366 : 365) { //Get amount of full years
		fullYears++;
	}

	int daysInLastYear = days - daysInFullYears;
	int month;
	int day;

	for (int i = 0; true; i++) { //Get amount of months and days
		int currentMonthDays = getMonthDays(i % 12, fullYears);
		daysInLastYear -= currentMonthDays;
		if (i % 12 == 0 && i > 1) fullYears++; //increase year if is january in the processed days (except if is first year of those days)
		if (daysInLastYear <= 0) {
			month = i % 12;
			day = currentMonthDays + daysInLastYear;
			break;
		}
	}
	Date date; //Create the result and set its properties
	date.day = day;
	date.month = month;
	date.year = fullYears;
	return date;
}


/**
* @param None
*
* @brief Converts current date to number of days since year 0
*
* @return days
*/
int Time::dateToDays() {

	int year = this->getYear();
	int month = this->getMonth();
	int day = this->getDay();
	int result = 0;

	for (int i = 0; i < year; i++) {
		if (isLeap(i)) result += 366;
		else result += 365;
	}

	for (int i = 0; i < month; i++) {
		result += getMonthDays(i % 12, year);
	}

	result += day;
	return result;
}

/**
 * @param None
 *
 * \brief Checks if the Time is valid
 *
 * @return None
 */
void Time::validateTime() {
	int minutes = this->getMinutes() % 60;
	int hours = (this->getMinutes() / 60 + this->getHours()) % 24;
	int extraDays = (this->getMinutes() / 60 + this->getHours()) / 24;
	this->date = daysToDate(dateToDays() + extraDays);
	this->hours.minutes = minutes;
	this->hours.hours = hours;
}

/**
 * @param None
 *
 * \brief Displays the Time
 *
 * @return None
 */
void Time::displayTime() const{
	cout << date.day + 1 << "/" << date.month + 1 << "/" << date.year<< " at " << makeMinTwoCharacters(hours.hours) << ":" << makeMinTwoCharacters(hours.minutes) << endl;
}

/**
 * @param None
 *
 * @brief Converts any date to Minutes
 *
 * @return minutes
 */
int Time::getTotalMinutes(){
	return dateToDays() * 24 * 60 + this->hours.hours * 60 + this->hours.minutes;
}

/**
* @param value
*
* @brief converts number to string with at least 2 characters
*
* @return result
*/
 string Time::makeMinTwoCharacters(int value){
	if (value < 10)
		return "0" + to_string(value);
	else return to_string(value);
}


/**
 * @param None
 *
 * @brief Asks the user for Time input (for demo purposes only)
 *
 * @return Time
 */
Time getCurrentTimeInput(){

    Time timeObject = Time(); // this is just an auxiliary obj to access time functions

    int hours, minutes, day, month, year;

    cout << "--CURRENT TIME INPUT--" << endl << endl;

    cout << "Year :";
    year = utilities::getUnsignedIntInput(0, UINT_MAX, "Invalid Input, please try again.");
    cout << "Month (1-12):";
    month = utilities::getUnsignedIntInput(1, 13, "Invalid Input, please try again.");

    cout << "Month Day (1-28/29/30/31):";
    switch(month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            day = utilities::getUnsignedIntInput(1, 32, "Invalid Input, please try again.");
            break;
        case 4: case 6: case 9: case 11:
            day = utilities::getUnsignedIntInput(1, 31, "Invalid Input, please try again.");
            break;
        default:

            if(timeObject.isLeap(year)) { //leap year
                day = utilities::getUnsignedIntInput(1, 30, "Invalid Input, please try again.");
            } else { //normal year
                day = utilities::getUnsignedIntInput(1, 29, "Invalid Input, please try again.");
            }

            break;
    }

    cout << "Hours (0-23):";
    hours = utilities::getUnsignedIntInput(0, 24, "Invalid Input, please try again.");
    cout << "Minutes (0-59):";
    minutes = utilities::getUnsignedIntInput(0, 60, "Invalid Input, please try again.");



    return Time(hours, minutes, day, month, year);

}

ostream& operator<<(ostream& os, Time& t) {
    os << t.getYear() << "/" << Time::makeMinTwoCharacters(t.getMonth()+1) << "/" << Time::makeMinTwoCharacters(t.getDay()+1) << " " << Time::makeMinTwoCharacters(t.getHours()) << ":" << Time::makeMinTwoCharacters(t.getMinutes());
    return os;
}
