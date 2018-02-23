#include "utilities.h"
#include <iostream>
#include <string>




/**
 * @param errorMsg - error message to show (in case of bad input)
 *
 * \brief Returns an unsigned int inputed by the user, only when the correct type is inserted
 *
 * @return input
 */

unsigned int utilities::getUnsignedIntInput(string errorMsg) {

	unsigned int input;

	//ask for the first input
	cin >> input;
	cin.ignore(1000, '\n');

	//while the input is incorrect type, show error msg, clear buffer and ask for input again
	while (!cin.good()) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << endl << errorMsg << endl;
		cin >> input;
		cin.ignore(1000, '\n');
	}

	//return the valid input
	return input;

}

/**
 * @param start - number of first option
 * @param end - number of last option
 * @param errorMsg - error message to show (in case of bad input)
 *
 * \brief Returns an unsigned int inputed by the user, only when the correct type is inserted, and the value is within the range given [start, end[
 *
 * @return input
 */
unsigned int utilities::getUnsignedIntInput(unsigned int startLimit, unsigned int endLimit, string errorMsg) {

	unsigned int input;

	//ask for the first input
	cin >> input;


	//while the input is incorrect type (or not within range), show error msg, clear buffer and ask for input again
	while (!cin.good() || (input < startLimit || !(input < endLimit))) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << endl << errorMsg << endl;
		cin >> input;
	}


	//return the valid input
	return input;

}

/**
 * @param fileNameCompany - the Name of the Company file
 * @param fileNameClients - the Name of the Clients file
 * @param fileNameBikes - the Name of the Bikes file
 *
 * @brief Checks if the files given by the User are valid
 *
 * @return bool - true if the files are valid, false if not
 *
 */
bool utilities::checkFiles(const string &fileNameCompany, const string &fileNameClients, const string &fileNameBikes,
						   const string &fileNameStores, const string &fileNameBikeParts, const string &fileNameScrapyard) {

	ifstream check;

	// check if fileNameCompany is a valid file
	check.open(fileNameCompany);

	// If it isn't open, then return false
	if(!check.is_open())
		return false;

	check.close();

	// check if fileNameClients is a valid file
	check.open(fileNameClients);

	if(!check.is_open())
		return false;

	check.close();

	// check if fileNameBikes is a valid file
	check.open(fileNameBikes);

	if(!check.is_open())
		return false;

	check.close();

	// check if fileNameStores is a valid file
	check.open(fileNameStores);

	if (!check.is_open())
		return false;

	check.close();

	// check if fileNameBikePartss is a valid file
	check.open(fileNameBikeParts);

	if(!check.is_open())
		return false;

	check.close();

	// check if fileNameBikePartss is a valid file
	check.open(fileNameScrapyard);

	if(!check.is_open())
		return false;

	check.close();


	return true;
}
