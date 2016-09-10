#ifndef CARTVECTOR_H
#define CARTVECTOR_H
#include <iostream>

class CartVector {

 public:
  
  // the x and y displacement values of the vector
  double x;
  double y;
  
  // default constructor initializes x and y to 0.0
  CartVector();
  // sets x and y to in_x and in_y
  CartVector(double , double);

};

CartVector operator*(CartVector , double);

CartVector operator/(CartVector , double);

// overloads stream output to produce vector formatted as <x, y>
std::ostream& operator<<(std::ostream& , CartVector);




#endif
