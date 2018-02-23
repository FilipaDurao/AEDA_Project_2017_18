#include <iostream>
#include "UI.h"
#include "utilities.h"

using namespace std;

//COMPANY MENU

/**
 * @param c - A Company Object
 *
 * @brief Shows menu to change Company's Settings
 *
 * @return void
 */
void menuCompanySettings(Company & c) {

    try {
        createMenu( " 1.COMPANY ", {
			{ "Display Info", displayCompanyInfo },
			{ "Display Users At The Moment", displayUsersAtTheMoment },
			{ "Display Premium Users", displayPremiums},
			{ "Add Place", addNewPlace},
			{ "Add Bike", addNewBike},
			{ "Send Bike to Scrapyard", sendToScrapyard},
			{ "Display Broken/Scrapped Bikes", displayBrokenBikes},
			{ "Scrape Bike", scrapeBike},
			{ "Remove Bike from Scrapyard", removeFromScrapyard},
			{ "Reallocate Bikes (Distribute bikes per place evenly)", reallocateCompanyBikes},
		}, c);
    }
    catch(utilities::CancelUserRequest& cancel) {}
    catch(utilities::NoBrokenBikes& n) {}
    catch(utilities::AllBikesScrapped& n) {}


    closeFunction();
}

/**
 * @param c - a reference to Company
 *
 * @brief It's called from the Company menu. Calls displayCompanyInfo() from Company.
 *
 * @return void
 */
void displayCompanyInfo(Company & c){
	c.displayCompanyInfo();
	closeFunction();
}

/**
 * @param c - a reference to Company
 *
 * @brief It's called from the Company menu. Calls displayUsersAtTheMoment() from Company.
 *
 * @return void
 */
void displayUsersAtTheMoment(Company & c){
	c.displayUsersAtTheMoment();
	closeFunction();
}

/**
 * @param c - a reference to Company
 *
 * @brief It's called from the Company menu. Calls displayPremiumUsers() from Company.
 *
 * @return void
 */
void displayPremiums(Company & c){
	c.displayPremiumUsers();
	closeFunction();
}

/**
 * @param c - a reference to Company
 *
 * @brief It's called from the Company menu. Calls realocateBikes() from Company and then displays the current distribution of bikes.
 *
 * @return void
 */
void reallocateCompanyBikes(Company & c){
	c.realocateBikes();

	cout << "Reallocated Bikes. The current bike distribution is the following: " << endl;

	c.displayPlacesAndBikes();

	closeFunction();
}


/**
 * @param c - a reference to Company
 *
 * @brief It's called from the Company menu. Calls addNewPlace() from Company with the details given by user.
 *
 * @return void
 */
void addNewPlace(Company & c) {
    string name;
    unsigned int posX, posY, ID;

    //getName
    cout << "Insert the new place's name: " << endl;
    getline(cin,name);

    //getX
    cout << "Insert the new place's X coordinate:" << endl;
    posX = utilities::getUnsignedIntInput("Invalid number. Try Again!");

    //getY
    cout << "Insert the new place's Y coordinate:" << endl;
    posY = utilities::getUnsignedIntInput("Invalid number. Try Again!");

    //getID
    ID = c.getCurrentMaxPlaceID() + 1;

    Place* placeToAdd = new Place(name,posX, posY, ID);

    c.addNewPlace(placeToAdd);

	closeFunction();
}

/**
 * @param c - a reference to Company
 *
 * @brief It's called from the Company menu. Calls addNewPlace() from Company with the details given by user.
 *
 * @return void
 */
void addNewBike(Company & c) {
    unsigned int bikeID, placeID, bikeTypeOption;
    Bike* bikeToAdd;

    //getName
    cout << "Choose the bike type: " << endl;

    cout << "0 - Cancel" << endl << endl;

    c.displayBikes();

    bikeTypeOption = utilities::getUnsignedIntInput(0, 5, "Invalid input. Try again.");

    //getID
    bikeID = c.getCurrentMaxBikeID() + 1;

    switch(bikeTypeOption) {
    case 0:
        throw utilities::CancelUserRequest();
        break;
    case 1:
        bikeToAdd = new Bike(urban, bikeID);
        break;
    case 2:
        bikeToAdd = new Bike(urbanSimple, bikeID);
        break;
    case 3:
        bikeToAdd = new Bike(race, bikeID);
        break;
    case 4:
        bikeToAdd = new Bike(child, bikeID);
        break;
    }


    c.addNewBike(bikeToAdd);

    cout << "Choose the Place to place the bike: " << endl;

    cout << "0 - Cancel" << endl << endl;
    c.displayPlaces();



    placeID = utilities::getUnsignedIntInput(0, c.getPlaces().size() + 1, "Invalid Input, try again.");

    if(placeID == 0) {
        throw utilities::CancelUserRequest();
    }

    Place* chosenPlace;

    vector<Place*> places = c.getPlaces();

    for(int i = 0; i < places.size(); i++) {
        if(places.at(i)->getID() == placeID){
            chosenPlace = places.at(i);
            break;
        }
    }

    chosenPlace->addBike(bikeToAdd);

	closeFunction();
}


/**
 * @param c - a reference to Company
 *
 * @brief It's called from the Company menu. Calls sendToScrapyard() from Company.
 *
 * @return void
 */
