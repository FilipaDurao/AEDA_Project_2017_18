#include "User.h"

// CONSTRUCTORS

/**
 * @param startPlace - the Place where the ride starts
 * @param bike* - the Bike the User is using
 *
 * \brief Creates an User.
 * detailed This class is purely virtual, so this constructor is only used when connected to PremiumUsr or BasicUsr.
 * This constructor is used for Basic Users, because they only exist when they start an utilziation, therefore, they always have a start place and a bike.
 *
 * @return User
 */
User::User(Place *startPlace, Bike *bike){
	this->startPlace = startPlace;
	this->bike = bike;
}

/**
 * @param None
 *
 * \brief Creates an User.
 * detailed This class is purely virtual, so this constructor is only used when connected to PremiumUsr or BasicUsr.
 * This constructor is used for Premium Users, because they can exist without being using a bike right now, so they don't necessarily need to have a start place and a bike.
 *
 * @return User
 */
User::User(){
	this->bike = NULL;
	this->startPlace = NULL;
}

User::~User() {
	// TODO Auto-generated destructor stub
}


// GETTERS

/**
 * @param None
 *
 * \brief Returns the start Place of the user (where it began to use the bike).
 *
 * @return startPlace*
 */
Place* User::getStartPlace() const{
	return this->startPlace;
}

/**
 * @param None
 *
 * \brief Returns the bike the User is using (if it's using any).
 *
 * @return bike*
 */
Bike* User::getBike() const{
	return this->bike;
}

// SETTERS

/**
 * @param startPlace* - the Place where the ride starts
 *
 * \brief Sets the start place of the utilization.
 *
 * @return None
 */
void User::setStartPlace(Place *startPlace){
	this->startPlace = startPlace;
}

/**
 * @param bike* - the Bike the User is using
 *
 * \brief Sets the bike for the utilization.
 *
 * @return None
 */
void User::setBike(Bike *bike){
	this->bike = bike;
}
