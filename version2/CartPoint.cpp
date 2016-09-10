#include <iostream>
#include <cmath>
#include "CartPoint.h"
#include "CartVector.h" 
#include "GameObject.h"
#include "Port.h"
#include "Dock.h"
//#include "Sailor.h"

using namespace std;

// class represents set of cartesian coordinates to help keep track of the game objects

// default constructor
CartPoint::CartPoint(){

  x = 0.0;
  y = 0.0;

} 

// constructor initializes coordinates to passed in doubles
CartPoint::CartPoint(double in_x, double in_y){

  x = in_x;
  y = in_y;

}

// returns the Cartesian distance between the two objects
double cart_distance(CartPoint p1, CartPoint p2){


  double cartDistance = sqrt(pow((p1.x - p2.x), 2) + pow((p1.y - p2.y), 2));

  return cartDistance;
}

// compares the x and y values of the two objects, returns true if they are the same
bool cart_compare(CartPoint p1, CartPoint p2){

  if (p1.x == p2.x && p1.y == p2.y){
    return true;
  }

  else {
    return false;
  }

}

// overloads the << operator to be able to print out a CartPoint object formatted as (x, y)
ostream& operator<<(ostream& outPoint, CartPoint p1){

  outPoint << "(" << p1.x << ", " << p1.y << ")";

  return outPoint;
}

// overloads the + operator in order to be able to easily add CartPoints
CartPoint operator+(CartPoint p1, CartVector v1){

  CartPoint sumPoint((p1.x + v1.x), (p1.y + v1.y));
 
  return sumPoint;
}

bool operator==(CartPoint p1, CartPoint p2){
  if(cart_compare(p1, p2)){
    return true;
  }
  else {
    return false;
  }
}

// overloads the - operator to subract CartPoints and returns the difference as a CartVector
CartVector operator-(CartPoint minuendPoint, CartPoint subtrahendPoint){

  CartVector differenceVector((minuendPoint.x - subtrahendPoint.x), (minuendPoint.y - subtrahendPoint.y));

  return differenceVector;
}




