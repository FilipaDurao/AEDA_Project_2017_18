#include "Position.h"


/**
 *  @param x - x coordinate
 *  @param y - y coordinate
 *
 *  \brief Constructor for position class. X and Y are values in 2d space.
 *
 *  @return None
 */
Position::Position(int x, int y):
    x(x), y(y)
{}

/**
 *  @param None
 *
 *  \brief Returns the X value for this position
 *  
 *  @return int x
 */
const int Position::getX() const {
    return this->x;
}

/**
 * @param None
 *
 * \brief Returns the Y value for this position
 *
 *  @return y
 */
const int Position::getY() const {
    return this->y;
}

/**
 *  @param secondPosition - the Position we are subtracting to our object
 *
 *  \brief Subtracts two points in 2d space
 *
 *  @return resulting Position
 */
Position Position::operator-(Position pos2){
    Position result ( (this->getX()) - (pos2.getX()), (this->getY()) - (pos2.getY())  );
    return result;
}

/**
 *  @param secondPosition - the Position we are adding to our object
 *
 *  \brief Adds two points in 2d space. Returns the resulting position.
 *
 *  @return Position
 */
Position Position::operator+(Position pos2){
    Position result( (this->getX()) + (pos2.getX()), (this->getY()) + (pos2.getY()));
    return result;
}

/**
 *   @param secondPosition - the Position we are calculating the distance from
 *
 * \brief Returns distance between 2 points. Returns the resulting position.
 *
 *  @return distance
 */
const double Position::getDistance(Position pos2) const{
    return sqrt(pow( (double)(pos2.getX() - this->getX()) ,2) + pow( (double)(pos2.getY() - this->getY()) ,2));
}
