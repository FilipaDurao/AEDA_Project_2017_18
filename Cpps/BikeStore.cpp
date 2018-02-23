#include "BikeStore.h"

/**
 * @brief Constructor of BikeStore objects
 *
 * @param name - name of the store
 * @param reputation - reputation of the store
 * @param stock - the type of bikes it sells associated with the quantity of those bikes available
 * @param typesForSale - all the types that the store sells
 *
 * @return BikeStore object
 */
BikeStore::BikeStore(string name, int reputation, vector <pair<typeOfBike, unsigned int>> stock, vector <typeOfBike> typesForSale): name(name), stock(stock), typesForSale(typesForSale) {
	this->reputation = reputation;
}

BikeStore::~BikeStore() {}


// GETTERS

/**
 * @brief Returns the name of the store
 *
 * @return name
 */
string BikeStore::getName() const{
	return name;
}

/**
 * @brief Returns the reputation of the store
 *
 * @return reputation
 */
int BikeStore::getReputation() const{
	return reputation;
}

/**
 * @brief Returns the stock of the store
 *
 * @return stock
 */
vector <pair<typeOfBike, unsigned int>> BikeStore::getStock() const{
	return stock;
}

/**
 * @brief Returns the types for sale on the store
 *
 * @return typesForSale
 */
vector <typeOfBike> BikeStore::getTypesForSale() const{
	return typesForSale;
}


// SETTERS

/**
 * @brief Changes the reputation of the store based on the buyer's insight
 *
 * @return void
 */
void BikeStore::changeReputation(int value){
	if(value == 1){
		reputation -= 2;
	}
	else if(value == 2){
		reputation -= 1;
	}
	else if(value == 4){
		reputation += 1;
	}
	else if(value == 5){
		reputation += 2;
	}
}

/**
 * @brief Decrements the stock of the bikes of type 'type' by 'numberOfBikes'
 *
 * @return void
 */
void BikeStore::changeStock(unsigned int type, unsigned int numberOfBikes){

	for(unsigned int i = 0; i < stock.size(); i++){
		if(stock.at(i).first == type){
			stock.at(i).second -= numberOfBikes;

			if(stock.at(i).second < 0){
				stock.at(i).second = 0;
			}

			break;
		}
	}

}

/**
 * @brief Increments by 20 the stock of every type of bike available in the store
 *
 * @return void
 */
void BikeStore::reStock(unsigned int type){

	for(unsigned int i = 0; i < stock.size(); i++){
		if(stock.at(i).first == type){
			stock.at(i).second += 20;
			break;
		}
	}

}

// OTHERS

/**
 * @brief Operator < so the insertion on the priority_queue of BikeStores 'stores' in Company is correct. A store is < than another is its reputation is <. In case of a draw, alfabetical order prevails
 *
 *
 * @return true or false depending on the reputation and name of the stores
 */
bool BikeStore::operator<(const BikeStore &b1) const{

	if(reputation < b1.reputation)
		return true;

	else if(reputation > b1.reputation)
		return false;

	else{
		if(name > b1.name)
			return true;
		else
			return false;
	}
}

