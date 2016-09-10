#include <iostream>
#include <fstream>
#include "Dock.h"
#include "GameObject.h"
#include "CartPoint.h"
#include "Sailor.h"
#include "Merchant.h"

using namespace std;

// class derived from GameObject, represents home for sailors. Has location and number of berths

// default constructor
Dock::Dock():GameObject('d', 0){
  state = 'u';
  berths = 30;

  cout << "Dock default constructed" << endl;
}

// constructor
Dock::Dock(int in_id, CartPoint in_loc):GameObject('d', in_id, in_loc){
  state = 'u';
  berths = 30;

  cout << "Dock constructed" << endl;
}

// destructor
Dock::~Dock(){
  cout << "Dock destructed." << endl;
}

// checks if there is enough space (empty berths) to dock sailor, if there is, returns true
bool Dock::dock_boat(Sailor* sailor_to_dock){
  if (this->berths < sailor_to_dock->get_size()){
    return false;
  }

  else {
    this->berths = this->berths - sailor_to_dock->get_size();
    return true;
  }
} 

// checks if sailor has emptied its boat, updates space once the sailor leaves
bool Dock::set_sail(Sailor* sailor_to_sail){
  if (sailor_to_sail->get_cargo() == 0){
    this->berths = this->berths + (sailor_to_sail->get_preSize());
    return true;
  }

  else {
    return false;
  }
}

// returns true if object has newly changed state and prints out state change message
bool Dock::update(){
  if (this->berths == 0 && this->state != 'p'){
    this->state = 'p';
    this->display_code = 'D';
    // cout << "Dock" << this->get_id() << " is packed" << endl; 
    return true;
  }

  else if (this->berths != 0 && this->state == 'p'){
    this->display_code = 'd';
    this->state = 'u';
    return true;
  }

  else {
    return false;
  }
}

// prints out status of the object
void Dock::show_status(){

  cout << "Dock Status: " << display_code << " with ID " << get_id() << " at location " << this->location << " has "
       << this->berths << " berths" << endl;
}

double Dock::get_berths(){
  return this->berths;
}

void Dock::save(ofstream& file){
  GameObject::save(file);
  file << " " << this->berths << endl;
}
