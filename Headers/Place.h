#ifndef PLACE_H_
#define PLACE_H_

#include <iostream>
#include <vector>
#include <string>

#include "Bike.h"
#include "Position.h"

using namespace std;

class Place {
private:
	string name;
	Position pos;
	const unsigned int ID;
	vector<Bike*> bikes;
public:
	// constructor and destructor
	Place(string name, unsigned int posX, unsigned int posY, const unsigned int ID);
	virtual ~Place();

	// GETTERS
	string getName() const;
	unsigned int getNumBikes() const;
	vector<Bike*> getBikes() const ;
	const unsigned int getID() const;
	Bike* getBikeInVec(unsigned int index) const;
	Position getPos() const;
	int getBikeInVecByID(int bikeID) const;

	const vector<Bike *> getBikeOfType(typeOfBike t) const;

	// SETTERS
	void addBike(Bike *bike);
	void removeBike(unsigned int index);

	//COMPARATORS
	struct compareByDistanceToPoint : std::binary_function<Place, Place, bool> {
		compareByDistanceToPoint(Position refPos) :refPos(refPos) {}
		bool operator()(Place *p1, Place *p2) {
			double dist1 = p1->getPos().getDistance(refPos);
			double dist2 = p2->getPos().getDistance(refPos);
			return dist1 < dist2;
		}
	private:
		Position refPos;
	};



	// AUXILIARES
	void displayPlace();
	void displayPlaceBikes();
};

#endif /* PLACE_H_ */
