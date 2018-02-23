#include "BasicUsr.h"
#include "utilities.h"

// Sets the initial value for the last attributed ID to a basic user
unsigned int BasicUsr::lastId = 0;

/**
 * @param startPlace - the place where the BasicUsr begins its ride
 * @param type - the type of bike requested
 * @param beginTime - the Time at which the BasicUsr begins its ride
 *
 * \brief Creates a Basic User. Its created whenever its a user that is not Premium, so it always has a bike, a start place and a temporary ID.
 *
 * @return BasicUsr
 */
BasicUsr::BasicUsr(Place *startPlace, typeOfBike type, Time beginTime) : User(){


	int numBikes = startPlace->getNumBikes(), option;	// auxiliar to the number of bikes in the Place in question
														// option for menu
	int typeExists = -1;		// If the type exists in the place the value is the index of the bike in the place. Else, it's 0


		for (int i = 0; i < numBikes; i++){							// goes through the bikes available at that place
			if (startPlace->getBikeInVec(i)->getType() == type){ // check if favorite type is available
				typeExists = i;
				break;
			}
		}

		if(typeExists != -1){					// check if requested type is available
			startPlace->getBikeInVec(typeExists)->setInitialTime(beginTime);			// set initial time of usage
			this->setStartPlace(startPlace);								// sets the User's start place
			this->setBike(startPlace->getBikeInVec(typeExists));						// sets the User's bike
			startPlace->getBikeInVec(typeExists)->setAvailability(false);			// sets the availability of the bike
			this->tempID=getTempIdToSet();									// sets the Id
			startPlace->removeBike(typeExists);										// removes the bike from the place
		}

		else{
			cout << " Type of bike not available. Would you like to take another one?" << endl;
			cout << "0 - Cancel" << endl;
			cout << "1 - Take another type of bike" << endl;

			option = utilities::getUnsignedIntInput(0, 2, "Invalid Input, please choose option 1 or 0 to Quit");

			switch(option){
				case 0:
					throw utilities::CancelUserRequest();
				case 1:
					startPlace->getBikeInVec(0);								// assigns the first available bike in the place
					startPlace->getBikeInVec(0)->setInitialTime(beginTime);		// set initial time of usage
					this->setStartPlace(startPlace);							// sets the User's start place
					this->setBike(startPlace->getBikeInVec(0));					// sets the User's bike
					startPlace->getBikeInVec(0)->setAvailability(false);			// sets the availability of the bike
					this->tempID=getTempIdToSet();								// sets the Id
					startPlace->removeBike(0);									// removes the bike from the place
					break;
			}


		}
}

/**
 * @param startPlace - the place where the BasicUsr begins its ride
 * @param type - the type of bike requested
 * @param beginTime - the Time at which the BasicUsr begins its ride
 * @param fromFile - specifies if the BasicUsr is being directly added through a file reading
 *
 * \brief Creates a Basic User. Its created whenever its a user that is not Premium, so it always has a bike, a start place and a temporary ID.
 *
 * @return BasicUsr
 */
BasicUsr::BasicUsr(unsigned int tempID, Place *startPlace, typeOfBike type, Time beginTime, bool fromFile) : User(){

    if(!fromFile) {
        BasicUsr(startPlace, type, beginTime);
    } else {
        this->setStartPlace(startPlace);						// sets the User's start place
        this->tempID=tempID;									// sets the Id

    }





}


BasicUsr::~BasicUsr() {}

// Getters

/**
 * @param None
 *
 * \brief Returns in which number the Temporary IDs go, so no BasicUsr has an equal ID number.
 *
 * @return tempIds
 */
int BasicUsr::getTempIdToSet(){
	lastId++;
	return lastId;
}

/**
 * @brief Returns the User 's ID
 *
 * @param None
 *
 * @return ID
 */
const unsigned int BasicUsr::getID() const{
	return tempID;
}

// User methods

/**
 * @param amountOfMinutes - the amount of minutes the User used the Bike
 *
 * \brief Calculates the amount of money that must be added to the User's account
 *
* @return amount calculated
 */
float BasicUsr::calcPayment(int amountOfMinutes){
	float amountPerMinute = 0.06, amountToAddToAccount;

	amountToAddToAccount = amountPerMinute*amountOfMinutes;

	amount += amountToAddToAccount;

	return amountToAddToAccount;
}

/**
 * @param None
 *
 * \brief Calculates the amount of money that the User must pay at the end of the month
 *
 * @return amount - Amount to pay
 */
float BasicUsr::getAmountToPay(){
	return amount;
}

/**
 * @brief Returns the User 's ID
 *
 * @param None
 *
 * @return ID
 */
const unsigned int BasicUsr::getUserID(){
	return this->tempID;
}

/**
 * @brief Returns the User 's type. Only to be used in case the User wants to search for nearest Places with bikes
 *
 * @param None
 *
 * @return type
 */
typeOfBike BasicUsr::getType() const{
	return type;
}


/**
 * @brief Returns if the User is PremiumUsr or not
 *
 * @param None
 *
 * @return isPremium
 */
bool BasicUsr::isPremium(){
	return false;
}

/**
 * \brief Displays a Basic User information.
 *
 * @param None
 *
 * @return None
 */
void BasicUsr::displayUser () const{
	cout << "Temporary ID: " << this->tempID << '\n';
	cout << "Using bike since ";
	User::getBike()->getInitialTime().displayTime();
}


/**
 * \brief Sets the end Time in the Bike, sets the availability to available, puts the bike in the Place where it was left.
 * Removes the bike from the User, resets the start place from the User and adds the price of the trip to the account
 *
 * @param endPlace - the Place where the User ends its trip
 * @param endTime  - the Time at which the User ends its trip
 *
 *
 * @return None
 */
void BasicUsr::returnBike(Place* endPlace, Time endTime){

	Time startTime = getBike()->getInitialTime();
	int amountOfTime =  (endTime - startTime).getTotalMinutes(); //The amount of time that the bike was used

	getBike()->setInitialTime(endTime); //sets the end Time
	getBike()->setAvailability(true);	//sets the availability to available
	endPlace->addBike(getBike());		//puts the bike in the Place where it was left

	setBike(NULL);						//removes the bike from the User
	setStartPlace(NULL);				//resets the start place from the User


	cout << "\nBike returned with success!\n";

	showReceipt(startTime, endTime);

}

bool BasicUsr::writeUserInfo(ostream & out_stream) const {

    out_stream << "." << tempID << endl;
    out_stream << getBike()->getInitialTime().getTotalMinutes() << endl;
    out_stream << getStartPlace()->getID() << endl;
    out_stream << getBike()->getID();

    return true;

}

void BasicUsr::showReceipt(Time startTime, Time endTime) {
    cout << endl << endl << "--RECEIPT--" << endl << endl;


    cout << "Start: " << startTime << endl;
    cout << "End: " << endTime << endl;

    cout << "TOTAL: " << calcPayment((endTime-startTime).getTotalMinutes()) << "eur." << endl;
}













