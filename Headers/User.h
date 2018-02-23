#ifndef USER_H_
#define USER_H_

#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "Bike.h"
#include "Time.h"
#include "Place.h"

using namespace std;

//class Company;

class User {
private:
	Place *startPlace;			// Place where it picks up the bike
	Bike *bike;					// The bike its using
public:
	User(Place *startPlace, Bike *bike);
	User();
	virtual ~User();

	virtual const unsigned int getUserID() = 0;
	virtual float calcPayment(int amountOfMinutes) = 0;
	virtual float getAmountToPay() = 0;
	virtual void displayUser () const = 0;
	virtual bool isPremium() = 0;
	virtual bool writeUserInfo(ostream & out_stream) const = 0;
	virtual void showReceipt(Time startTime, Time endTime) = 0;


	// GETTERS
	Place* getStartPlace() const;
	Bike* getBike() const;


	// SETTERS
	void setStartPlace(Place *startPlace);
	void setBike(Bike *bike);

	// OTHERS
	virtual void returnBike(Place* endPlace, Time endTime) = 0;
};

#endif /* USER_H_ */