void sendToScrapyard(Company & c) {

    c.displayAllBikes();

    Bike* bikeToSend = nullptr;

    while(bikeToSend == nullptr) {
        cout << "Choose the ID of the bike to send to scrapyard (0 to cancel)" << endl;
        unsigned int id = utilities::getUnsignedIntInput("Invalid ID, try again.");
        if (id == 0) {
            return;
        }

        bikeToSend = c.getBikeByID(id);

        if(bikeToSend != nullptr) break;
        else cout << "That bike does not exist!" << endl << endl;
    }

    c.sendToScrapyard(bikeToSend);

	closeFunction();
}

/**
 * @param c - a reference to Company
 *
 * @brief It's called from the Company menu. Calls removeFromScrapyard() from Company.
 *
 * @return void
 */
void removeFromScrapyard(Company & c) {

    c.displayBrokenBikes();

    Bike* bikeToRemove = nullptr;

    while(bikeToRemove == nullptr) {
        cout << "Choose the ID of the bike to remove from scrapyard (0 to cancel)" << endl;
        unsigned int id = utilities::getUnsignedIntInput("Invalid ID, try again.");
        if (id == 0) {
            return;
        }

        bikeToRemove = c.getBrokenBikeByID(id);

        if(bikeToRemove != nullptr) break;
        else cout << "That bike does not exist!" << endl << endl;
    }

    c.removeFromScrapyard(bikeToRemove);

	closeFunction();
}

/**
 * @param c - a reference to Company
 *
 * @brief It's called from the Company menu. Calls displayBrokenBikes() from Company.
 *
 * @return void
 */
void displayBrokenBikes(Company & c) {

    try {
        c.displayBrokenBikes();
    } catch(utilities::NoBrokenBikes& n) {
        cout << "There are no broken bikes to scrap!" << endl;
        throw;
    }

	closeFunction();
}

/**
 * @param c - a reference to Company
 *
 * @brief It's called from the Company menu. Calls displayBrokenBikes() from Company.
 *
 * @return void
 */
void scrapeBike(Company & c) {

    try {
        c.displayBrokenBikes();
    } catch(utilities::NoBrokenBikes& n) {
        cout << "There are no broken bikes to scrap!" << endl;
        throw;
    } catch(utilities::AllBikesScrapped& n) {
        cout << "All bikes are already scrapped!" << endl;
        throw;
    }



    Bike* bikeToScrape = nullptr;

    while(bikeToScrape == nullptr) {
        cout << "Select a bike to scrape. (Enter the bike's id - 0 to cancel)" << endl;
        unsigned int id = utilities::getUnsignedIntInput("Invalid ID, try again.");
        if (id == 0) {
            return;
        }

        bikeToScrape = c.getBrokenBikeByID(id);

        if(bikeToScrape != nullptr) {
            if(bikeToScrape->getScrappingDate().getTotalMinutes() == 0) break; // not scrapped yet
            else {
                cout << "That bike was already scrapped on ";
                bikeToScrape->getScrappingDate().displayTime();
                bikeToScrape = nullptr;
            }
        }
        else cout << "That bike does not exist!" << endl << endl;
    }


    Time currentDate = getCurrentTimeInput();
    c.scrapeBike(bikeToScrape, currentDate);

    c.displayBrokenBikes();


	closeFunction();
}



//BASIC USER MENU

/**
 * @param c - a reference to Company
 *
 * @brief Shows menu for BasicUsr service usage
 *
 * @return void
 */
void menuEnterBasicUsr(Company & c) {


	createMenu( " 3.BASIC USERS ", {
			{ "Request Bike", basicRequestBike },
			{ "Return Bike", basicReturnBike },
		}, c);

    closeFunction();
}

/**
 * @param c - a reference to Company
 *
 * @brief It's called from the BasicUsr menu. Calls requestBike() from BasicUsr.
 *
 * @return void
 */
void basicRequestBike(Company & c){

	 try {
		BasicUsr* basic = c.createBasicUsr();
		vector<Place *> places;

		if(basic->getBike() == NULL){
			places = c.getNearestPlacesWithBike(basic->getType(), basic->getStartPlace()->getPos());

			for(unsigned int i = 0; i < places.size(); i++){
				cout << " " << places.at(i)->getName();
			}

			closeFunction();
		}

		else
			c.addBasicToUsersVec(basic);
	  }

	  catch (utilities::CancelUserRequest& cancel) {}
	  catch (utilities::NoBikesAvailable & noBikes) {
        cout << "There are no bikes available here." << endl;
	  }

	  closeFunction();
}

/**
 * @param c - a reference to Company
 *
 * @brief It's called from the BasicUsr menu. Calls returnBike() from BasicUsr.
 *
 * @return void
 */
