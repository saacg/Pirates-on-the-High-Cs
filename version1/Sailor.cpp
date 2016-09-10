#include <iostream>
#include <cmath>
#include "GameObject.h"
#include "CartPoint.h"
#include "CartVector.h"
#include "Port.h"
#include "Dock.h"
#include "Sailor.h"

using namespace std;

// class derived from GameObject, represents character in the game

// default constructor
Sailor::Sailor():GameObject('S', 0){

  state = 'a';
  health = 25;
  size = 15;
  preSize = 15;
  hold = 100;
  cargo = 0;

  cout << "Sailor default constructed" << endl;
}

// constructor
Sailor::Sailor(int in_id, Dock* hideout):GameObject('S', in_id, hideout->get_location()){
  this->hideout = hideout;
  this->dock = hideout;
  this->state = 'h';
  this->health = 25;
  this->size = 15;
  this->preSize = 15;
  this->hold = 100;
  this-> cargo = 0;

  cout << "Sailor constructed" << endl;
}

// destructor
Sailor::~Sailor(){
  cout << "Sailor destructed." << endl;
}

// returns true if state has changed
// giant switch statement for all the states
bool Sailor::update(){
  bool returnUpdate;
  switch(this->state){
  case 'a': returnUpdate = false; break;
  case 's': 
    if (this->update_location()){
      this->state = 'a';
      returnUpdate = true;
      break; 
    }
    else {
      returnUpdate = false;
      break;
    }
  case 'o': 
    if (this->update_location()){
      this->state = 'l';
      returnUpdate = true;
      break;
    }
    else {
      returnUpdate = false;
      break;
    }			 
  case 'i':
    if (this->update_location()){
      this->state = 'u';
      returnUpdate = true;
      break;
    }
    else {
      returnUpdate = false;
      break;
    }
  case 'l':
    if (this->cargo == this->hold){
      this->state = 'a';
      cout << this->display_code << this->get_id() << ": My boat is filled up. Send me to a Dock to unload."
	   << " Dropping anchor" << endl;
      returnUpdate = true;
      break; 
    }
    else {
      double supplies = port->provide_supplies();
      if (supplies == 0){
	this->state = 'a';
	cout << this->display_code << this->get_id() << ": This Port has no more supplies for me."
	     << " Dropping anchor" << endl;
	returnUpdate = true;
	break;
      }
      else {
      double newCargo = this->cargo + supplies;
      this->cargo = newCargo > this->hold? this->hold: newCargo;
      cout << this->display_code << this->get_id() << ": My new cargo is " << this->cargo << endl;
      returnUpdate = false;
      break;
      }
    }
  case 'u':  
    if (dock->dock_boat(this)){
      this->state = 'd';
      if (this->cargo > 0){
	this->preSize = this->size;
	this->hold = this->hold + 20;
	this->size = this->size + 5;
	this->cargo = 0;
      }
      cout << this->display_code << this->get_id() << ": I am unloading at the dock" << endl;
      returnUpdate = true;
      break;
    }
    else {
      this->state = 't';
      cout << this->display_code << this->get_id();
      if (this->is_hidden()){
	cout << ": Help! My home dock is full" << endl;  // Based on some confusion about sample output 1, I was under the impression we would have to differentiate between the "hideout" being full or just another dock
      }                                                  // However, due to clarification, it appears we should just be returning "home dock" every time. I just made both return home dock because I did not want to tamper much
      else {                                             // with my already working and tested code, so that is why this check looks redundant. 
	cout << ": Help! My home dock is full" << endl;
      }
      returnUpdate = true;
      break;
    }
  case 'd': returnUpdate = false; break;
  case 'h':
    this->update_location(); 
    if (this->is_hidden()){
      this->state = 'a';
      returnUpdate = true;
      break;
    }
    else {
      returnUpdate = false;
      break;
    }
  case 't': returnUpdate = false; break;
  }

  return returnUpdate;
}

// getter function for size
double Sailor::get_size(){
  return size;
}

// getter function for preSize (in order to properly update berths)
double Sailor::get_preSize(){
  return preSize;
}

// getter function for cargo
double Sailor::get_cargo(){
  return cargo;
}

// prepares object to move to a new location
// calls setup destination function in order to set the new location
// changes state
void Sailor::start_sailing(CartPoint dest){
  setup_destination(dest);
  state = 's';
  cout << "Sailing " << get_id() << " to " << destination << endl;
  cout << display_code << get_id() << ": On my way" << endl; 
}

