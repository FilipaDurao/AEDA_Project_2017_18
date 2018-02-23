#include "Company.h"

#include "utilities.h"
#include <algorithm>
#include <stack>

using namespace std;
// CONSTRUTOR/DESTRUTOR
/**
 * @param fileNameCompany - the name of the file with the Company and Place data
 * @param fileNameClients - the name of the file with the PremiumUsr data
 * @param fileNameBikes - the name of the file with the Bike data
 *
 * @brief Creates a Company.
 *
 * @return Company
 */
Company::Company(const string &fileNameCompany, const string &fileNameClients, const string &fileNameBikes,
                 const string &fileNameStores, const string &fileNameParts, const string &fileNameScrapyard) : fileNameCompany(fileNameCompany),
                                                                              fileNameClients(fileNameClients),
                                                                              fileNameBikes(fileNameBikes),
                                                                              fileNameStores(fileNameStores),
                                                                              fileNameParts(fileNameParts),
                                                                              fileNameScrapyard(fileNameScrapyard),
                                                                              bikeParts(bikePart("", "", 0)) {

	ifstream in_stream(fileNameCompany);
	string compName, numBikes, type, numPrUsers, name, email, adress, phone, ID, NIF, favType, password, isUsing, currentAmount, numPlaces, x, y, inNumBikes, placeID, bikeID, startPlaceID, scrappingDate;
    int startTime;

	if (in_stream.is_open()){


			getline(in_stream, compName);					// get from the file and set the Company Name
			this->name = compName;

			while (!in_stream.eof()){
					getline(in_stream, name);
					getline(in_stream, placeID);
					unsigned int placeIDaux = stoi(placeID);
					getline(in_stream, x);
					unsigned int xAux = stoi(x);
					getline(in_stream, y);
					unsigned int yAux = stoi(y);
					Place *place = new Place(name, xAux, yAux, placeIDaux);
					places.push_back(place);
			}
	}


	in_stream.close();

	in_stream.open(fileNameBikes);

		if(in_stream.is_open()){

			while(!in_stream.eof()){

				getline(in_stream,type);
				getline(in_stream, bikeID);
				getline(in_stream, placeID);


				if (type == "urban"){
					Bike *bike = new Bike(urban, stoi(bikeID));			// Create the Bike

					if(stoi(placeID) != -1){								// If the Bike it's not being used
						for(unsigned int i = 0; i < places.size(); i++){
							if(places.at(i)->getID() == stoi(placeID)){		// Find the place it refers to
								places.at(i)->addBike(bike);				// Place it there
								break;
							}
						}

					}
					this->bikes.push_back(bike);								// Put in the Company's bikes vector
				}

				if (type == "urbanSimple"){
					Bike *bike = new Bike(urbanSimple, stoi(bikeID));

					if(stoi(placeID) != -1){								// If the Bike it's not being used
						for(unsigned int i = 0; i < places.size(); i++){
							if(places.at(i)->getID() == stoi(placeID)){		// Find the place it refers to
								places.at(i)->addBike(bike);				// Place it there
								break;
							}
						}
					}
					this->bikes.push_back(bike);								// Put in the Company's bikes vector
				}

				if (type == "race"){
					Bike *bike = new Bike(race, stoi(bikeID));

					if(stoi(placeID) != -1){								// If the Bike it's not being used
						for(unsigned int i = 0; i < places.size(); i++){
							if(places.at(i)->getID() == stoi(placeID)){		// Find the place it refers to
								places.at(i)->addBike(bike);				// Place it there
								break;
							}
						}
					}
					this->bikes.push_back(bike);								// Put in the Company's bikes vector
				}

				if (type == "child"){
					Bike *bike = new Bike(child, stoi(bikeID));

					if(stoi(placeID) != -1){								// If the Bike it's not being used
						for(unsigned int i = 0; i < places.size(); i++){
							if(places.at(i)->getID() == stoi(placeID)){		// Find the place it refers to
								places.at(i)->addBike(bike);				// Place it there
								break;
							}
						}
					}
					this->bikes.push_back(bike);								// Put in the Company's bikes vector
				}
			}
	}

	in_stream.close();

	in_stream.open(fileNameClients);



	if (in_stream.is_open()){


        while(getline(in_stream, ID)){

            //CHECK IF BASIC USER (HAS A . (dot))
            if(ID[0] == '.') {
                //It's reading a Basiic User Information
                ID = ID.substr(1, ID.length() - 1); // get the id only after the '.';
                getline(in_stream, isUsing);
                getline(in_stream, startPlaceID);
                getline(in_stream, bikeID);

                startTime = stoi(isUsing);

                Place * startPlace;

                for(unsigned int i = 0; i < places.size(); i++){
                    if(places.at(i)->getID() == stoi(startPlaceID)){		// Find the place it refers to
                        	startPlace = places.at(i);			// set the startPlace
                        break;
                    }
                }

                Bike* currentBike;

                for(unsigned int i = 0; i < bikes.size(); i++){
                    if(bikes.at(i)->getID() == stoi(bikeID)){		// Find the place it refers to
                        	currentBike = bikes.at(i);			// set the startPlace
                        break;
                    }
                }


                Time beginTime = Time(stoi(isUsing));

                BasicUsr *newUser = new BasicUsr(stoi(ID), startPlace, currentBike->getType(), beginTime, true);

                usersAtTheMoment.push_back(newUser);	// Goes to the usersAtTheMoment vector

                currentBike->setAvailability(false);	// The availability is set to false
                currentBike->setInitialTime(startTime);   //Set the startTime
                newUser->setBike(currentBike);



                for(unsigned int i = 0; i < startPlace->getNumBikes(); i++){
                    if(startPlace->getBikeInVec(i)->getID() == currentBike->getID()) {
                        startPlace->removeBike(i);
                        break;
                    }
                }


                continue; //continue the while loop, so it can read another user (basic or premium)
            }



			getline(in_stream, name);
			getline(in_stream, email);
			getline(in_stream, adress);
			getline(in_stream, phone);
			getline(in_stream, NIF);
			getline(in_stream, favType);
			getline(in_stream, password);
			getline(in_stream, isUsing);
			getline(in_stream, currentAmount);
			getline(in_stream, bikeID);


			startTime = stoi(isUsing);

            if (favType == "urban"){

                if(startTime == 0) {            //If the user is not using a bike

                    PremiumUsr *newUser = new PremiumUsr(name, email, adress, stoi(ID), stoi(phone), stoi(NIF), urban, password, false, stof(currentAmount));
                    premiumUsers.push_back(newUser);

                } else {                        //the user is already using a bike

                    PremiumUsr *newUser = new PremiumUsr(name, email, adress, stoi(ID), stoi(phone), stoi(NIF), urban, password, true, stof(currentAmount));
                    premiumUsers.push_back(newUser);

                    usersAtTheMoment.push_back(newUser);	// Goes to the usersAtTheMoment vector

                    for(unsigned int i = 0; i < bikes.size(); i++){
                        if(bikes.at(i)->getID() == stoi(bikeID)){
                            bikes.at(i)->setAvailability(false);	// The availability is set to false
                            bikes.at(i)->setInitialTime(Time(startTime));   //Set the startTime
                            newUser->setBike(bikes.at(i));
                        }
                    }

                }
            }

            if (favType == "urbanSimple"){
                if(startTime == 0) {            //If the user is not using a bike

                    PremiumUsr *newUser = new PremiumUsr(name, email, adress, stoi(ID), stoi(phone), stoi(NIF), urbanSimple, password, false, stof(currentAmount));
                    premiumUsers.push_back(newUser);

                } else {                        //the user is already using a bike

                    PremiumUsr *newUser = new PremiumUsr(name, email, adress, stoi(ID), stoi(phone), stoi(NIF), urbanSimple, password, true, stof(currentAmount));
                    premiumUsers.push_back(newUser);

                    usersAtTheMoment.push_back(newUser);	// Goes to the usersAtTheMoment vector

                    for(unsigned int i = 0; i < bikes.size(); i++){
                        if(bikes.at(i)->getID() == stoi(bikeID)){
                            bikes.at(i)->setAvailability(false);	// The availability is set to false
                            bikes.at(i)->setInitialTime(Time(startTime));   //Set the startTime
                            newUser->setBike(bikes.at(i));
                        }
                    }

                }
            }

            if (favType == "race"){
                if(startTime == 0) {            //If the user is not using a bike

                    PremiumUsr *newUser = new PremiumUsr(name, email, adress, stoi(ID), stoi(phone), stoi(NIF), race, password, false, stof(currentAmount));
                    premiumUsers.push_back(newUser);

                } else {                        //the user is already using a bike

                    PremiumUsr *newUser = new PremiumUsr(name, email, adress, stoi(ID), stoi(phone), stoi(NIF), race, password, true, stof(currentAmount));
                    premiumUsers.push_back(newUser);

                    usersAtTheMoment.push_back(newUser);	// Goes to the usersAtTheMoment vector

                    for(unsigned int i = 0; i < bikes.size(); i++){
                        if(bikes.at(i)->getID() == stoi(bikeID)){
                            bikes.at(i)->setAvailability(false);	// The availability is set to false
                            bikes.at(i)->setInitialTime(Time(startTime));   //Set the startTime
                            newUser->setBike(bikes.at(i));
                        }
                    }

                }
            }

            if (favType == "child"){
                if(startTime == 0) {            //If the user is not using a bike

                    PremiumUsr *newUser = new PremiumUsr(name, email, adress, stoi(ID), stoi(phone), stoi(NIF), child, password, false, stof(currentAmount));
                    premiumUsers.push_back(newUser);

                } else {                        //the user is already using a bike

                    PremiumUsr *newUser = new PremiumUsr(name, email, adress, stoi(ID), stoi(phone), stoi(NIF), child, password, true, stof(currentAmount));
                    premiumUsers.push_back(newUser);

                    usersAtTheMoment.push_back(newUser);	// Goes to the usersAtTheMoment vector

                    for(unsigned int i = 0; i < bikes.size(); i++){
                        if(bikes.at(i)->getID() == stoi(bikeID)){
                            bikes.at(i)->setAvailability(false);	// The availability is set to false
                            bikes.at(i)->setInitialTime(Time(startTime));   //Set the startTime
                            newUser->setBike(bikes.at(i));
                        }
                    }

                }
            }
		}
	}

	in_stream.close();


	// For part 2
    //Bikes repair shop
    in_stream.open(fileNameParts);
    string supplier;
    string price;

    if (in_stream.is_open()) {

        while (!in_stream.eof()) {

            getline(in_stream, name);
            getline(in_stream, supplier);
            getline(in_stream, price);

            bikeParts.insert(bikePart(name, supplier, stof(price)));
        }
    }

    in_stream.close();

    //Bike Stores
	string reputation;
	vector <typeOfBike> typesForSale;
	vector <pair<typeOfBike, unsigned int>> stock;
	int rep;


	type = "";


	in_stream.open(fileNameStores);


	if (in_stream.is_open()){

		while(!in_stream.eof()){

			getline(in_stream, name);
			getline(in_stream, reputation);

			while(getline(in_stream, type)){

				if(type != "."){

					if(type == "urban"){
						typesForSale.push_back(urban);
					}

					else if(type == "urbanSimple"){
						typesForSale.push_back(urbanSimple);
					}

					else if(type == "race"){
						typesForSale.push_back(race);
					}

					else if(type == "child"){
						typesForSale.push_back(child);
					}

				}

				else if(type == "."){
					break;
				}

			}

			while(getline(in_stream, type)){

				if(type != "."){

					if(type == "urban"){
						getline(in_stream, numBikes);
						stock.push_back(make_pair(urban, (unsigned int)stoi(numBikes)));
					}

					else if(type == "urbanSimple"){
							getline(in_stream, numBikes);
							stock.push_back(make_pair(urbanSimple, (unsigned int)stoi(numBikes)));
					}

					else if(type == "race"){
						getline(in_stream, numBikes);
						stock.push_back(make_pair(race, (unsigned int)stoi(numBikes)));
					}

					else if(type == "child"){
						getline(in_stream, numBikes);
						stock.push_back(make_pair(child, (unsigned int)stoi(numBikes)));
					}

				}

				else if(type == "."){
					break;
				}
			}


		rep = stoi(reputation);

		BikeStore b(name, rep, stock, typesForSale);
		stores.push(b);
		typesForSale.clear();
		stock.clear();

		}
	}
	in_stream.close();

	//SCRAPYARD

	in_stream.open(fileNameScrapyard);

		if(in_stream.is_open()){

			while(!in_stream.eof()){

				getline(in_stream,type);
				getline(in_stream, bikeID);
				getline(in_stream, scrappingDate);


				if (type == "urban"){
					Bike *bike = new Bike(urban, stoi(bikeID));			// Create the Bike

					Time sDate = Time(stoi(scrappingDate));

					bike->setState(broken);
					bike->setScrappingDate(sDate);

					this->brokenBikes.insert(bike);								// Put in the Company's broken bikes vector
				}

				if (type == "urbanSimple"){
					Bike *bike = new Bike(urbanSimple, stoi(bikeID));

					Time sDate = Time(stoi(scrappingDate));

					bike->setState(broken);
					bike->setScrappingDate(sDate);

					this->brokenBikes.insert(bike);								// Put in the Company's broken bikes vector
				}

				if (type == "race"){
					Bike *bike = new Bike(race, stoi(bikeID));

					Time sDate = Time(stoi(scrappingDate));

					bike->setState(broken);
					bike->setScrappingDate(sDate);

					this->brokenBikes.insert(bike);								// Put in the Company's broken bikes vector
				}

				if (type == "child"){
					Bike *bike = new Bike(child, stoi(bikeID));

					Time sDate = Time(stoi(scrappingDate));

					bike->setState(broken);
					bike->setScrappingDate(sDate);

					this->brokenBikes.insert(bike);								// Put in the Company's broken bikes vector
				}
			}
	}

	in_stream.close();

}


