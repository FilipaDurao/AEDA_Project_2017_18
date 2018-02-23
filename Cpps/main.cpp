#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "Company.h"
#include "UI.h"
#include "utilities.h"

using namespace std;

int main(){

	string fileNameCompany, fileNameClients, fileNameBikes, fileNameStores, fileNameParts, fileNameScrapyard;

    do{
		cout << "Please enter the name of the Company file.\n";
		cin >> fileNameCompany;

		cout << "Please enter the name of the Clients file.\n";
		cin >> fileNameClients;

		cout << "Please enter the name of the Bikes file.\n";
		cin >> fileNameBikes;

        cout << "Please enter the name of the Bike Stores file.\n";
        cin >> fileNameStores;

        cout << "Please enter the name of the Bike Parts file.\n";
        cin >> fileNameParts;

        cout << "Please enter the name of the Scrapyard file.\n";
        cin >> fileNameScrapyard;

    }	while(!utilities::checkFiles(fileNameCompany, fileNameClients, fileNameBikes, fileNameStores, fileNameParts, fileNameScrapyard));

//    fileNameBikes = "CompanyBikes.txt";
//    fileNameClients = "ClientFile.txt";
//    fileNameCompany = "CompanyFile.txt";
//    fileNameStores = "BikeStores.txt";
//    fileNameParts = "BikeParts.txt";
//    fileNameScrapyard = "Scrapyard.txt";


	Company rentABike(fileNameCompany, fileNameClients, fileNameBikes, fileNameStores, fileNameParts, fileNameScrapyard);

	createMenu(rentABike.getCompanyName() +  " -- MAIN MENU", {
			{"Company",       menuCompanySettings},
			{"Premium Users", menuPremiumUsr},
			{"Basic Users",   menuEnterBasicUsr},
			{"Bike Stores",   menuBikeStores},
			{"Bike Parts",    menuBikeParts}
	}, rentABike);

	exitProgram(rentABike);

	return 0;
}