// prepares sailor to move to a port and take in supplies
// calls setup destination function to set the new location
// changes state
void Sailor::start_supplying(Port* destPort){
  port = destPort;
  setup_destination(port->get_location());
  state = 'o';
  cout << "Sailor " << this->get_id() << " supplying at Port " << port->get_id() << " and going to Port " << port->get_id()
       << endl;
  cout << this->display_code << this->get_id() << ": Supplies here I come!" << endl; 

}

// prepares the sailor to move to its hideout dock
// changes state
void Sailor::start_hiding(){
  setup_destination(this->hideout->get_location());
  this->state = 'h';
  cout << "Sailor " << this->get_id() << " hiding " << this->get_id() << endl;
  cout << this->display_code << this->get_id() << ": Off to hide" << endl;
}

// compares sailor's current location to that of its hideout and returns true if they are the same
bool Sailor::is_hidden(){
  if (cart_compare(this->get_location(), hideout->get_location())){
      return true;
    }

    else {
      return false;
    }
}

// prepares sailor to move to a dock and unload cargo
// changes state
void Sailor::start_docking(Dock* destDock){
  this->setup_destination(destDock->get_location()); 
  this->dock = destDock; 
  this->state = 'i';
  cout << "Sailor " << this->get_id() << " sailing to Dock " << dock->get_id() << endl;
  cout << this->display_code << this->get_id() << ": Off to Dock" << endl;
}

// causes sailor to stop whatever it is doing and remain stationary until directed otherwise
// changes state
void Sailor::anchor(){
 if (state == 'd'){
    this->dock->set_sail(this);
  }
  this->state = 'a';
  cout << "Stopping " << this->get_id() << endl;
  cout << this->display_code << this->get_id() << ": Dropping anchor" << endl;
}

// prints out status of object
void Sailor::show_status(){
  cout << "Sailor status: " << this->display_code << " with ID " << this->get_id() << " at location " << this->location;
  switch(this->state){
  case 'a': 
    if (this->is_hidden()){
      cout << " is anchored (and hiding). Has a size of: " << this->size << ", cargo of: " << this->cargo << ", hold of: "
	   << this->hold << ", and health of: " << this->health << endl; break;
    }
    else {
      cout << " is anchored. Has a size of: " << this->size << ", cargo of: " << this->cargo << ", hold of: "
	   << this->hold << ", and health of: " << this->health << endl; break;
    }
  case 'h': cout << " is going to hide at Dock " << this->hideout->get_id() << endl; break;
  case 's': cout << " Has a speed of: " << this->get_speed() << " and is heading to: " << this->destination << endl; break;
  case 'o': cout << " is outbound to Port: " << port->get_id() << " with a speed of " << this->get_speed() << endl; break;
  case 'i': cout << " is inbound to Dock: " << dock->get_id() << " with a speed of " << this->get_speed() << endl; break;
  case 'l': cout << " is supplying at Port " << port->get_id() << endl; break;
  case 'u': cout << " is unloading at Dock " << dock->get_id() << endl; break;
  case 'd': cout << " is docked at Dock " << dock->get_id() << endl; break;
  case 't': cout << " is in trouble " << this->get_id() << endl; break;
  }
}

// returns speed of sailor based on formula in assignment sheet
double Sailor::get_speed(){
  double speed = (size - (cargo * .1));
  return speed; 
}

// private member function, updates location while object is moving
// returns true when object arrives at destination
bool Sailor::update_location(){
  if (this->state == 'h'){
    this->destination = this->hideout->get_location();
  }
  double xDifference = abs(this->destination.x - this->location.x);
  double yDifference = abs(this->destination.y - this->location.y);
  if (xDifference <= abs( this->delta.x) && yDifference <= abs(this->delta.y)){
    this->location = this->destination;
    cout << this->display_code << this->get_id() << ": I'm there!" << endl;
    switch(this->state){
    case 'i': cout << this->display_code << this->get_id() << ": Starting to unload at a dock" << endl; break;
    case 'o': cout << this->display_code << this->get_id() << ": Starting to supply at a port" << endl; break;
    }
    return true;
  }
  else {
    this->location = (this->location + this->delta);
    cout << this->display_code << this->get_id() << ": Just keep sailing..." << endl;
    return false;
  }
}

// sets up destination for object to move to
void Sailor::setup_destination(CartPoint dest){
  if (state == 'd'){
    this->dock->set_sail(this);
  }
  this->destination = dest;
  if (cart_distance(this->destination, this->get_location()) == 0){
    this-> delta = CartVector (0,0);
  }

  else{
    this->delta = ((this->destination - this->get_location()) * (this->get_speed() / cart_distance(this->destination, this->get_location())));
  }
}
