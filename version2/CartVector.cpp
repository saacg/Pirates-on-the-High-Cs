#include <iostream>
#include <cmath>
#include "CartVector.h"
#include "CartPoint.h"

using namespace std;

// class represents a vector in the real plane (set of x and y displacements)

// default constructor
CartVector::CartVector(){

  x = 0.0;
  y = 0.0;

}

// constructor initializes CartVector values to passed in doubles
CartVector::CartVector(double in_x, double in_y){

  x = in_x;
  y = in_y;

}

// overloads * operator to return the product of a CartVector and a scalar as a new CartVector
CartVector operator*(CartVector v1, double d){
  
  CartVector scalarProductVector((v1.x * d), (v1.y * d));
 
  return scalarProductVector;
}

// overloads / operator to return the quotient of a CartVector by a scalar as a new CartVector
CartVector operator/(CartVector v1, double d){

  if (d == 0){
    return v1;
  }

  else {
    CartVector scalarQuotientVector((v1.x / d), (v1.y / d));
    return scalarQuotientVector;
  }
}

// overloads << operator to print out a CartVector object in the form <x, y>
ostream& operator<<(ostream& outputVector, CartVector v1){

  outputVector << "<" << v1.x << ", " << v1.y << ">";

  return outputVector;
}

