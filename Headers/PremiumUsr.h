#ifndef PREMIUMUSR_H_
#define PREMIUMUSR_H_

#include <iostream>
#include <vector>
#include <string>

#include "User.h"
#include "Place.h"
#include "Bike.h"

using namespace std;


class PremiumUsr : public User{
private:
	const string name, email, adress, password;
	const unsigned int ID, phone, NIF;
	const typeOfBike favouriteType;
	float amount;
	static unsigned int lastUsedId;		/**< Holds the value for the last attributed ID to a basic user*/
	bool isUsingABike;

public:
	// Constructor and destructor
	PremiumUsr();
	PremiumUsr(string name, string email, string adress, unsigned int ID, unsigned int phone, unsigned int NIF, typeOfBike type, string password, bool isUsing, float currentAmount);
	PremiumUsr(string name, string email, string adress, unsigned int phone, unsigned int NIF, typeOfBike type, string password);
	virtual ~PremiumUsr();

	// GETTERS
	const string getName() const;
	const string getEmail() const;
	const string getAdress() const;
	const unsigned int getID() const;
	const unsigned int getPhone() const;
	const unsigned int getNIF() const;
	const typeOfBike getFavouriteType() const;
	const string getFavouriteTypeInString() const;
	const string getPassword() const;
	bool getIsUsing() const;

	// methods from User
	float calcPayment(int amountOfMinutes);
	float getAmountToPay();
	void displayUser () const;
	void returnBike(Place* endPlace, Time endTime);
	bool isPremium();
	virtual const unsigned int getUserID();
	void showReceipt(Time startTime, Time endTime);

	//OTHERS
	int requestBike(Time now, Place *placeBegin);
	void setIsUsingBike(bool isUsing);
	bool writeUserInfo(ostream & out_stream) const { return false; };
	void payDebt();

};

#endif /* PREMIUMUSR_H_ */
