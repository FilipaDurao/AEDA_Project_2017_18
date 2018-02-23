#ifndef TIME_H_
#define TIME_H_

#include <iostream>
#include <string>

using namespace std;

class TimeOperationException {
	string message;
public:
	TimeOperationException(string message) : message(message) {}
};

struct Date {
	int day = 0;
	int month = 0;
	int year = 0;
};


struct Hours {
	int minutes = 0;
	int hours = 0;
};

class Time {

public:
	Time(int totalMinutes);
	Time(int hours, int minutes, int day, int month, int year);
	Time(int hours, int minutes);
	Time(int day, int month, int year);
	Time(Hours hours);
	Time(Date date);
	Time(Hours hours, Date date);
	Time();

//Getters
	int getHours();
	int getMinutes();
	int getDay();
	int getMonth();
	int getYear();
	Date getDate();
	int getTotalMinutes();

	void validateTime();

	Time operator+(Time time);
	Time operator-(Time time);
	bool operator>(Time time);

	void displayTime() const;
	static string makeMinTwoCharacters(int value);

	bool isLeap(int year);

	friend ostream& operator<<(ostream& os, Time& t);


private:
	int getMonthDays(int month, int year);
	int dateToDays();
	Date daysToDate(int days);
	Date date;
	Hours hours;
};

//Receive time user input
Time getCurrentTimeInput();
#endif /* TIME_H_ */