Company::~Company() {
	// TODO Auto-generated destructor stub
}


//VECTOR WORKS

/**
 * @param premium - a PremiumUsr
 *
 * @brief Adds a PremiumUsr to the premiumUsers vector of Company
 *
 * @return None
 */
void Company::addPremiumToPremiumVec(PremiumUsr* premium){
	premiumUsers.push_back(premium);
}

/**
 * @param premium - a PremiumUsr
 *
 * @brief Removes a PremiumUsr to the usersAtTheMoment vector of Company when the User stops using a Bike
 *
 * @return None
 */
void Company::removePremiumFromUsersVec(PremiumUsr* premium){
	for(unsigned int i = 0; i < usersAtTheMoment.size(); i++){
		if(usersAtTheMoment.at(i)->isPremium()){
			if(usersAtTheMoment.at(i)->getUserID() == premium->getID()){
				usersAtTheMoment.erase(usersAtTheMoment.begin() + i);
				return;
			}
		}
	}
}

/**
 * @param basic - a BasicUsr
 *
 * @brief Removes a BasicUsr to the usersAtTheMoment vector of Company when the User stops using a Bike
 *
 * @return None
 */
void Company::removeBasicFromUsersVec(BasicUsr* basic){
	for(unsigned int i = 0; i < usersAtTheMoment.size(); i++){
		if(usersAtTheMoment.at(i)->isPremium() == false){
			if(usersAtTheMoment.at(i)->getUserID() == basic->getID()){
				usersAtTheMoment.erase(usersAtTheMoment.begin() + i);
				return;
			}
		}
	}
}
/**
 * @param premium - a PremiumUsr
 *
 * @brief Adds a PremiumUsr to the usersAtTheMoment vector of Company when the User starts using a Bike
 *
 * @return None
 */
