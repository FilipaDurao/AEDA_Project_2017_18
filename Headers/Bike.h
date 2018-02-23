#ifndef BIKE_H_
#define BIKE_H_

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include "Time.h"

using namespace std;

enum typeOfBike {urban, urbanSimple, race, child};
enum bikeState {good, reapairing, broken};


class Bike {
private:
	const typeOfBike type;				/**< The bike type */
	Time initialTime;					/**< The time when it returns the bike */
	bool availability;					/**< Availability of the bike, True if available, False if not*/
	const unsigned int ID;
	bikeState state;
	Time scrappingDate;
	static unsigned int lastID;

public:
	Bike(typeOfBike type, unsigned int ID);
	~Bike();

	// getters
	typeOfBike getType() const;
	string getTypeInString() const;
	Time getInitialTime() const;
	bool getAvailability() const;
	unsigned int getID() const;
	bikeState getState() const;
	Time getScrappingDate() const;

	// setters
	void setInitialTime(Time initialTime);
	void setAvailability(bool availability);
	void setState(bikeState state);
	void setScrappingDate(Time scrappingDate);

};

struct bikeScrappingHash
{
	int operator() (const Bike * bike) const
	{
		return bike->getID();
	}

	bool operator() (const Bike* b1, const Bike* b2) const
	{
		return (b1->getID() == b2->getID());
	}
};

typedef unordered_set<Bike*, bikeScrappingHash, bikeScrappingHash> bikeScrapping;

#endif /* BIKE_H_ */