void basicReturnBike(Company & c){

	string basicID = "";

	cout << "\nPlease enter your ID (0 to Cancel): ";

    bool invalidID = true;
    unsigned int ID;
    BasicUsr* basic;
    try{
        while(invalidID) {

            ID = utilities::getUnsignedIntInput("Invalid Number, try again.");

            //If the user types "0", the function should exit
            if(ID == 0) throw utilities::CancelUserRequest();
            basic = c.getBasicUserAtTheMomentByID(ID);


            if(basic == nullptr) {
                cout << "Such ID (" << ID << ") does not exist in the BasicUsers Database!" << endl << "Try Again." << endl;
            } else {
                invalidID = false;
            }
        }


        // Get the place where the User is
        int placeOption;
        bool validPlace = false;
        Place *newPlace;

        while(!validPlace){

            // Get the place where the User is
            c.displayPlaces();
            cout << "\n\nIn which renting point are you? (Type in the correspondent number) ";
            placeOption = utilities::getUnsignedIntInput(1, c.getPlaces().size() + 1, "Invalid Place. Please try again.");

            // Find the given place in the places vector
            for(unsigned int i = 0; i < c.getPlaces().size(); i++){
                if(c.getPlaces().at(i)->getID() == placeOption){
                    newPlace = c.getPlaces().at(i);
                    validPlace=true;
                    break;
                }
            }
        }

        //Time nowTime = Time(18, 00);
        //To be able to test different values, the Current Time will be asked for input, otherwise, the time must be read from the system
        Time nowTime = getCurrentTimeInput();

        basic->returnBike(newPlace, nowTime);
        c.removeBasicFromUsersVec(basic);
    }
    catch (utilities::CancelUserRequest& cancel) {}

    closeFunction();
}



//PREMIUM USER MENU

/**
 * @param c - a reference to Company
 *
 * @brief Shows menu for PremiumUsr service usage
 *
 * @return void
 */
void menuPremiumUsr(Company & c){

	createMenu( " 2.PREMIUM USERS ", {
				{ "Log In", menuLoginPremiumUsr },
				{ "New Register", newPremiumUsr },
			}, c);



}

/**
 * @param c - a reference to Company
 *
 * @brief It's called from the PremiumUsr menu. Creates a new PremiumUsr
 *
 * @return void
 */
void newPremiumUsr(Company & c){

	string name, email, adress, phone, NIF, type, password = "a", confPassword = "b";
	bool success;


	while (name == ""){
		cout << "\nIntroduce your name: ";
		getline(cin, name);						//get the name

		if (name.size() < 2)					//verify if its logical
			name = "";
	}

	while (email == ""){
		cout << "\nIntroduce your email: ";
		getline(cin, email);					//get the email

		if ( (email.find('@') == string::npos) || ((email.find(".com") == string::npos) && (email.find(".pt") == string::npos))){
			//verify if its logical
			email = "";
		}
	}

	while (adress == ""){
		cout << "\nIntroduce your adress: ";
		getline(cin, adress);					//get the adress

		if (adress.size() < 5){
			//verify if its logical
			adress == "";
		}
	}

	while (true){
		cout << "\nIntroduce your phone number: ";
		getline(cin, phone);

		if (isNumber(phone)){
			if (phone.size() < 9){
				phone = "";
			}

			else
				break;
		}
	}

	while(NIF == ""){
		cout << "\nIntroduce your NIF: ";
		getline(cin, NIF);

		if (isNumber(NIF)){
			if (NIF.size() < 9){
				NIF = "";
			}
			else
				break;
		}
	}

	while(true){
		cout << "\nIntroduce your pre-defined type of bike: ";
		getline(cin, type);

		if (type == "urban" || type == "urbanSimple" || type == "child" || type == "race")
			break;
	}

	while (password != confPassword){

		cout << "\nIntroduce your password: ";
		getline(cin, password);

		cout << "\nPlease confirm your password: ";
		getline(cin, confPassword);

		if(password != confPassword){
			cout << "\nYour confirmation password does not match your initial password, please try again.";
			getchar();
		}

	}

	success = c.createPremiumUsr(name, email, adress, phone, NIF, type, password);

	if (success == true){
		cout << "\nUser account created with success!\n";
		c.saveUsers();
	}
	else
		cout << "\nUser account creation failed.\n";


}


/* PREMIUM USER LOGIN UI */

unsigned int currentLoginID = -1;	/**< Holds the value of the id of the premium user logged in / -1 if no login */

/**
 * @brief Exception to be thrown when a login fails, due to exceeding the no. of tries
 */
class LoginFail{
public:
    LoginFail(){};
};

/**
 * @brief Exception to be thrown when a user wants to log out
 */
class LogOut{
public:
    LogOut(){};
};


/**
 * @param c - a reference to Company
 *
 * @brief Shows menu for PremiUmusr login, if a user has already logged in, the User's page is shown
 *
 * @return void
 */
void menuLoginPremiumUsr(Company & c) {

    //Points at the logged user, initially it will have a wrong value, but the premiumUserLogin function sets this ptr to the user's ptr
    PremiumUsr* user = new PremiumUsr();

    try{
        //UI that prompts the user login. If correct login, the user pointer will point to the logged user, otherwise, it will throw a LoginFailed exception.
    	if(currentLoginID != -1) {
			//A User is already logged in.
			menuUserArea(c);
		} else {
			premiumUserLogin(user, c);
		}
        closeFunction();
    }

    catch(utilities::CancelUserRequest& cancel) {
        closeFunction();
    }

    catch(LoginFail& failedLogin) {
        closeFunction();
    }

}






/**
 * @param c - a reference to Company
 *
 * @brief Asks for email and password from user to log in as premium user and return the PremiumUser on success or throw LoginFail Exception.
 *
 * @return PremiumUsr*
 */