void Company::addPremiumToUsersVec(PremiumUsr* premium){
	usersAtTheMoment.push_back(premium);
}
/**
 * @param basic - a BasicUsr
 *
 * @brief Adds a BasicUsr to the usersAtTheMoment vector of Company
 *
 * @return None
 */
void Company::addBasicToUsersVec(BasicUsr* basic){
	usersAtTheMoment.push_back(basic);
}

//DISPLAYS

/**
 * @param None
 *
 * @brief Displays the company info
 * \details Displays the total amount of Bikes, the total amount of PremiumUsrs, the total amount of users using Bikes at the moment,
 * 			and the total amount of Places. Then lists for each Place how many Bikes are available.
 *
 * @return None
 */
void Company::displayCompanyInfo() const{

	cout << endl << "** " << name << " **" <<"\n\n";

	cout << "> The company has " << bikes.size() << " bikes." << '\n';
	cout << "> The company has " << premiumUsers.size() << " Premium Users." << '\n';
	cout << "> The company has " << usersAtTheMoment.size() << " users using bikes at the moment" << '\n';
	cout << "> The company has " << places.size() << " bike stations." << '\n';

	for(unsigned int i = 0; i < places.size(); i++){
		cout << "\n " << places.at(i)->getName() << '\n';
		cout << "-" << places.at(i)->getNumBikes() << " bikes available.\n";
	}
}

/**
 * @param None
 *
 * @brief Displays the company users at the moment info.
 *
 * @return None
 */
void Company::displayUsersAtTheMoment() const{
	if(usersAtTheMoment.size() == 0) cout << "There are no users at the moment!" << endl;
    else {
        for(unsigned int i = 0; i < usersAtTheMoment.size(); i++){
            usersAtTheMoment.at(i)->displayUser();
        }
    }

}

/**
 * @param None
 *
 * @brief Displays the company PremiumUsrs info.
 *
 * @return None
 */
void Company::displayPremiumUsers(){
	for (unsigned int i = 0; i < premiumUsers.size(); i++){
		premiumUsers.at(i)->displayUser();
	}
}

/**
 * @param None
 *
 * @brief Displays the company Places info.
 *
 * @return None
 */
void Company::displayPlaces() const{
	for(unsigned int i = 0; i < places.size(); i++){
		cout << endl << endl << endl << places.at(i)->getID() << " - " << places.at(i)->getName() << endl << endl;
		places.at(i)->displayPlaceBikes();
	}
}

