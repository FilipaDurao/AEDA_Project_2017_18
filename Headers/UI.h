#ifndef UI_H_
#define UI_H_
#include "menu.h"
#include "Time.h"

// COMPANY
void menuCompanySettings(Company & c);
void displayUsersAtTheMoment(Company & c);
void displayCompanyInfo(Company & c);
void displayPremiums(Company & c);
void reallocateCompanyBikes(Company & c);
void addNewPlace(Company & c);
void addNewBike(Company & c);
void displayBrokenBikes(Company & c);
void scrapeBike(Company & c);
void sendToScrapyard(Company & c);
void removeFromScrapyard(Company & c);

// BASIC USER
void menuEnterBasicUsr(Company & c);
void basicRequestBike(Company & c);
void basicReturnBike(Company & c);

// PREMIUM USER
void menuLoginPremiumUsr(Company & c);
void menuLogoutPremiumUsr(Company & c);
void menuUserArea(Company & c);
void menuPremiumUsr(Company & c);
void newPremiumUsr(Company & c);
void premiumRequestBike(Company & c);
void premiumReturnBike (Company & c);
void premiumUserLogin(PremiumUsr*&, Company & c);
void payDebt(Company &c);

// BIKE STORES
void menuBikeStores(Company & c);
void displayTopFiveStores(Company & c);
void displayAllStores(Company & c);
void displayStoresWithType(Company & c);
void displayStoresWithStock(Company & c);
void buyBikesFromBest(Company & c);
void buyBikesFromStore(Company & c);
void reStockStores(Company & c);

// BIKE PARTS
void menuBikeParts(Company &c);
void displayBikeParts(Company &c);
void buyBikePart(Company &c);
void getCheapestBikePart(Company &c);
void removeBikePart(Company &c);
void addBikePart(Company &c);
void getCheapestBikePart(Company &c);
void removeBikePart(Company &c);
void addBikePart(Company &c);
string inputBikePartName(Company &c);
string inputSupplierForPart(Company &c, string name);

// OTHERS
void exitProgram(Company &c);
bool isNumber(string input);
void printBikeStore(BikeStore b);
vector<BikeStore> getStoresWithType(Company & c, unsigned int t);
vector<BikeStore> getStoresWithStock(Company & c, unsigned int quantity, unsigned int typeRequested);
void printSatisfaction();
string typeToString(typeOfBike type);


#endif // UI_H_