void premiumUserLogin( PremiumUsr*& user, Company & c) {
    string email, password;
    bool invalidEmail = true;

    cout << endl << "LOGIN" << endl << endl;

    while(invalidEmail){
        //Getting e-mail (catch exception if non existent email or if user writes "0" to cancel login)
        try {
            cout << "E-mail: ";
            getline(cin, email);

            //Write "0" to cancel
            if (email == "0") {
                invalidEmail= false;
                throw utilities::CancelUserRequest();
            }

            //Verify the email existence and if so, return the user, otherwise, return UnexistentEmail Exception
            c.getPremiumUsrByEmail(user, email);
            invalidEmail = false;
        }

        catch(UnexistentEmail& noEmail){
            cout << "There's no such e-mail (" + noEmail.getEmail() + ") in the database. Try Again." << endl << endl;
        }
    }


    //value for the max password tries the user gets
    const int maxPasswordTries = 5;
    int remainingTries, invalidPasswordCount = 0;

    while(invalidPasswordCount < maxPasswordTries) {
        //Getting password (catch exception if email and password don't match)

        cout << "Password: ";
        cin >> password;
        bool isCorrectPassword = c.verifyPassword(user, password);

        if(isCorrectPassword) {
            //if the password is valid, we need to break the loop
            break;
        } else {
            invalidPasswordCount++;
            remainingTries = maxPasswordTries - invalidPasswordCount;
            cout << "The password does not match the email (" + email + "). Remaining Tries: " + to_string(remainingTries) << endl;
        }
    }


    //checking if the loop has ended because the no. of tries exceeded
    if(invalidPasswordCount == maxPasswordTries) {
        cout << "Maximum number of wrong tries exceeded, the login is blocked." << endl;
        throw LoginFail();
        closeFunction();
    }

    else{
    	currentLoginID = user->getID();

    menuUserArea(c);
    }

}



/**
 * @param c - a reference to Company
 *
 * @brief Shows menu with logged Premium User's options
 *
 * @return void
 */
void menuUserArea(Company & c) {

	PremiumUsr* currentPremium = c.getPremiumUserByID(currentLoginID);
	string name = currentPremium->getName();

	try{

		createMenu( name +  " -- USER'S AREA ", {
		  { "Request Bike", premiumRequestBike },
		  { "Return Bike", premiumReturnBike },
		  { "Get Amount to Pay", payDebt},
		  { "Log Out", menuLogoutPremiumUsr }
		 }, c);

		}

		catch (LogOut & logout) {
			closeFunction(false);
		}

		catch(utilities::CancelUserRequest& cancel){
			closeFunction(false);
		}

}


/**
 * @param c - a reference to Company
 *
 * @brief Shows menu with logged Premium User's options
 *
 * @return void
 */
void menuLogoutPremiumUsr(Company & c) {

    cout << "Are you sure you want to Log Out? (Y/N)" << endl;
    string response;
    cin >> response;
    while(response != "y" && response != "Y" && response != "n" && response != "N") {
        cout << "Invalid input, please write 'Y' or 'N'!" << endl;
        cin >> response;
    }

    if (response == "Y" || response == "y") {
        currentLoginID = -1;
        throw LogOut();
    }

}

/**
 * @param c - a reference to Company
 *
 * @brief It's called from the PremiumUsr menu. Calls requestBike() from PremiumUsr.
 *
 * @return void
 */
void premiumRequestBike(Company & c){

	// Get who is the User requesting the bike
	PremiumUsr* currentPremium = c.getPremiumUserByID(currentLoginID);

	if(currentPremium->getIsUsing() == true){
		cout << "\n\nYou are already using a Bike!\n";		// The user is already using a Bike
		return;
	}

	string type = currentPremium->getFavouriteTypeInString();
	int placeOption;
	bool validPlace = false;
	Place *newPlace;

	while(!validPlace){

		cout << endl << endl << "0 - Cancel\n";
		// Get the place where the User is
		c.displayPlaces();
		cout << "\n\nIn which renting point are you?  (Type in the correspondent number)";
		placeOption = utilities::getUnsignedIntInput(0, c.getPlaces().size() + 1, "Invalid Place. Please try again.");

		if(placeOption == 0){
			throw utilities::CancelUserRequest();
		}

		// Find the given place in the places vector
		for(unsigned int i = 0; i < c.getPlaces().size(); i++){
			if(c.getPlaces().at(i)->getID() == placeOption){
				newPlace = c.getPlaces().at(i);
				validPlace=true;
				break;
			}
		}
	}


	//Time nowTime = Time(17, 30);
	//To be able to test different values, the Current Time will be asked for input, otherwise, the time must be read from the system
	Time nowTime = getCurrentTimeInput();

	vector<Place *> places;

	try{
		int success = currentPremium->requestBike(nowTime, newPlace);

		if (success == 0){
			c.addPremiumToUsersVec(currentPremium);

			cout << "\nBike rented with success!\n";

			closeFunction();
		}

		else if (success == 1){

			cout << endl;

			if(type == "urban"){
				places = c.getNearestPlacesWithBike(urban, newPlace->getPos());

				if(places.size() == 0){
					cout << "\nThere are no bikes of your favorite type available anywhere at the moment\n";
				}

				for(unsigned int k = 0; k < places.size(); k++){
					cout << " " << places.at(k)->getName() << endl;
				}

				closeFunction();
			}
			else if(type == "urbanSimple"){
				places = c.getNearestPlacesWithBike(urbanSimple, newPlace->getPos());

					if(places.size() == 0){
						cout << "\nThere are no bikes of that type available anywhere at the moment\n";
					}

					cout << endl;
					for(unsigned int k = 0; k < places.size(); k++){
						cout << " " << places.at(k)->getName() << endl;
					}

					closeFunction();
			}
			else if(type == "race"){
				places = c.getNearestPlacesWithBike(race, newPlace->getPos());

					if(places.size() == 0){
						cout << "\nThere are no bikes of that type available anywhere at the moment\n";
					}

					for(unsigned int k = 0; k < places.size(); k++){
						cout  << " " << places.at(k)->getName() << endl;
					}

					closeFunction();
			}
			else if(type == "child"){
				places = c.getNearestPlacesWithBike(child, newPlace->getPos());

					if(places.size() == 0){
						cout << "\nThere are no bikes of that type available anywhere at the moment\n";
					}

					for(unsigned int k = 0; k < places.size(); k++){
						cout << " "  << places.at(k)->getName() << endl;
					}

					closeFunction();
			}
		}
	}

	catch(utilities::CancelUserRequest & cancel) {
	      closeFunction();
	  }

}