/**
 * @param None
 *
 * @brief Displays the company Bike types info.
 *
 * @return None
 */
void Company::displayBikes() const{
	cout << "1 - Urban" << endl;
	cout << "2 - Urban Simple" << endl;
	cout << "3 - Racing" << endl;
	cout << "4 - Child Bike" << endl;
}


// GETTERS

/**
 * @param None
 *
 * @brief Returns a vector with all the Places of the Company
 *
 * @return places - vector<Place *>
 */
const vector<Place *> Company::getPlaces() const{
	return places;
}

priority_queue <BikeStore> Company::getStores() const{
	return stores;
}

/**
 * @param None
 *
 * @brief Returns the name of the Company.
 *
 * @return name - const string
 */
const string Company::getCompanyName() const{
	return this->name;
}

/**
 * @param None
 *
 * @brief Returns the name of the file used to import the data of the Company and later to which we will export the data.
 *
 * @return fileNameCompany - const string
 */
const string Company::getCompanyFileName() const{
	return this->fileNameCompany;
}

/**
 * @param None
 *
 * @brief Returns the name of the file used to import the data of the Clients and later to which we will export the data.
 *
 * @return fileNameClients - const string
 */
const string Company::getClientsFileName() const{
	return this->fileNameClients;
}

/**
 * @param None
 *
 * @brief Returns the name of the file used to import the data of the Stores and later to which we will export the data.
 *
 * @return fileNameStores - const string
 */
const string Company::getStoresFileName() const{
	return this->fileNameStores;
}

/**
 * @param None
 *
 * @brief Returns the name of the file used to import the data of the Bike Parts and later to which we will export the data.
 *
 * @return fileNameBikeParts - const string
 */
const string Company::getBikePartsFileName() const {
    return this->fileNameParts;
}

/**
 * @param None
 *
 * @brief Returns the name of the file used to import the data of the Bikes and later to which we will export the data.
 *
 * @return fileNameBikes - const string
 */
const string Company::getBikesFileName() const{
	return this->fileNameBikes;
}

/**
 * @param None
 *
 * @brief Returns the name of the file used to import the data of the Broken Bikes and later to which we will export the data.
 *
 * @return fileNameBikes - const string
 */
const string Company::getBrokenBikesFileName() const{
	return this->fileNameScrapyard;
}

/**
 * @param None
 *
 * @brief Returns the number of bikes owned by the company.
 *
 * @return numBikes
 */
unsigned int Company::getNumBikes() const{
	return this->bikes.size();
}

/**
 * @param None
 *
 * @brief Returns the number of Premium Clients in the company.
 *
 * @return numPremiumClients
 */
unsigned int Company::getNumPremiumCl() const{
	return this->premiumUsers.size();
}

/**
 * @param None
 *
 * @brief Returns the number of users using bikes at this moment.
 *
 * @return numMomentUsrs
 */
unsigned int Company::getNumMomentUsr() const{
	return this->usersAtTheMoment.size();
}

/**
 * @param user - Pointer to PremiumUsr, where the info about the matched user is going to go
 * @param email - email to search
 *
 * @brief If the email exists, it places the PremiumUsr (corresponding to the email) info the given PremiumUsr*. If none found, throw UnexistentEmail exception
 *
 * @return none
 */
void Company::getPremiumUsrByEmail(PremiumUsr*& user, string email) {
    bool foundMatch = false;

    for(int i = 0; i < this->premiumUsers.size(); i++) {
        if(this->premiumUsers.at(i)->getEmail() == email) {
          user = premiumUsers.at(i);
          foundMatch = true;
          break;
        }
    }

    if (!foundMatch) throw UnexistentEmail(email);
}


/**
 * @param ID - A possible PremiumUsr ID
 *
 * @brief If there is a PremiumUsr with such ID, returns a pointer to it, else, returns a NULL pointer
 *
 * @return Pointer to PremiumUsr
 */
PremiumUsr* Company::getPremiumUserByID(unsigned int ID) const{

	for(unsigned int i = 0; i < premiumUsers.size(); i++){
		if(premiumUsers.at(i)->getID() == ID){
			return premiumUsers.at(i);
		}
	}

	return NULL;
}

/**
 * @param ID - A possible BasicUsr ID
 *
 * @brief If there is a BasicUsr with such ID, returns a pointer to it, else, returns a NULL pointer
 *
 * @return Pointer to BasicUsr
 */
BasicUsr* Company::getBasicUserAtTheMomentByID(unsigned int ID) const{

	for(unsigned int i = 0; i < usersAtTheMoment.size(); i++){
		if( (usersAtTheMoment.at(i)->isPremium() == false) && (usersAtTheMoment.at(i)->getUserID() == ID) ){
			return (BasicUsr*)usersAtTheMoment.at(i);
		}
	}

	return NULL;
}


/**
 * @param none
 *
 * @brief returns company's bikeParts BST
 *
 * @return BST bikeParts
 */
BST<bikePart> Company::getBikeParts() const {
    return bikeParts;
}

/**
 * @param None
 *
 * @brief Returns a vector with all the PremiumUsrs of the Company
 *
 * @return premiumUsers - vector<PremiumUsr *>
 */
vector<PremiumUsr*> Company::getAllPremiums(){
	return this->premiumUsers;
}

/**
 * @param None
 *
 * @brief Returns a vector with all the Bikes of the Company
 *
 * @return bikes - vector<Bike *>
 */
vector<Bike*> Company::getAllBikes() const{
	return this->bikes;
}


// LOGIN SYSTEM

/**
 * @param user
 * @param password
 *
 * @brief Returns true or false, whether the given password for the given user is correct or not
 *
 * @return bool
 */
const bool Company::verifyPassword(PremiumUsr*& user, string password) const {
    return (user->getPassword() == password);
}

/**
 * @param user - pointer to the User
 * @param password - the password the User inserted
 *
 * @brief Returns the User's password on the system
 *
 * @return bool
 */
const string Company::checkPw(PremiumUsr*& user, string password) const {
    return user->getPassword();
}

/**
 * @param name
 * @param email
 * @param adress
 * @param phone
 * @param NIF
 * @param type - type of Bike that the User will prefer
 * @param password
 *
 * @brief Creates a new PremiumUsr.
 *
 * @return Returns True or False whether the User was created or not
 */
