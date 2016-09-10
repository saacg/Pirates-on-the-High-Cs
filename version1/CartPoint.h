#ifndef CARTPOINT_H 
#define CARTPOINT_H
#include <iostream>
#include "CartVector.h"

class CartPoint {
 public:
  // the x value of the point
  double x;

  // the y value of the point
  double y;

  // default constructor - initializes x and y to 0.0
  CartPoint();

  // sets x and y to in_x and in_y
  CartPoint(double , double);
 
};

// returns the Cartesian (ordinary) distance between p1 and p2
double cart_distance (CartPoint , CartPoint );

// returns true if the x and y values of the two points are the same
bool cart_compare (CartPoint , CartPoint );

// overloads output operator to produce a point formatted (x, y)
std::ostream& operator<<(std::ostream& , CartPoint);

// overloads arithmetic operators
CartPoint operator+(CartPoint , CartVector);

CartVector operator-(CartPoint minuendPoint, CartPoint subtrahendPoint);


#endif
