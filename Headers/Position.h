#include <iostream>
#include <cmath>



class Position{
    int x,y;

    public:
    Position(int x, int y);
	const int getX() const;
	const int getY() const;
    Position operator-(Position pos2);
    Position operator+(Position pos2);
    const double getDistance(Position pos2) const;
	
};
