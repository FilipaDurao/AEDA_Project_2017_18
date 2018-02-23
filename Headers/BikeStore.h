#ifndef BIKESTORE_H_
#define BIKESTORE_H_

#include <string>

#include "Bike.h"

class BikeStore {
private:
	string name;
	int reputation;
	vector <pair<typeOfBike, unsigned int>> stock;
	vector <typeOfBike> typesForSale;

public:
	BikeStore(string name, int reputation, vector <pair<typeOfBike, unsigned int>> stock, vector <typeOfBike> typesForSale);
	virtual ~BikeStore();


	// GETTERS
	string getName() const;
	int getReputation() const;
	vector <pair<typeOfBike, unsigned int>> getStock() const;
	vector <typeOfBike> getTypesForSale() const;


	// SETTERS
	void changeReputation(int value);
	void changeStock(unsigned int type, unsigned int numberOfBikes);
	void reStock(unsigned int type);



	// OTHERS
	bool operator<(const BikeStore &b1) const;


};

#endif /* BIKESTORE_H_ */
