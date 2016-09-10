#include <iostream>
#include <fstream>
#include<list>
#include "CartPoint.h"
#include "CartVector.h"
#include "GameObject.h"
#include "Port.h"
#include "Dock.h"
#include "Sailor.h"
#include "Model.h"
#include "View.h"
#include "Merchant.h"

using namespace std;

Merchant::Merchant(Model* world):Sailor ('M', world){
  this->size = 10;
  this->preSize = 10;
  this->recruitTime = 0;
}

Merchant::Merchant(int id, Dock* home, Model* world):Sailor('M', id, home, world){
  this->size = 10;
  this->preSize = 10; 
  this->recruitTime = 0;
  // cout << "Merchant constructed" << endl;
}

/*
Merchant::~Merchant(){
  cout << "Merchant destructed" << endl;
}
*/

double Merchant::get_speed(){
  double speed = (1 / this->size) * this->health * 4;

  return speed;
}

bool Merchant::start_recruiting(Merchant* sailor_mate){
  int openBerths = this->hideout->get_berths() - (this->get_size() + sailor_mate->get_size());
  // cout << "Open berths: " << openBerths << endl;
  if ((world->we_have_privacy(this))
      && this->get_health() >= 40 && this->get_health() <= 60
      && sailor_mate->get_health() >= 40 && sailor_mate->get_health() <= 60
      && openBerths >= 10){
    cout << this->get_display() << this->get_id() << ": I found a new recruit!" << endl;
    // cout << sailor_mate->get_display() << this->get_id() << ": I found a new recruit!" << endl;
    return true;
  }

  else{
    return false;
  }
}

bool Merchant::update(){
  bool returnUpdate;
  switch(this->state){
  case 'a':
    if (this->is_hidden()){
      Sailor* sailor_mate = world->find_Sailor_mate(this);
      if (sailor_mate != NULL){
	//	cout << this->get_display() << this->get_id() <<  ": I found a mate" << endl;
	if (this->start_recruiting(dynamic_cast<Merchant*>(sailor_mate))){
	  this->set_state('r');
	  sailor_mate->set_state('r');
	  returnUpdate = true; break;
	}
      } 
      this->health -= 5;
      if(health <= 0){
	cout << this->get_display() << this->get_id() << " starved to death!" << endl;
	this->state = 'x';
	returnUpdate = true; break;
      }
    }
    returnUpdate = false; break;
  case 'r': 
    if(world->we_have_privacy(this)){
      this->recruitTime++;
      if(recruitTime == 2){
	world->spawn_Merchant(this);
	this->recruitTime = 0;
	this->set_state('a');
	returnUpdate = true; break;
      }
      else{
	returnUpdate = false; break;
      }
    }
    else{
      this->set_state('a');
      returnUpdate = true; break;
    }
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
  case 'x': returnUpdate = false; break;
  }

  return returnUpdate;
}

void Merchant::show_status(){
  if(this->state == 'x'){
  }

  else{
    cout << "Merchant status: " << this->display_code << " with ID " << this->get_id() << " at location " << this->location;
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
    case 'r': cout << " is recruiting a merchant" << endl; break;
    }
  }

}

void Merchant::save(ofstream& file){
  Sailor::save(file);
  file << this->recruitTime << endl;
}