bool Company::createPremiumUsr(string name, string email, string adress, string phone, string NIF, string type, string password){

	for (unsigned int i = 0; i < premiumUsers.size(); i++){
		if( (premiumUsers.at(i)->getName() == name) || (premiumUsers.at(i)->getEmail() == email) || (premiumUsers.at(i)->getPhone() == stoi(phone)) || (premiumUsers.at(i)->getNIF() == stoi(NIF)) ){
			return false;		// Not possible to create the user
		}
	}

	if (type == "urban"){
		PremiumUsr* premium = new PremiumUsr(name, email, adress, stoi(phone), stoi(NIF), urban, password);
		premiumUsers.push_back(premium);
		return true; 	// User created with success
	}
	if (type == "urbanSimple"){
		PremiumUsr* premium = new PremiumUsr(name, email, adress, stoi(phone), stoi(NIF), urbanSimple, password);
		premiumUsers.push_back(premium);
		return true; 	// User created with success
	}
	if (type == "race"){
		PremiumUsr* premium = new PremiumUsr(name, email, adress, stoi(phone), stoi(NIF), race, password);
		premiumUsers.push_back(premium);
		return true; 	// User created with success
	}
	if (type == "child"){
		PremiumUsr* premium = new PremiumUsr(name, email, adress, stoi(phone), stoi(NIF), child, password);
		premiumUsers.push_back(premium);
		return true; 	// User created with success
	}
}




/**
 * @param email - the unexistent email
 *
 * @brief Creates an UnexistentEmail exception
 *
 * @return UnexistentEmail
 */
UnexistentEmail::UnexistentEmail(string email) : email(email) {};

/**
 * @param None
 *
 * @brief Returns the unexistent email form UnexistentEmail exception object
 *
 * @return email
 */
const string UnexistentEmail::getEmail() const {
    return this->email;
}

/**
 * @param None
 *
 * @brief Creates a new BasicUsr when a Bike is requested by a non PremiumUsr
 *
 * @return basicUsr - BasicUsr *
 */
BasicUsr* Company::createBasicUsr(){

	string type = "";
	unsigned int bikeOption, placeOption;
	bool validPlace = false, validBikeType = false;
	Place *newPlace;


	cout << "\n\n0 - Cancel\n";
	displayBikes();
	cout << "\n\nWhich type of bike are you interested in taking?  (Type in the correspondent number)\n";
	bikeOption = utilities::getUnsignedIntInput(0, 5, "Invalid option. Please try again");

	//throwing cancel exception
	if(bikeOption == 0) throw utilities::CancelUserRequest();


	while(!validPlace){

			// Get the place where the User is
			cout << "\n\n0 - Cancel\n";
			displayPlaces();
			cout << "\n\nIn which renting point are you?  (Type in the correspondent number)\n";
			placeOption = utilities::getUnsignedIntInput(0, getPlaces().size() + 1, "Invalid Place. Please try again.");

			//throwing cancel exception
			if(placeOption == 0) throw utilities::CancelUserRequest();

			// Find the given place in the places vector
			for(unsigned int i = 0; i < getPlaces().size(); i++){
				if(getPlaces().at(i)->getID() == placeOption){
                    if(getPlaces().at(i)->getNumBikes() == 0) throw utilities::NoBikesAvailable();
					newPlace = getPlaces().at(i);
					validPlace=true;
					break;
				}
			}
		}

	//Time startTime = Time(17, 30);
	//To be able to test different values, the Current Time will be asked for input, otherwise, the time must be read from the system
	Time startTime = getCurrentTimeInput();

	BasicUsr * basic;


	if(bikeOption == 1){
		basic = new BasicUsr(&*newPlace, urban, startTime);
	}
	if(bikeOption == 2){
		basic = new BasicUsr(&*newPlace, urbanSimple, startTime);
	}
	if(bikeOption == 3){
		basic = new BasicUsr(&*newPlace, race, startTime);
	}
	if(bikeOption == 4){
		basic = new BasicUsr(&*newPlace, child, startTime);
	}

	cout << "Your temporary ID is: " << basic->getID() << endl;
	return basic;
}



//GET SPECIFIC BIKES
/**
*
* @param type - the type of bike requested
* @param position - the position where the user is
*
*@brief Returns the vector of Places near of where the User is that has the requested type of Bike
*
* @return places
*/
const vector<Place *> Company::getNearestPlacesWithBike(typeOfBike t, Position p) const{
	vector<Place *> places = getPlaces();
	vector<Place *> result;
	for (int i = 0; i < places.size(); i++) {
		Place* place = places[i];
		vector<Bike*> availableBikesOfType = place->getBikeOfType(t);
		if (availableBikesOfType.size() > 0) {
			result.push_back(place);
		}
	}
	std::sort(result.begin(), result.end(), Place::compareByDistanceToPoint(p));
	return result;
}

/**
*
*
* @param pair<Place*, unsigned int>& p1
* @param pair<Place*, unsigned int>& p2
*
*@brief Auxiliary function that return true if the unsigned int in p1 is less than unsigned int in p2
*
* @return Bool
*/

bool comparePlacesByNumBikes(pair<Place*, unsigned int>& p1, pair<Place*, unsigned int> & p2) {

    return p1.second > p2.second;
}

Bike* Company::getBikeByID(unsigned int id) {
    for(int i =0; i< bikes.size(); i++) {
        if(bikes.at(i)->getID() == id) return bikes.at(i);
    }

    return nullptr;
}


Bike* Company::getBrokenBikeByID(unsigned int id) {

    if(brokenBikes.empty()) return nullptr;
    bikeScrapping::const_iterator it;
    for (it = brokenBikes.begin(); it != brokenBikes.end(); ++it) {
        if((*it)->getID() == id) {
            return *it;

        }
    }

    return nullptr;
}


