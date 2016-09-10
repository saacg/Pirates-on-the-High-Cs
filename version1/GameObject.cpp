#include <iostream>
#include <cmath>
#include "GameObject.h"
#include "CartPoint.h"
#include "Port.h"
#include "Dock.h"
#include "Sailor.h"

using namespace std;

// class is the base class for all game objects, contains all common members
// abstract class (see header file)

// constructor initializes display code and id number, uses the default CartPoint destructor to set the location to (0, 0)
GameObject::GameObject(char in_code, int in_id){

  CartPoint p1;
  display_code = in_code;
  id_num = in_id;
  location = p1;

  cout << "GameObject default constructed" << endl;

}

// constructor initializes display code, id number, and location to passed in values
GameObject::GameObject(char in_code, int in_id, CartPoint in_loc){

  display_code = in_code;
  id_num = in_id;
  location = in_loc;

  cout << "GameObject constructed" << endl;
}


// destructor prints out destruction receipt
// virtual function so derived classes can call their own 
GameObject::~GameObject(){
  cout << "GameObject destructed" << endl;
}


// getter function for location CartPoint
CartPoint GameObject::get_location(){

  return (this->location);
}

// getter function for id number
int GameObject::get_id(){

  return (this->id_num);
}

// outputs information currently contained in the instance of the class
// virtual function so derived classes can call their own
void GameObject::show_status(){

  cout << display_code << " with ID " << id_num << " at location " << location << "." << endl;

}

// inserts its values into the grid array in order to be plotted
// if there is already an object in that location, changes the array values to '*' and ' '
void GameObject::drawself(char* grid){
  if (*grid == '.'){
    *grid = this->display_code;
    *(grid + 1) = static_cast<char>(this->get_id() + 48);
  }
  else {
    *grid = '*';
    *(grid + 1) = ' ';
  }
}
