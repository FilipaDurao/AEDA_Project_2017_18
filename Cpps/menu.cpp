#include "menu.h"
#include "utilities.h"
#include <iostream>
#include <string>

using namespace std;




/**
 * @param None
 *
 * \brief Asks the user to press any key to exit the function
 *
 * @return None
 */
void closeFunction() {
    cin.clear();
    cin.ignore(1000, '\n');
	cout << "\n\n\n\nPress ENTER to quit.";

	int caracters = getchar();

	if(caracters == 10)		// if ENTER is pressed
		return;
	else
		cin.ignore(1000, '\n');
}

/**
 * @param showMsg - true to show "press to close" msg, false to ommit it
 *
 * \brief Exit the menu function
 *
 * @return None
 */
void closeFunction(bool showMsg) {
  if(showMsg) cout << "\n\n\n\nPress ENTER to quit.";

  int caracters = getchar();

  if(caracters == 10)    // if ENTER is pressed
    return;
  else
    cin.ignore(1000, '\n');
}


/**
 * @param menuTitle - the title of the menu
 * @param menuItems - the menu Items and the pointers to the functions they call
 * @param &Company
 *
 * \brief Creates a menu
 *
 * @return menu
 */
void createMenu(string menuTitle, vector<pair<string, menuFunctionPtr>> menuItems, Company &c) {
	while (1) { //show menu until it has quit
		int selectedItem = -1;

		//CLEAR TERMINAL

		cout << "\n ------ " << menuTitle << " ------\n  _\n |\n"; //displays the title of the menu
		for (int i = 0; i < menuItems.size(); i++) {
			cout << " | " << i + 1 << " - " << menuItems[i].first << "\n |\n"; //displays each menu item with an identifier (i) which is: the index of the item + 1
		}
		cout << " | 0 - Back\n |_\n\n----------------------------------------------- \n\n"; //displays back option

		//sets the error msg
		string errorMsg = "Invalid Input. Insert a value beetween 0 and " + to_string(menuItems.size()) + "\n";

		//Ask for input
		cout << "Please insert a value beetween 0 and " + to_string(menuItems.size()) + "\n";

		//Receive input
		selectedItem = utilities::getUnsignedIntInput(0, menuItems.size() + 1, errorMsg); //checks for a valid input

		if (selectedItem == 0) {
			break; //exit if user has inserted a 0
		} else {
			menuItems[selectedItem - 1].second(c); //executes function corresponding to the selected item
		}

	}
}