/**
*
*
* @param None
*@brief Reallocates the company's bikes so that the number of bikes in each place is more well distributed
*
* @return None
*/
void Company::realocateBikes() {

    //Total bikes counter
    unsigned int totalBikes = 0;

    vector<pair<Place*, unsigned int>> placesBikeNecessity;

    //iterating all the places
    for(int i = 0; i < places.size(); i++) {
        //increment the total bikes counter
        totalBikes += places.at(i)->getNumBikes();
    //add the place to the vector for further analysis
        placesBikeNecessity.push_back(make_pair(places.at(i), places.at(i)->getNumBikes()));
    }

    unsigned int avgBikePerPlace = totalBikes / places.size(); // minimum number of bikes for each place, rounded bottom

    //sorting placesBikeNecessity by num of bikes (DESC)
    sort(placesBikeNecessity.begin(), placesBikeNecessity.end(), comparePlacesByNumBikes);


    bool unsorted = true;
    while(unsorted) {
        //iterating placesBikeNecessity and reallocating bikes
        for(int i = 0; i < placesBikeNecessity.size(); i++) {

            if( ( placesBikeNecessity.at(i).second - avgBikePerPlace ) == 1 ) {
                // if the difference between the first place no of bikes and the avg is <= 1, it may or may not be distributed,
                //to check we must see if the last place has enough bikes, but if it needs, the first place must only transfer 1 bike (so it stays with avg nBikes)
                if(placesBikeNecessity.at(placesBikeNecessity.size() - 1 - i).second < avgBikePerPlace) { //the oloast place needs at least one bike
                    transferBikes( placesBikeNecessity.at(i).first , placesBikeNecessity.at(placesBikeNecessity.size() - 1 - i).first, 1);
                    placesBikeNecessity.at(i).second -= 1;
                    placesBikeNecessity.at(placesBikeNecessity.size() - 1 - i).second += 1;
                    break;
                } else { //The last place has enough bikes, so the bikes are distributed
                    unsorted = false;
                    continue;
                }

            } else if (( placesBikeNecessity.at(i).second - avgBikePerPlace ) == 0) { //the first place has the avg num of bikes, then the distribution is correct
                unsorted = false;
                continue;
            }
            else {  //distribute
                unsorted = true;
                //how many bikes does the lesser place need?
                unsigned int nBikesInNeed = avgBikePerPlace - placesBikeNecessity.at(placesBikeNecessity.size() - 1 - i).second;

                //transfer nBikesInNeed from the place with the higher no. of bikes to the place with the lesser amount
                transferBikes( placesBikeNecessity.at(i).first , placesBikeNecessity.at(placesBikeNecessity.size() - 1 - i).first, nBikesInNeed);
                placesBikeNecessity.at(i).second -= nBikesInNeed;
                placesBikeNecessity.at(placesBikeNecessity.size() - 1 - i).second += nBikesInNeed;

                break;



            }
        }


        if(unsorted) {
            sort(placesBikeNecessity.begin(), placesBikeNecessity.end(), comparePlacesByNumBikes);

        } else { // already sorted
            break;
        }


    }

}

/**
*
*
* @param Place* p1 - origin place
* @param Place* p2 - destination place
* @param unsigned int nBikes - number of bikes to transfer (careful not to ask more bikes than the ones available in p1!)

*@brief Reallocates the company's bikes so that the number of bikes in each place is more well distributed
*
* @return None
*/
void Company::transferBikes(Place* p1, Place* p2, unsigned int nBikes) {

    for(unsigned int i = 0; i< nBikes; i++) {
        //pointer to the bike to transfer
        Bike* bikeToTransfer = p1->getBikes().at(0);
        //add the bike to p2
        p2->addBike(bikeToTransfer);
        //remove the bike from p1
        p1->removeBike(0);
    }

}

/**
*
*
* @param None

*@brief Outputs the places with each place no. of bikes
*
* @return None
*/
void Company::displayPlacesAndBikes() const {
    for(unsigned int i = 0; i < places.size(); i++) {
        cout << places.at(i)->getName() << " -- " << places.at(i)->getNumBikes() << " bikes" << endl;
    }
}

/**
*
*
* @param None

*@brief Outputs all the company's (active) bikes
*
* @return None
*/
void Company::displayAllBikes() const {
    for(unsigned int i = 0; i < places.size(); i++) {
        for(unsigned int j = 0; j < places.at(i)->getBikes().size(); j++) {
            cout << "ID: " << places.at(i)->getBikes().at(j)->getID() << " | Type: " << places.at(i)->getBikes().at(j)->getTypeInString() << endl;
         }
    }
}

/**
*
*
* @param Place* p1 - place to add

*@brief Adds the given place to the company's places vector
*
* @return None
*/
void Company::addNewPlace(Place* p1) {
    places.push_back(p1);
}

/**
*
*
* @param Bike* b1 - bike to add

*@brief Adds the given Bike to the company's bikes vector
*
* @return None
*/
void Company::addNewBike(Bike* b1) {
    bikes.push_back(b1);
}

//STORE MANAGEMENT

/**
 * @brief "Buys" a bike from a BikeStore, decrementing in the stock of the number of bikes of the type that was just purchased
 *
 * @return True if the purchase was made, false if not
 */
bool Company::buyBike(string storeName, unsigned int type){

	bool exists = false;
	stack<BikeStore> aux;
	unsigned int bikeID;

	while(!stores.empty()){

		BikeStore b = stores.top();

		if(b.getName() == storeName){
			b.changeStock(type, 1);
			exists = true;
		}

		aux.push(b);
		stores.pop();
	}

	while(!aux.empty()){
		stores.push(aux.top());
		aux.pop();
	}


	if(exists == false){
		cout << "\nThere is no store with such name, please try again!" << endl;
		return false;
	}

	return true;
}

/**
 * @brief Allows the client to rate the store.
 *
 * @return void
 */
void Company::rateStore(unsigned int input, string storeName){

	stack<BikeStore> aux;

	while(!stores.empty()){

		BikeStore b = stores.top();

		if(b.getName() == storeName){
			b.changeReputation(input);
		}

		aux.push(b);
		stores.pop();
	}

	while(!aux.empty()){
		stores.push(aux.top());
		aux.pop();
	}

}

/**
 * @brief Increments by 20 all types of bikes in all stores
 *
 * @return void
 */
