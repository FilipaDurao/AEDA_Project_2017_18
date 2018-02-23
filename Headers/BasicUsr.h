#ifndef BASICUSR_H_
#define BASICUSR_H_

#include <iostream>
#include <vector>
#include <string>
#include "User.h"
#include "Time.h"

using namespace std;

class BasicUsr : public User{
private:
	unsigned int tempID;				// A temporary ID so we know who it is and for how long is using the bike
	static unsigned int lastId;			// Holds the value for the last attributed ID to a basic user
	float amount = 0;
	typeOfBike type;		// To use in case it's needed to use to search for nearest places
public:
	BasicUsr(Place *startPlace, typeOfBike type, Time beginTime);
	BasicUsr(unsigned int ID, Place *startPlace, typeOfBike type, Time beginTime, bool fromFile);
	~BasicUsr();

	// GETTERS
	const unsigned int getID() const;
	int getTempIdToSet();
	typeOfBike getType() const;



	// USER METHODS
	float calcPayment(int amountOfMinutes);
	float getAmountToPay();
	void displayUser () const;
	int requestBike(Time now, typeOfBike type, Place *placeBegin);
	void returnBike(Place* endPlace, Time endTime);
	bool isPremium();
	virtual const unsigned int getUserID();
	bool writeUserInfo(ostream & out_stream) const;
	void showReceipt(Time startTime, Time endTime);
};

#endif /* BASICUSR_H_ */
