#include "Place.h"

/**
 * @param name - name of the Place
 * @param posX - X coordinate of the Place
 * @param posY - Y coordinate of the Place
 * @param ID - the ID of the Place
 *
 * \brief Creates a place where the company keeps the bikes.
 *
 * @rreturn Place
 */
Place::Place(string name, unsigned int posX, unsigned int posY, const unsigned int ID) : ID(ID), pos(Position(posX,posY)) {
	this->name = name;
}

Place::~Place() {
	// TODO Auto-generated destructor stub
}

/**
 * @param None
 *
 * \brief Returns the name of the Place.
 *
 * @return Name
 */
string Place::getName() const{
	return this->name;
}
/**
 * @param None
 *
 * \brief Returns the bikes of the Place.
 *
 * @return bikes
 */
vector<Bike*> Place::getBikes() const {

    return this->bikes;
}

/**
 * @param None
 *
 * \brief Returns the number of bikes in that place.
 *
 * @return Number of bikes in the place
 */
unsigned int Place::getNumBikes() const{
	return this->bikes.size();
}

/**
 * @param None
 *
 * \brief Returns the ID of a Place.
 *
 * @return ID
 */
const unsigned int Place::getID() const{
	return this->ID;
}

/**
 * @param bike* - the Bike that is to be added to the Place
 *
 * \brief Adds a bike* to the bikes vector.
 *
 * @return None
 */
void Place::addBike(Bike *bike){
	this->bikes.push_back(bike);
}


/**
 * @param index - index of the Bike in the Bikes vector
 *
 * \brief Returns a pointer to a bike available at the Place
 *
 * @return bike*
 */
Bike* Place::getBikeInVec(unsigned int index) const{
	return this->bikes.at(index);
}

/**
 * @param bike* - index of the Bike in the Bikes vector
 *
 * \breif Removes a bike from the vector of available bikes in the Place
 *
 * @return None
 */
void Place::removeBike(unsigned int index){
	this->bikes.erase(bikes.begin()+index-1);
}


/**
 * @param None
 *
 * @brief Returns the Position of the Place
 *
 * @return position
 */
Position Place::getPos() const{
	return pos;
}

/**
 * @param t - typeOfBike
 *
 * @brief Returns a vector of Bike pointers with all the Bikes of a certain Type available on the Place
 *
 * @return bikes
 */
const vector<Bike *> Place::getBikeOfType(typeOfBike t) const{

	vector<Bike*> result;

	for(unsigned int i = 0; i < bikes.size(); i++){
		if (bikes.at(i)->getType() == t){
			result.push_back(bikes.at(i));
		}
	}

	return result;
}

/**
 * @param bikeID
 *
 * @brief Returns a Bike in a Bikes vector in Place by it's ID. If it doesn't exist there, returns -1
 *
 * @return bike - Bike *
 */
int Place::getBikeInVecByID(int bikeID) const{

	for(unsigned int i = 0; i < bikes.size(); i++){
		if(bikes.at(i)->getID() == bikeID)
			return i;
	}

	return -1;
}

//AUXILIARES

/**
 * @param None
 *
 * @brief Displays a Place info
 *
 * @return None
 */
void Place::displayPlace(){
	cout << name << " (" << pos.getX() << ", " << pos.getY() <<  ") ";
}



string parseBikeType(Bike bike) {

    typeOfBike type = bike.getType();


    switch(type) {

    case urban:
        return "urban";
    case urbanSimple:
        return "urbanSimple";
    case race:
        return "race";
    case child:
        return "child";

    }
}


/**
 * @param None
 *
 * @brief Displays a Place's bikes' info
 *
 * @return None
 */
void Place::displayPlaceBikes() {
    for(int i = 0; i< bikes.size(); i++) {
        cout << "----BIKE----" <<endl;

        cout << "ID: " << bikes.at(i)->getID() << endl;
        cout << "Type: " << parseBikeType(*bikes.at(i)) << endl;
        cout << "Available: " << (bikes.at(i)->getAvailability() ? "Yes" : "No") << endl ;

        cout << "----------" << endl << endl;
    }
}











