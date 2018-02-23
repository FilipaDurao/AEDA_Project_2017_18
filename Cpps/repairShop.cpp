//
// Created by henrique on 19-12-2017.
//

#include "repairShop.h"

bikePart::bikePart(string name, string supplier, float price) :
        name(name),
        supplier(supplier) {
    this->lastPrice = (float) ((int) (price * 100)) / 100;
}

/**
 * @param price - last purchase's price
 *
 * \brief Sets last price for given part entry
 *
 * @return none
 */
void bikePart::setPrice(float price) {
    this->lastPrice = price;
};

/**
 * @param none
 *
 * \brief returns part's name
 *
 * @return string name
 */
string bikePart::getName() const {
    return this->name;
}

/**
 * @param none
 *
 * \brief returns part's supplier
 *
 * @return string supplier
 */
string bikePart::getSupplier() const {
    return supplier;
}

/**
 * @param none
 *
 * \brief returns part's last purchase's price
 *
 * @return float price
 */
float bikePart::getPrice() const {
    return this->lastPrice;
}

bool operator<(const bikePart &bp1, const bikePart &bp2) {
    if (bp1.getName() != bp2.getName()) return bp1.getName() < bp2.getName();
    else return bp1.getPrice() < bp2.getPrice();
}

bool bikePart::operator==(const bikePart &bp2) {
    return this->name == bp2.getName() && this->getSupplier() == bp2.getSupplier();
}

bool bikePart::operator!=(const bikePart &bp2) {
    return !(*this == bp2);
}

void addPart() {

}





