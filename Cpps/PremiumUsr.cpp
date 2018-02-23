#include "PremiumUsr.h"
#include "utilities.h"


unsigned int PremiumUsr::lastUsedId = 0;

/**
 * @param name - the name of the PremiumUsr
 * @param email - the email address of the PremiumUSr
 * @param address - the address of the PremiumUsr
 * @param ID - the ID of the PremiumUsr
 * @param phone - the phone number of the PremiumUsr
 * @param NIF - the NIF of the PremiumUsr
 * @param favouriteType - the favorite type of Bike of the PremiumUsr
 *
 * \brief Creates a Premium User. To be used when reading the users from the file.
 *
 * @return None
 */
PremiumUsr::PremiumUsr(string name, string email, string adress, unsigned int ID, unsigned int phone, unsigned int NIF, typeOfBike favouriteType, string password, bool isUsing, float currentAmount): User (), name(name), email(email), adress(adress), ID(ID), phone(phone), NIF(NIF), favouriteType(favouriteType), password(password){
	lastUsedId = ID + 1;
	isUsingABike = isUsing;
	amount = currentAmount;
}

/**
 * @param name - the name of the PremiumUsr
 * @param email - the email address of the PremiumUSr
 * @param address - the address of the PremiumUsr
 * @param phone - the phone number of the PremiumUsr
 * @param NIF - the NIF of the PremiumUsr
 * @param favouriteType - the favorite type of Bike of the PremiumUsr
 *
 * \brief Creates a Premium User. To be used when creating users during the execution, IDs are set sequentially through Users.
 * The amount is started at 7euros, the monthly subscription for a PremiumUsr
 *
 * @return None
 */
PremiumUsr::PremiumUsr(string name, string email, string adress, unsigned int phone, unsigned int NIF, typeOfBike type, string password): User(), name(name), email(email), adress(adress), phone(phone), NIF(NIF), favouriteType(type), ID(lastUsedId), password(password) {
	lastUsedId++;
	isUsingABike = false;
	amount = 7;
}

/**
 * @param None
 *
 * \brief Creates an empty Premium User. (the values are initialized because they're constants)
 *
 * @return None
 */
PremiumUsr::PremiumUsr() : name(""), adress(""), ID(1), phone(1), NIF(1), favouriteType(typeOfBike::child) {}

PremiumUsr::~PremiumUsr() {
	// TODO Auto-generated destructor stub
}



// GETTERS

/**
 * @param None
 *
 * \brief Returns a string with the User's name.
 *
 * @return Name
 */
const string PremiumUsr::getName() const{
	return this->name;
}

/**
 * @param None
 *
 * \brief Returns the Premium User's email.
 *
 * @return Email
 */
const string PremiumUsr::getEmail() const{
	return this->email;
}


/**
 * @param None
 *
 * \brief Returns the Premium User's password.
 *
 * @return Password
 */
const string PremiumUsr::getPassword() const{
	return this->password;
}


/**
 * @param None
 *
 * \brief Returns the Premium User's adress.
 *
 * @return Adress
 */
const string PremiumUsr::getAdress() const{
	return this->adress;
}

/**
 * @param None
 *
 * \brief Returns the Premium User's ID.
 *
 * @return ID
 */
const unsigned int PremiumUsr::getID() const{
	return this->ID;
}

/**
 * @param None
 *
 * \brief Returns the Premium User's phone number.
 *
 * @return Phone
 */
const unsigned int PremiumUsr::getPhone() const{
	return this->phone;
}

/**
 * @param None
 *
 * \brief Returns the Premium User's NIF.
 *
 * @return NIF
 */
const unsigned int PremiumUsr::getNIF() const{
	return this->NIF;
}

/**
 * @param None
 *
 * \brief Returns the Premium User's favourite type(in a string).
 *
 * @return favouriteType(string)
 */
const string PremiumUsr::getFavouriteTypeInString() const{

	if(favouriteType == urban)
		return "urban";
	if(favouriteType == urbanSimple)
		return "urbanSimple";
	if(favouriteType == race)
		return "race";
	if(favouriteType == child)
		return "child";


}

/**
 *  @param None
 *
 *  \brief Returns the Premium User's favourite type.
 *
 *  @return favotiteType
 */
const typeOfBike PremiumUsr::getFavouriteType() const{
	return favouriteType;
}

/**
 *  @param None
 *
 *  \brief Returns the Premium User's status (if it's using a Bike or not)
 *
 *  @return isUsingABike
 */
bool PremiumUsr::getIsUsing() const{
	return isUsingABike;
}


// methods from user

/**
 * @param amountOfMinutes - the amount of minutes the User used the Bike
 *
 * \brief Calculates the amount of money that must be added to the User's account
 *
 * @return amount calculated
 */
float PremiumUsr::calcPayment(int amountOfMinutes){

	float amountPerMinute = 0.03, amountToAddToAccount;

	amountToAddToAccount = amountPerMinute*amountOfMinutes;

	amount += amountToAddToAccount;

	return amountToAddToAccount;
}

/**
 * @param None
 *
 * \brief Returns the PremiumUsr's ID
 *
 * @return ID
 */
const unsigned int PremiumUsr::getUserID(){
	return this->ID;
}


/**
 * @param None
 *
 * \brief Returns the amount the PremiumUsr must pay
 *
 * @return amount - Amount to pay
 */
float PremiumUsr::getAmountToPay(){
	return amount;
}

/**
 * @param None
 *
 * \brief Displays a Premium User information.
 *
 * @return None
 */