/**
 * @param c - a reference to Company
 *
 * @brief It's called from the PremiumUsr menu. Calls returnBike() from PremiumUsr.
 *
 * @return void
 */
void premiumReturnBike (Company & c){

	// Get who is the User returning the bike
	PremiumUsr* currentPremium = c.getPremiumUserByID(currentLoginID);

	if(currentPremium->getIsUsing() == false){
		cout << "This User is not currently using a Bike!" << endl;
		closeFunction();
	}

	else{

		// Get the place where the User is
		int placeOption;
		bool validPlace = false;
		Place *newPlace;

		while(!validPlace){

			// Get the place where the User is
			c.displayPlaces();
			cout << "\n\nIn which renting point are you?  (Type in the correspondent number) ";
			placeOption = utilities::getUnsignedIntInput(1, c.getPlaces().size() + 1, "Invalid Place. Please try again.");

			// Find the given place in the places vector
			for(unsigned int i = 0; i < c.getPlaces().size(); i++){
				if(c.getPlaces().at(i)->getID() == placeOption){
					newPlace = c.getPlaces().at(i);
					validPlace=true;
					break;
				}
			}
		}

		//Time nowTime = Time(18, 0);
        //To be able to test different values, the Current Time will be asked for input, otherwise, the time must be read from the system
        Time nowTime = getCurrentTimeInput();

		currentPremium->returnBike(newPlace, nowTime);

		c.removePremiumFromUsersVec(currentPremium);
	}
}

/**
 * @param c - a reference to Company
 *
 * @brief It's called from the PremiumUsr menu. Calls getAmountToPay() from PremiumUsr.
 *
 * @return void
 */
void payDebt(Company &c){

	PremiumUsr* currentPremium = c.getPremiumUserByID(currentLoginID);

	try{
        currentPremium->payDebt();
	}
	catch (utilities::CancelUserRequest& cancel) {}


	closeFunction();
}


// BIKE STORE MENU

/**
 * @param c - a reference to Company
 *
 * @brief Shows menu with BikeStore options
 *
 * @return void
 */
void menuBikeStores(Company & c){

    try {
        createMenu( " 4.BIKE STORES ", {
			{ "Display Top 5", displayTopFiveStores },
			{ "Display All Stores", displayAllStores },
			{ "Display Stores With Given Type Available", displayStoresWithType },
			{ "Display Stores With Given Stock Available", displayStoresWithStock },
			{ "Buy Bikes From Best Store", buyBikesFromBest },
			{ "Buy Bikes From A Chosen Store", buyBikesFromStore },
			{ "Re-Stock stores", reStockStores},
		}, c);
    }
    catch(utilities::CancelUserRequest& cancel) {}


    closeFunction();
}

/**
 * @brief Displays on the screen the information about the top 5 best stores
 *
 * @param c - a reference to Company
 *
 * @return void
 */
void displayTopFiveStores(Company & c){

	priority_queue<BikeStore> aux = c.getStores();

	for(unsigned int i = 0; i < 5; i++){
		printBikeStore(aux.top());
		aux.pop();

		if(aux.size() == 0)
			break;
	}

	closeFunction();
}

/**
 * @brief Displays on the screen the information about all the stores
 *
 * @param c - a reference to Company
 *
 * @return void
 */
void displayAllStores(Company & c){

	priority_queue<BikeStore> aux = c.getStores();

	while(!aux.empty()){
		printBikeStore(aux.top());
		aux.pop();
	}

	closeFunction();
}

/**
 * @brief Displays on the screen the stores that sell a given type of Bike
 *
 * @param c - a reference to Company
 *
 * @return void
 */
void displayStoresWithType(Company & c){

	unsigned int input;
	string in;

	// Get the type that the buyer is interested in
	cout << endl << "What type of Bike are you interested in buying? " << endl;
	c.displayBikes();
	input = utilities::getUnsignedIntInput(1, 5, "Input out of range!");

	vector<BikeStore> stores = getStoresWithType(c, (input-1));

	// Display on the screen the stores with that type available, no matter the stock
	cout << endl << endl << "The stores with that type available are: " << endl;

	for(unsigned int i = 0; i < stores.size(); i++){
		printBikeStore(stores.at(i));
	}

	closeFunction();
}