void Company::reStockAllStores(){

	stack<BikeStore> aux;
	vector <typeOfBike> typesForSale;

	while(!stores.empty()){

		BikeStore b = stores.top();
		typesForSale = b.getTypesForSale();

		for(unsigned int i = 0; i < typesForSale.size(); i++){
			b.reStock(typesForSale.at(i));
		}

		aux.push(b);
		stores.pop();

	}

	while(!aux.empty()){
		stores.push(aux.top());
		aux.pop();
	}

}

//GETTERS

unsigned int Company::getCurrentMaxPlaceID() const {

    int currMax = 0;
    for(int i = 0; i < places.size(); i++){
        if(places.at(i)->getID() > currMax) {
            currMax = places.at(i)->getID();
        }
    }

    return currMax;

}

unsigned int Company::getCurrentMaxBikeID() const {

    int currMax = 0;
    for(int i = 0; i < bikes.size(); i++){
        if(bikes.at(i)->getID() > currMax) {
            currMax = bikes.at(i)->getID();
        }
    }

    return currMax;

}

/**
*
* @param type - the type of bike requested
* @param position - the position where the user is
*
*@brief Returns the vector of Places near of where the User is that has the 'amount' amount of Bikes of the requested type
*
* @return places
*/
const vector<Place *> Company::getNearestPlacesWithBike(typeOfBike t, Position p, int amount) const {
	vector<Place *> places = getPlaces();
	vector<Place *> result;
	for (int i = 0; i < places.size(); i++) {
		Place* place = places[i];
		vector<Bike*> availableBikesOfType = place->getBikeOfType(t);
		if (availableBikesOfType.size() >= amount) {
			result.push_back(place);
		}
	}
	std::sort(result.begin(), result.end(), Place::compareByDistanceToPoint(p));
	return result;
}


//BIKE PARTS
void Company::removePart(bikePart bp) {
    this->bikeParts.remove(bp);
}

void Company::addPart(bikePart bp) {
    this->bikeParts.insert(bp);
}




/**
*
*
* @param None
* @brief Displays all the broken bikes on the screen, as well as scrapped bikes
*
* @return None
*/
void Company::displayBrokenBikes()  {

    if(brokenBikes.empty()) throw utilities::NoBrokenBikes();
    bikeScrapping::const_iterator it;
    int scrappedCounter = 0, nBikes = 0;
    for (it = brokenBikes.begin(); it != brokenBikes.end(); ++it) {
        if((*it)->getState() == broken) {
            if((*it)->getScrappingDate().getTotalMinutes() == 0) {//Not scrapped
                cout << (*it)->getID() << " -- NOT SCRAPPED YET.";
            }
            else {
                cout << (*it)->getID() << " -- Scrapped on: ";
                (*it)->getScrappingDate().displayTime();
                scrappedCounter++;
            }

            nBikes++;
            cout << endl;
        }
    }

    if(scrappedCounter == nBikes) throw utilities::AllBikesScrapped();

}

/**
*
*
* @param bike - bike to scrap
* @brief scraps a bike from the "scrapyard"
*
* @return None
*/
void Company::scrapeBike(Bike* bike, Time scrappingDate) {

    if(brokenBikes.empty()) throw utilities::NoBrokenBikes();

    bikeScrapping::const_iterator bikeIt = brokenBikes.find(bike);

    brokenBikes.erase(bikeIt);



    bike->setState(broken);
    bike->setScrappingDate(scrappingDate);

    brokenBikes.insert(bike);


}

/**
*
*
* @param bike - bike to scrap
* @brief Sends a bike to the "scrapyard"
*
* @return None
*/
void Company::sendToScrapyard(Bike* bike) {

    bool bikeFound=false;;

    for(int i = 0; i < places.size(); i++) {
        for(int j = 0; j < places.at(i)->getBikes().size(); j++) {
            if(places.at(i)->getBikes().at(j) == bike) {
                places.at(i)->removeBike(j);
                bikeFound = true;
                break;
            }
            if (bikeFound) break;
        }
    }

    bike->setState(broken);
    bike->setScrappingDate(Time(0));
    brokenBikes.insert(bike);

}

/**
*
*
* @param bike - bike to remove
* @brief removes a bike from the "scrapyard"
*
* @return None
*/
void Company::removeFromScrapyard(Bike* bike) {

    if(brokenBikes.empty()) throw utilities::NoBrokenBikes();

    bikeScrapping::const_iterator bikeIt = brokenBikes.find(bike);

    brokenBikes.erase(bikeIt);


}


//SAVE IN THE FILES

/**
 * @param None
 *
 * @brief Saves the Users info in the Client File before the program closes
 *
 * @return None
 */
void Company::saveUsers(){

	ofstream out_stream;
	string userFileName = this->getClientsFileName();

	out_stream.open(userFileName);

	for (unsigned int i = 0; i < this->usersAtTheMoment.size(); i++){

        //will become true if the function writes something(if the user is basic)
        bool isBasic = usersAtTheMoment.at(i)->writeUserInfo(out_stream); //writeUserInfo only actually outputs the info of basicUsrs, this way premiumUsrs are not duplicated on the file

        //the next code block ensures that the last line of the document will not have a \n so it doesn't bug
        if (isBasic){
            if(i == this->usersAtTheMoment.size() - 1) {
                //when it reaches the last element, it will verify it is the last entry to print. If so, it will not output a \n
                if(this->premiumUsers.size() == 0) break;
                out_stream << endl;

            }
            else{
                out_stream << endl;
            }
        }
	}


	for (unsigned int i = 0; i < this->premiumUsers.size(); i++){

		out_stream << premiumUsers.at(i)->getID() << endl;
		out_stream << premiumUsers.at(i)->getName() << endl;
		out_stream << premiumUsers.at(i)->getEmail() << endl;
		out_stream << premiumUsers.at(i)->getAdress() << endl;
		out_stream << premiumUsers.at(i)->getPhone() << endl;
		out_stream << premiumUsers.at(i)->getNIF() << endl;
		out_stream << premiumUsers.at(i)->getFavouriteTypeInString() << endl;
		out_stream << premiumUsers.at(i)->getPassword() << endl;
		out_stream << (premiumUsers.at(i)->getIsUsing() ? premiumUsers.at(i)->getBike()->getInitialTime().getTotalMinutes() : 0) << endl; //if isUsing, write the startTime in Minutes, otherwise write 0
		out_stream << premiumUsers.at(i)->getAmountToPay()<< endl;


		if(i+1 != this->premiumUsers.size()){
			if(premiumUsers.at(i)->getIsUsing() == false){
				out_stream << 0 << endl;
			}
			else
				out_stream << premiumUsers.at(i)->getBike()->getID() << endl;
		}
		else{
			if(premiumUsers.at(i)->getIsUsing() == false){
				out_stream << 0;
			}
			else
				out_stream << premiumUsers.at(i)->getBike()->getID();
		}

	}

	out_stream.close();
}