void PremiumUsr::displayUser () const{
	cout << "\nName: " << this->getName() << endl;
	cout << "Email adress: " << this->getEmail() << endl;
	cout << "Adress: " << this->getAdress() << endl;
	cout << "Client ID: " << getID() << endl;
	cout << "Phone: " << this->getPhone() << endl;
	cout << "NIF: " << this->getNIF() << endl;
	cout << "Favourite type of bike: " ;

	if (this->favouriteType == urban){
		cout << "urban\n";
	}

	if (this->favouriteType == urbanSimple){
		cout << "urbanSimple\n";
	}

	if (this->favouriteType  == race){
		cout << "race\n";
	}

	if (this->favouriteType == child){
		cout << "child\n";
	}

	cout << "Rented since: ";
	this->getBike()->getInitialTime().displayTime();
}

/**
 * @param isUsing - a bool
 *
 * @brief Sets if the PremiumUsr isusing a Bike or not
 *
 * @return None
 */
void PremiumUsr::setIsUsingBike(bool isUsing){
	isUsingABike = isUsing;
}

/**
 * @param None
 *
 * @brief Returns if the User is PremiumUsr or not
 *
 * @return isPremium
 */
bool PremiumUsr::isPremium(){
	return true;
}

/**
 * @param now - Time at the moment of the request
 * @param type - The type of bike the User requested
 * @param placeBegin - The Place where the User is
 *
 * @brief Requests a Bike for the User and adds the User to the users at the moment vector in company.
 *
 * @Return Returns true or false whether it was able to request a Bike or not
 */
int PremiumUsr::requestBike(Time now, Place *placeBegin){


	int numBikes = placeBegin->getNumBikes(), option;					// auxiliar to the number of bikes in the Place in question
																		// option for menu
	int typeExists = -1;		// If the type exists in the place the value is the index of the bike in the place. Else, it's 0


		for (int i = 0; i < numBikes; i++){							// goes through the bikes available at that place
			if (placeBegin->getBikeInVec(i)->getType() == getFavouriteType()){ // check if favorite type is available
				typeExists = i;
				break;
			}
		}

			if(typeExists != -1){												// if favorite type is available
				placeBegin->getBikeInVec(typeExists)->setInitialTime(now);		// set initial time of usage
				this->setStartPlace(placeBegin);								// sets the User's start place
				this->setBike(placeBegin->getBikeInVec(typeExists));			// sets the User's bike
				placeBegin->getBikeInVec(typeExists)->setAvailability(false);	// sets the availability of the bike
				placeBegin->removeBike(typeExists);								// removes the bike from the place
				setIsUsingBike(true);											// set that the User is now using a bike

				return 0;														// Success!
			}


			else{
				cout << "Your favorite type of bike is not available. Would you like to take another one or check another place?" << endl << endl;
				cout << " 0 - Cancel\n 1 - Take an available type of bike\n 2 - Get closest place with bikes of your favorite type\n";
				option = utilities::getUnsignedIntInput(0, 3, "Invalid option, please try again.");
				}

				switch(option){
				case 0:
					throw utilities::CancelUserRequest();
					break;

				case 1:
					placeBegin->getBikeInVec(0)->setInitialTime(now);			// set initial time of usage
					this->setStartPlace(placeBegin);							// sets the User's start place
					this->setBike(placeBegin->getBikeInVec(0));					// sets the User's bike
					placeBegin->getBikeInVec(0)->setAvailability(false);		// sets the availability of the bike
					placeBegin->removeBike(0);									// removes the bike from the place
					setIsUsingBike(true);										// set that the User is now using a bike
					return 0;
					break;

				case 2:
					return 1;	// Call Get Nearest Places!
					break;
				}

}


/**
 * @param endPlace - the Place where the User ends its trip
 * @param endTime  - the Time at which the User ends its trip
 * \brief Sets the end Time in the Bike, sets the availability to available, puts the bike in the Place where it was left.
 * Removes the bike from the User, resets the start place from the User and adds the price of the trip to the account
 *
 * @return None
 */
void PremiumUsr::returnBike(Place* endPlace, Time endTime){

    Time startTime = getBike()->getInitialTime();
	int amountOfTime =  (endTime - startTime).getTotalMinutes(); //The amount of time that the bike was used

	getBike()->setAvailability(true);	//sets the availability to available

	endPlace->addBike(getBike());		//puts the bike in the Place where it was left

	setIsUsingBike(false);				// set that the User is now NOT using a bike anymore

	setBike(NULL);						//removes the bike from the User
	setStartPlace(NULL);				//resets the start place from the User


	showReceipt(startTime, endTime);

	cout << "\nBike returned with success!\n";
}

/**
 * @param startTime - the begining time of usage
 * @param endTime - the end time of usage
 *
 * @brief Shows the payment receipt for the usage of the Bike
 *
 * @return None
 */
void PremiumUsr::showReceipt(Time startTime, Time endTime) {
    cout << endl << endl << "--RECEIPT--" << endl << endl;

    cout << name <<endl;
    cout << NIF << endl;

    cout << "Start: " << startTime << endl;
    cout << "End: " << endTime << endl;

    Time finalTime = endTime-startTime;

    cout << "TOTAL MINUTES: " << finalTime.getTotalMinutes() << endl;
    cout << "TOTAL: " << calcPayment(finalTime.getTotalMinutes()) << "€" << endl;
}

/**
 * @param Resets the debt of the PremiumUsr to 0 (Pays the dept)
 */
void PremiumUsr::payDebt() {

    if(amount == 0) {
        cout << "You have no debt pending!" << endl;
    } else {

        cout << "Current Debt: " << amount << endl;
        cout << endl << endl << "Press ENTER to pay, or '0' to cancel" << endl;

        int character;
        while(character = getchar()){
            if(character == 10){		// if ENTER is pressed
                amount = 0;
                break;
            } else if (character == '0') {
                throw utilities::CancelUserRequest();
            }
            else
                cin.ignore(1000, '\n');
        }



    }

}



