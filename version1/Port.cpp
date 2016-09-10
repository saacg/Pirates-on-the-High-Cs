#include <iostream>
#include "GameObject.h"
#include "CartPoint.h"
#include "Port.h"


using namespace std;

// class derived from GameObject, contains supplies for sailors

// default constructor 
Port::Port():GameObject('P', 0){
  state = 'f';
  inventory = 500;
  
  cout << "Port default constructed" << endl;
}

// constructor initializes member variables
Port::Port(int in_id, CartPoint in_loc):GameObject('P', in_id, in_loc){
  state = 'f';
  inventory = 500;

  cout << "Port constructed" << endl;
} 

// destructor, prints out desctruction receipt
Port::~Port(){
  cout << "Port destructed." << endl;
}

// returns true if the port holds no more supplies
bool Port::is_empty(){

  if (inventory == 0){
    return true;
  }

  else {
    return false;
  }
}

// checks if the object has enough supplies to satisfy the amount requested (default value set to 50), if it does, returns the requested amount, if not, returns what it can
// updates quantity of supplies 
double Port::provide_supplies(double amount_to_provide){

  if (inventory >= amount_to_provide){
    inventory -= amount_to_provide;
    return amount_to_provide;
  }
  
  else {
    amount_to_provide = inventory;
    inventory = 0;
    return amount_to_provide;
  }
}

// checks if object is newly empty, if so it changes state and prints out a change state message
bool Port::update(){
  
  if(inventory == 0 && state != 'e'){
    state = 'e';
    display_code = 'p';
    cout << "Port " << get_id() << " has been depleted of supplies" << endl;
    return true;
  }

  else {
    return false;
  }
}

// prints out status of object
void Port:: show_status(){
  cout << "Port Status: " << this->display_code << " with ID " << get_id() << " at location " << this->location 
       << " containing supplies " << inventory << endl;
}

