#include "Bike.h"

unsigned int Bike::lastID = 0;

/**
 * @param type - the type of Bike
 * @param ID - the ID of the Bike
 *
 * \brief Creates a bike.
 *
 * @return Bike
 */
Bike::Bike(typeOfBike type, unsigned int ID): type(type), ID(ID){
	availability = true;
	state = good;
	scrappingDate = Time(0);

	if(ID > lastID){
		lastID = ID + 1;
	}
}

Bike::~Bike() {
	// TODO Auto-generated destructor stub
}


// GETTERS

/**
 * @param None
 *
 * \brief Returns the type of bike.
 *
 * @return type
 */
typeOfBike Bike::getType() const{
	return this->type;
}

/**
 * @param None
 *
 * \brief Returns the type of bike in a string
 *
 * @return type
 */
string Bike::getTypeInString() const{
	if(type == urban)
		return "urban";
	if(type == urbanSimple)
		return "urbanSimple";
	if(type == race)
		return "race";
	if(type == child)
		return "child";
}
/**
 * @param None
 *
 * \brief Returns the initial using time (on the bike).
 *
 * @return initialTime
 */
Time Bike::getInitialTime() const{
	return this->initialTime;
}

/**
 * @param None
 *
 * \brief Returns the availability of the Bike.
 *
 * @return availability
 */
bool Bike::getAvailability() const{
	return this->availability;
}

/**
 * @param None
 *
 * \brief Returns the ID of the Bike.
 *
 * @return ID
 */
unsigned int Bike::getID() const{
	return ID;
}

/**
 * @param None
 *
 * \brief Returns the state of the Bike.
 *
 * @return state
 */
bikeState Bike::getState() const {
    return state;
}

/**
 * @param None
 *
 * \brief Returns the state of the Bike.
 *
 * @return scrappingDate
 */
Time Bike::getScrappingDate() const {
    return scrappingDate;
}


// SETTERS

/**
 * @param initialTime - beginning of usage
 *
 * \brief Sets the initial using time of the bike.
 *
 * @return None
 */
void Bike::setInitialTime(Time initialTime){
	this->initialTime = initialTime;
}

/**
 * @param availability
 *
 * \brief Sets the availability of the bike.
 *
 * @return None
 */
void Bike::setAvailability(bool availability){
	this->availability = availability;
}

/**
 * @param state - new state
 *
 * \brief sets the state of the Bike.
 *
 * @return none
 */
void Bike::setState(bikeState state) {
    this->state = state;
}

/**
 * @param scrappingDate - date of the scrapping
 *
 * \brief sets the scrapping date of the Bike.
 *
 * @return none
 */
void Bike::setScrappingDate(Time scrappingDate) {
    this->scrappingDate = scrappingDate;
}