/**
 * @brief Displays on the screen the stores that sell a given type of Bike on the requested amount
 *
 * @param c - a reference to Company
 *
 * @return void
 */
void displayStoresWithStock(Company & c){

	unsigned int input, quantity;
	string in;

	// Get the type that the buyer is interested in
	cout << endl << "What type of Bike are you interested in buying? " << endl;
	c.displayBikes();
	input = utilities::getUnsignedIntInput(1, 5, "Input out of range!");
	unsigned int typeRequested = input-1;

	vector<BikeStore> stores = getStoresWithType(c, input-1);

	// Get the amount of bikes the buyer is interested in buying
	cout << endl << "What quantity are you interested in buying? " << endl;
	cin >> quantity;

	vector<BikeStore> storesWithStock = getStoresWithStock(c, quantity, typeRequested);

	// Display on the screen the stores with the amount of bikes requested of the type requested
	for(unsigned int i = 0; i < storesWithStock.size(); i++){
		printBikeStore(storesWithStock.at(i));
	}

	// If there are no Bikes with the requested stock
	if(storesWithStock.size() == 0){
		cout << "\nNo stores with such stock available!\n";
	}

	closeFunction();
}

/**
 * @brief "Buys" the requested type and amount of Bikes from the best store with such stock available (by reducing the stock of that type of bike by amount)
 *
 * @param c - a reference to Company
 *
 * @return void
 */
void buyBikesFromBest(Company & c){

	unsigned int input, quantity;
	string in;

	// Get the type that the buyer is interested in
	cout << endl << "What type of Bike are you interested in buying? " << endl;
	c.displayBikes();
	input = utilities::getUnsignedIntInput(1, 5, "Input out of range!");
	unsigned int typeRequested = input-1;

	// Get the amount of bikes the buyer is interested in buying
	cout << endl << "What quantity are you interested in buying? " << endl;
	cin >> quantity;

	vector<BikeStore> storesWithStock = getStoresWithStock(c, quantity, typeRequested);

	string bestStoreName = storesWithStock.at(0).getName();

	// "Buy" the requested bikes
	for(unsigned int i = 0; i < quantity; i++){
		c.buyBike(bestStoreName, typeRequested);
	}

	cout << "Bought From " << bestStoreName << endl;

	// Allow buyer to rate the store
	cout << "\n\nWhat is your level of satisfaction with this store? " << endl;
	printSatisfaction();

	input = utilities::getUnsignedIntInput(1, 6, "Input out of range!");
	c.rateStore(input, bestStoreName);

	cout << "\nThank you for your contribution!" << endl;

	closeFunction();
}

/**
 * @brief "Buys" the requested type and amount of Bikes from the store (chosen by the buyer) with such stock available (by reducing the stock of that type of bike by amount)
 *
 * @param c - a reference to Company
 *
 * @return void
 */
void buyBikesFromStore(Company & c){

	unsigned int input, quantity;
	string in, storeName;

	// Get the type that the buyer is interested in
	cout << endl << "What type of Bike are you interested in buying? " << endl;
	c.displayBikes();
	input = utilities::getUnsignedIntInput(1, 5, "Input out of range!");
	unsigned int typeRequested = input-1;

	// Get the amount of bikes the buyer is interested in buying
	cout << endl << "What quantity are you interested in buying? " << endl;
	cin >> quantity;

	vector<BikeStore> storesWithStock = getStoresWithStock(c, quantity, typeRequested);

	for(unsigned int i = 0; i < storesWithStock.size(); i++){
		printBikeStore(storesWithStock.at(i));
	}

	// Let the buyer choose the store that prefers
	cout << "\nFrom what store do you want to buy your bikes?" << endl;
	cin.ignore(1000, '\n');
	getline(cin, storeName);

	bool bought;

	// "Buy" the requested bikes
	for(unsigned int i = 0; i < quantity; i++){
		bought = c.buyBike(storeName, typeRequested);
	}

	// If the purchase was successfull
	if(bought){
		cout << "Bought From " << storeName << endl << endl;

		cout << "\n\nWhat is your level of satisfaction with this store? " << endl;
		printSatisfaction();

		input = utilities::getUnsignedIntInput(1, 6, "Input out of range!");
		c.rateStore(input, storeName);

		cout << "\nThank you for your contribution!" << endl;
	}

	closeFunction();
}

/**
 * @brief Increment by 20 the stock of all types in all stores
 *
 * @param c - a reference to Company
 *
 * @return void
 */
void reStockStores(Company & c){
	c.reStockAllStores();
	closeFunction();
}

/**
 * @brief Prints on the screen all the relevant information about a BikeStore
 *
 * @param b - a BikeStore
 *
 * @return void
 */
void printBikeStore(BikeStore b){

	cout << endl << b.getName();
	cout << endl << "Reputation: " << b.getReputation() << endl;

	vector <pair<typeOfBike, unsigned int>> stock = b.getStock();

	for(unsigned int i = 0; i < stock.size(); i++){
		cout << "   - " << stock.at(i).second << " " << typeToString(stock.at(i).first) << " bikes available" << endl;
	}

}

