#pragma once
#include <vector>
#include <string>
#include "Company.h"

using namespace std;

//set menuFunctionPtr as a pointer for a function like void(Company &e);
typedef void(*menuFunctionPtr)(Company &c);

//function to create a menu
void createMenu(string menuTitle, vector<pair<string, menuFunctionPtr>> menuItems, Company &c);

//asks the user to press any key to exit the function
void closeFunction();
void closeFunction(bool showMsg);


