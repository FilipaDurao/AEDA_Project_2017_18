#ifndef COMPANY_H_
#define COMPANY_H_

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <time.h>
#include <queue>

#include "Time.h"
#include "Bike.h"
#include "User.h"
#include "BasicUsr.h"
#include "PremiumUsr.h"
#include "Place.h"
#include "BikeStore.h"
#include "repairShop.h"


using namespace std;

class User;

class Company{
private:
	string name;
	const string fileNameCompany, fileNameClients, fileNameBikes, fileNameStores, fileNameParts, fileNameScrapyard;    // Save the name of the file so we can later write on it
	vector <Bike*> bikes;															// All the bikes owned by the company
	vector <PremiumUsr*> premiumUsers;							 					// Premium users are always the same, they are kept in this vector.
	vector <User*> usersAtTheMoment;												// These are the users that at the moment have a bike. Includes the premium users.
	vector <Place*> places;															// All the places in which the company has bikes in
	bikeScrapping brokenBikes;                                     					// hashTable with the broken bikes
	priority_queue <BikeStore> stores;												// Priority queue with the bike stores
	BST<bikePart> bikeParts;

public:
	Company(const string &fileNameCompany, const string &fileNameClients, const string &fileNameBikes,
			const string &fileNameStores, const string &fileNameParts, const string &fileNameScrapyard);
	virtual ~Company();

	//VECTOR WORKS
	void addPremiumToPremiumVec(PremiumUsr* premium);
	void addPremiumToUsersVec(PremiumUsr* premium);
	void removePremiumFromUsersVec(PremiumUsr* premium);
	void removeBasicFromUsersVec(BasicUsr* basic);
	void addBasicToUsersVec(BasicUsr* basic);

	//DISPLAYS
	void displayCompanyInfo() const;
	void displayUsersAtTheMoment() const;
	void displayPremiumUsers();
	void displayPlaces() const;
	void displayBikes() const;
	void displayAllBikes() const;
	void displayPlacesAndBikes() const;
	void displayBrokenBikes();

	//GETTERS
	const string getCompanyName() const;
	const string getCompanyFileName() const;
	const string getClientsFileName() const;
	const string getBikesFileName() const;
	const string getStoresFileName() const;
	const string getBikePartsFileName() const;
	const string getBrokenBikesFileName() const;
	unsigned int getNumBikes() const;
	unsigned int getNumPremiumCl() const;
	unsigned int getNumMomentUsr() const;
	const vector<Place *> getPlaces() const;
	priority_queue <BikeStore> getStores() const;
	PremiumUsr* getPremiumUserByID(unsigned int ID) const;
	BasicUsr* getBasicUserAtTheMomentByID(unsigned int ID) const;
	unsigned int getCurrentMaxPlaceID() const;
	unsigned int getCurrentMaxBikeID() const;
	Bike* getBikeByID(unsigned int id);
	Bike* getBrokenBikeByID(unsigned int id);



	BST<bikePart> getBikeParts() const;

	vector<PremiumUsr*> getAllPremiums();
	vector<Bike*> getAllBikes() const;

	//LOGIN SYSTEM
	void getPremiumUsrByEmail(PremiumUsr*& user, string email);
	const bool verifyPassword(PremiumUsr*& user, string password) const;
	bool createPremiumUsr(string name, string email, string adress, string phone, string NIF, string type, string password);
	BasicUsr* createBasicUsr();


	//GET SPECIFIC BIKES
	const vector<Place *> getNearestPlacesWithBike(typeOfBike t, Position p) const;
	const vector<Place *> getNearestPlacesWithBike(typeOfBike t, Position p, int amount) const;
    const string checkPw(PremiumUsr*& user, string password) const;

    //REALLOCATING BIKES
    void realocateBikes();
    void transferBikes(Place* p1, Place* p2, unsigned int nBikes);

    //COMPANY MANAGEMENT
    void addNewPlace(Place* p1);
    void addNewBike(Bike* b1);

	//BIKE PARTS
	void removePart(bikePart bp);
	void addPart(bikePart bp);

    //STORE MANAGEMENT
    bool buyBike(string storeName, unsigned int type);
    void rateStore(unsigned int input, string storeName);
    void reStockAllStores();

    //SCRAPYARD
    void scrapeBike(Bike* bike, Time scrappingDate);
	void sendToScrapyard(Bike* bike);
	void removeFromScrapyard(Bike* bike);


    //SAVE IN THE FILES
    void saveUsers();
    void saveBikes();
    void saveCompanyNameAndPlaces();
	void saveParts();
	//TODO this function below
	void saveStores();

	void saveBrokenBikes();

	string typeToString(unsigned int type);
};

//Exception to be thrown when an email doesn't exist in the database
class UnexistentEmail{
private:
    string email;
public:
    UnexistentEmail(string email);
    const string getEmail() const;
};

#endif /* COMPANY_H_ */