/**
 * @brief Returns in a vector all the stores that sell a given type of bike
 *
 * @param c - a reference to Company
 * @param t - a type of Bike (represented by an unsigned int
 *
 * @return All stores with type of bike 't'
 */
vector<BikeStore> getStoresWithType(Company & c, unsigned int t){

	priority_queue<BikeStore> aux = c.getStores();
	vector <typeOfBike> types;
	bool hasType = false;

	vector<BikeStore> stores;

	while(!aux.empty()){

		hasType = false;
		types = aux.top().getTypesForSale();

		for(unsigned int i = 0; i < types.size(); i++){
			if(types.at(i) == t){
				hasType = true;
				break;
			}
		}

		if(hasType){
			stores.push_back(aux.top());
		}
		aux.pop();
	}

	return stores;
}

/**
 * @brief Returns in a vector all the stores that sell a given type of bike on the requested amount
 *
 * @param c - a reference to Company
 * @param quantity - the amount of bikes requested
 * @param typeRequested - a type of Bike (represented by an unsigned int
 *
 * @return All stores with type of bike 't' on 'quantity' amount or more
 */
vector<BikeStore> getStoresWithStock(Company & c, unsigned int quantity, unsigned int typeRequested){

	priority_queue<BikeStore> aux = c.getStores();

	vector <pair<typeOfBike, unsigned int>> stock;
	vector<BikeStore> result;

	while(!aux.empty()){

		BikeStore b = aux.top();

		stock = b.getStock();

		for(unsigned int i = 0; i < stock.size(); i++){

			if((stock.at(i).first == typeRequested) && (stock.at(i).second >= quantity)){
				result.push_back(b);
			}

		}

		aux.pop();
	}

	return result;
}



// BIKE STORE MENU
/**
 * @param company
 *
 * \brief Displays bike part's menu and redirects to corresponding place
 *
 * @return void
 */
void menuBikeParts(Company &c) {

    try {
        createMenu(" 5.BIKE PARTS ", {
                {"Display all bike parts",           displayBikeParts},
                {"Buy bike part",                    buyBikePart},
                {"Get cheapest price for bike part", getCheapestBikePart},
                {"Remove bike part record",          removeBikePart},
                {"Add bike part record",             addBikePart}
        }, c);

    }

    catch (utilities::CancelUserRequest &cancel) {}

    closeFunction();
}

/**
 * @param company
 *
 * \brief Displays bike parts' info
 *
 * @return void
 */
void displayBikeParts(Company &c) {

    BST<bikePart> bps = c.getBikeParts();
    BSTItrIn<bikePart> it(bps);
    string lastItem = "";
    while (!it.isAtEnd()) {
        bikePart bp = it.retrieve();
        if (bp.getName() != lastItem) {
            cout << "->" << bp.getName() << endl;
            lastItem = bp.getName();
        }

        cout << "   Supplier: " << bp.getSupplier() << "  - Last price: " << bp.getPrice() << endl;
        it.advance();
    }

    closeFunction();
}

/**
 * @param company
 *
 * \brief Prompts user which bike part to buy and at what price and makes proper changes
 *
 * @return void
 */
void buyBikePart(Company &c) {
    string bikePartName = inputBikePartName(c);
    if (bikePartName != "") {
        string supplier = inputSupplierForPart(c, bikePartName);
        if (supplier != "") {
            cout << "Insert the current purchase's price to update part's info:" << endl;
            unsigned int newPrice = utilities::getUnsignedIntInput("Price not valid");
            bikePart newPart(bikePartName, supplier, newPrice);
            BST<bikePart> bps = c.getBikeParts();
            BSTItrIn<bikePart> it(bps);
            unsigned int counter = 0;
            while (!it.isAtEnd()) {
                bikePart bp = it.retrieve();
                if (bp == newPart) {
                    c.removePart(bp);
                    break;
                }
                it.advance();
            }
            c.addPart(newPart);
        }
    }
    closeFunction();
}

/**
 * @param company
 *
 * \brief returns product after requesting one to the user and checking if exists
 *
 * @return part's name
 */
string inputBikePartName(Company &c) {
    BST<bikePart> bps = c.getBikeParts();
    BSTItrIn<bikePart> it(bps);
    string lastItem;
    cout << "Available Parts:" << endl;
    unsigned int counter = 0;
    while (!it.isAtEnd()) {
        bikePart bp = it.retrieve();
        if (bp.getName() != lastItem) {
            counter++;
            cout << counter << " -> " << bp.getName() << endl;
            lastItem = bp.getName();
        }
        it.advance();
    }
    string msg = "Please select a bike part by typing the corresponding number (or press 0 to go back)";
    cout << msg << endl;
    string input;
    cin >> input;
    cin.clear();
    cin.ignore(1000, '\n');
    while (stoi(input) < 0 || stoi(input) > counter) {

        cout << "Invalid input. " << msg << endl;
        cin >> input;
        cin.clear();
        cin.ignore(1000, '\n');
    }
    if (stoi(input) == 0) return "";
    lastItem = "";
    counter = 0;
    it = BSTItrIn<bikePart>(bps);
    while (!it.isAtEnd()) {
        bikePart bp = it.retrieve();
        if (bp.getName() != lastItem) {
            counter++;
            if (counter == stoi(input)) return bp.getName();
            lastItem = bp.getName();
        }
        it.advance();
    }
    return "";
}