/**
 * @param None
 *
 * @brief Saves the Bikes info in the Bike File before the program closes
 *
 * @return None
 */
void Company::saveBikes(){

	ofstream out_stream;
	string bikeFileName = this->getBikesFileName();

	out_stream.open(bikeFileName);

	for (unsigned int i = 0; i < places.size(); i++){

        if(i != 0 && places.at(i)->getNumBikes() > 0) out_stream << endl;

		for (unsigned j = 0; j < places.at(i)->getNumBikes(); j++){

			out_stream << this->places.at(i)->getBikeInVec(j)->getTypeInString() << endl;		// type of bike
			out_stream << this->places.at(i)->getBikeInVec(j)->getID() << endl;					// bike's ID

			if(j+1 == places.at(i)->getNumBikes()){
				out_stream << this->places.at(i)->getID(); // If it's not occupied then it's the Place ID that goes to the File
			}
			else {
				out_stream << this->places.at(i)->getID() << endl;
			}
		}
	}

	if(usersAtTheMoment.size() != 0) out_stream << endl;

    for(unsigned int j = 0; j < usersAtTheMoment.size(); j++){

        out_stream << usersAtTheMoment.at(j)->getBike()->getTypeInString() << endl;		// type of bike
        out_stream << usersAtTheMoment.at(j)->getBike()->getID() << endl;				// bike's ID

        if(j == usersAtTheMoment.size()-1){		// If it's the last user's bike to save
            out_stream << -1;
        }
        else
            out_stream << -1 << endl;
    }

	out_stream.close();
}

/**
 * @param None
 *
 * @brief Saves the Company and Places info in the Company File before the program closes
 *
 * @return None
 */
void Company::saveCompanyNameAndPlaces(){

	ofstream out_stream;
	string companyFileName = this->getCompanyFileName();

	out_stream.open(companyFileName);

	out_stream << this->getCompanyName() << endl;				// Save the company Name

	for (unsigned int i = 0; i < places.size(); i++){			// For each of the Company places

		out_stream << places.at(i)->getName() << endl;			// Save the name
		out_stream << places.at(i)->getID() << endl;			// Save the ID
		out_stream << places.at(i)->getPos().getX() << endl;	// Save the Position (x coordinate)

		if(i+1 != this->places.size())
			out_stream << places.at(i)->getPos().getY() << endl;	// Save the Position (y coordinate)
		else
			out_stream << places.at(i)->getPos().getY();
	}

    out_stream.close();
}

/**
 * @brief Saves in the bike parts' file all the parts' information
 *
 * @return void
 */
void Company::saveParts() {
	  ofstream out_stream;
	  string fileName = getBikePartsFileName();
	  out_stream.open(fileName);
	  string bikePartsFileName = this->getBikePartsFileName();
	  BSTItrIn<bikePart> it(bikeParts);
	  bool flag = false;

	  while (!it.isAtEnd()) {
	   if (flag) out_stream << "\n";
	   else flag = true;
	        bikePart bp = it.retrieve();
	        out_stream << bp.getName() << endl;
	        out_stream << bp.getSupplier() << endl;
	    out_stream << bp.getPrice();
	        it.advance();
	    }
	    out_stream.close();
}

/**
 * @brief Converts an int representing a Bike Type to a string with the type's name
 *
 * @return The type's name
 */
string Company::typeToString(unsigned int type){
	if(type == 0)
		return "urban";
	else if(type == 1)
		return "urbanSimple";
	else if(type == 2)
		return "race";
	else
		return "child";
}

/**
 * @brief Saves in the store's file all the stores information
 *
 * @return void
 */
void Company::saveStores(){

	ofstream out_stream;
	string storesFileName = this->getStoresFileName();

	out_stream.open(storesFileName);

	vector<typeOfBike> types;
	vector <pair<typeOfBike, unsigned int>> stock;

	while(!stores.empty()){

		out_stream << stores.top().getName() << endl;
		out_stream << stores.top().getReputation() << endl;

		types = stores.top().getTypesForSale();

		for(unsigned int i = 0; i < types.size(); i++){
			out_stream << typeToString(types.at(i)) << endl;
		}

		out_stream << "." << endl;

		stock = stores.top().getStock();

		for(unsigned int i = 0; i < stock.size(); i++){
			out_stream << typeToString(stock.at(i).first) << endl;
			out_stream << stock.at(i).second << endl;
		}

		if(stores.size() > 1){
			out_stream << "." << endl;
		}

		else
			out_stream << ".";

		stores.pop();
	}

}

/**
 * @param None
 *
 * @brief Saves the Broken Bikes info File before the program closes
 *
 * @return None
 */
void Company::saveBrokenBikes(){

	ofstream out_stream;
	string fileBrokenBikes = this->getBrokenBikesFileName();

	out_stream.open(fileBrokenBikes);


	if(brokenBikes.empty()) return;
    bikeScrapping::const_iterator it;
    for (it = brokenBikes.begin(); it != brokenBikes.end(); ++it) {

        out_stream << (*it)->getTypeInString() << endl;
        out_stream << (*it)->getID() << endl;
        out_stream << (*it)->getScrappingDate().getTotalMinutes();

        bikeScrapping::const_iterator oldIt = it;
        if((++it) != brokenBikes.end()) out_stream << endl;
        it = oldIt;
    }


	out_stream.close();
}



