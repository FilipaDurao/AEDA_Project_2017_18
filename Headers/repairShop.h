//
// Created by henrique on 19-12-2017.
//

#ifndef PROJETO_REPAIRSHOP_H
#define PROJETO_REPAIRSHOP_H

#include "BST.h"

class bikePart {
    string name;
    string supplier;
    float lastPrice;
public:
    bikePart(string name, string supplier, float price);

    void setPrice(float newPrice);

    string getName() const;

    string getSupplier() const;

    float getPrice() const;

    friend bool operator<(const bikePart &bp1, const bikePart &bp2);

    bool operator==(const bikePart &bp2);

    bool operator!=(const bikePart &bp2);

};

#endif //PROJETO_REPAIRSHOP_H