/**
 * @param company
 * @param name - part name
 *
 * \brief returns supplier after requesting it and checking if exists
 *
 * @return string supplier
 */
string inputSupplierForPart(Company &c, string name) {
    cout << "Available suppliers for part " << name << ":" << endl;
    BST<bikePart> bps = c.getBikeParts();
    BSTItrIn<bikePart> it(bps);
    unsigned int counter = 0;
    while (!it.isAtEnd()) {
        bikePart bp = it.retrieve();
        if (bp.getName() == name) {
            counter++;
            cout << counter << " - " << bp.getSupplier() << endl;
        }
        it.advance();
    }

    string msg = "Please select a supplier by typing the corresponding number (or press 0 to go back)";
    cout << msg << endl;
    string input;
    cin >> input;
    cin.clear();
    cin.ignore(1000, '\n');
    while (stoi(input) < 0 || stoi(input) > counter) {
        cout << "Invalid input. " << msg << endl;
        cin >> input;
        cin.clear();
        cin.ignore(1000, '\n');
    }
    if (stoi(input) == 0) return "";
    counter = 0;
    it = BSTItrIn<bikePart>(bps);
    while (!it.isAtEnd()) {
        bikePart bp = it.retrieve();
        if (bp.getName() == name) {
            counter++;
            if (counter == stoi(input)) return bp.getSupplier();
        }
        it.advance();
    }
    return "";

}

/**
 * @param company
 *
 * \brief displays cheapest part of an inserted name
 *
 * @return void
 */
void getCheapestBikePart(Company &c) {

    string name = inputBikePartName(c);

    if (name != "") {
        BST<bikePart> bps = c.getBikeParts();
        BSTItrIn<bikePart> it(bps);

        while (!it.isAtEnd()) {

            bikePart bp = it.retrieve();
            if (bp.getName() == name) {
                cout << "Cheapest " << name << ": " << bp.getSupplier() << " - Last purchase price: " << bp.getPrice() << endl;
                break;
            }

            it.advance();
        }
    }

    closeFunction();

}

/**
 * @param company
 *
 * \brief removes bike part in company's parts BST
 *
 * @return void
 */
void removeBikePart(Company &c) {
    string bikePartName = inputBikePartName(c);
    if (bikePartName != "") {
        string supplier = inputSupplierForPart(c, bikePartName);
        if (supplier != "") {
            bikePart newPart(bikePartName, supplier, 0);
            BST<bikePart> bps = c.getBikeParts();
            BSTItrIn<bikePart> it(bps);
            unsigned int counter = 0;
            while (!it.isAtEnd()) {
                bikePart bp = it.retrieve();
                if (bp == newPart) {
                    c.removePart(bp);
                    cout << "Bike part removed successfully" << endl;
                    break;
                }
                it.advance();
            }
            if (it.isAtEnd()) cout << "Bike part non-existant. Couldn't remove." << endl;
        }
    }
    closeFunction();
}


/**
 * @param company
 *
 * \brief adds bike part to company's parts BST
 *
 * @return void
 */
void addBikePart(Company &c) {
    string name, supplier;
    unsigned int price;
    cout << "Please insert bike part's name:" << endl;
    cin >> name;
    cin.clear();
    cin.ignore(1000, '\n');
    cout << "Please insert bike part's supplier:" << endl;
    cin >> supplier;
    cin.clear();
    cin.ignore(1000, '\n');
    BST<bikePart> bps = c.getBikeParts();
    BSTItrIn<bikePart> it(bps);
    unsigned int counter = 0;
    while (!it.isAtEnd()) {
        bikePart bp = it.retrieve();
        if (bp.getName() == name && bp.getSupplier() == supplier) {
            cout << "Bike part already exists. Exiting." << endl;
            closeFunction();
            return;
        }
        it.advance();
    }
    cout << "Please insert bike part's last purchase's price:" << endl;
    price = utilities::getUnsignedIntInput("Invalid Price");
    c.addPart(bikePart(name, supplier, price));
    closeFunction();
}



// OTHERS

/**
 * @param c - a reference to Company
 *
 * @brief Calls all the save functions from Company when the program is being closed, saving all the current information on a file.
 *
 * @return void
 */
void exitProgram(Company &c){

	c.saveBikes();
	c.saveCompanyNameAndPlaces();
	c.saveUsers();
	c.saveParts();
	//TODO uncomment this
	c.saveStores();
    c.saveBrokenBikes();
}

/**
 * @param input - any string
 *
 * @brief Checks if the string is a number, with no alphabetic characters
 *
 * @return bool - whether is true or false that the string is a number (true if it is, false otherwise)
 */
bool isNumber(string input){

	for (unsigned int i = 0; i < input.size(); i++){
		if(input[i] < '0' || input[i] > '9')
			return false;
	}

	return true;
}

void printSatisfaction(){
	cout << "1 - Very Bad" << endl;
	cout << "2 - Bad" << endl;
	cout << "3 - Reasonable" << endl;
	cout << "4 - Good" << endl;
	cout << "5 - Very Good" << endl;
}

string typeToString(typeOfBike type){
	if(type == urban)
		return "urban";
	else if(type == urbanSimple)
		return "urbanSimple";
	else if(type == race)
		return "race";
	else
		return "child";
}
