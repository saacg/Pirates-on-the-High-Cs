#include <iostream>
#include <list>
#include <cstdlib>
#include <iterator>
#include <fstream>
#include <string>
#include "CartPoint.h"
#include "CartVector.h"
#include "GameObject.h"
#include "Port.h"
#include "Dock.h"
#include "Sailor.h"
#include "Model.h"
#include "View.h"
#include "Merchant.h"
#include "Pirate.h"
#include "Kraken.h"

using namespace std;

// class stores all game objects in memory and interacts with the Controller and View components

// default constructor instantiates 10 game objects on the heap using arrays of pointers
Model::Model(){

  time = 0;
  srand(time);
  object_ptrs = new list<GameObject*>;
  active_ptrs = new list<GameObject*>;
  port_ptrs = new list<Port*>;
  dock_ptrs = new list<Dock*>;
  sailor_ptrs = new list<Sailor*>;

  unprotected_sailors = new list<Sailor*>;
  
  dock_ptrs->push_back(new Dock(1, CartPoint (5, 1)));
  dock_ptrs->push_back(new Dock(2, CartPoint (6, 2)));
  dock_ptrs->push_back(new Dock(3, CartPoint (1, 8)));

  for (list<Dock*>::iterator it = dock_ptrs->begin(); it != dock_ptrs->end(); it++){
    object_ptrs->push_back(*it);
  }
     
 
  port_ptrs->push_back(new Port(1, CartPoint(1, 20)));
  port_ptrs->push_back(new Port(2, CartPoint(20, 1)));
  port_ptrs->push_back(new Port(3, CartPoint(20, 20)));
  port_ptrs->push_back(new Port(4, CartPoint(7, 2)));

  for(list<Port*>::iterator it = port_ptrs->begin(); it != port_ptrs->end(); it++){
    object_ptrs->push_back(*it);
  }


  sailor_ptrs->push_back(new Merchant(1, get_Dock_ptr(1), this));
  sailor_ptrs->push_back(new Merchant(2, get_Dock_ptr(1), this));
  sailor_ptrs->push_back(new Merchant(3, get_Dock_ptr(2), this));
  sailor_ptrs->push_back(new Pirate(4, this));
  sailor_ptrs->push_back(new Pirate(5, this));

  for(list<Sailor*>::iterator it = sailor_ptrs->begin(); it != sailor_ptrs->end(); it++){
    object_ptrs->push_back(*it);
  }

  for(list<GameObject*>:: iterator it = object_ptrs->begin(); it != object_ptrs->end(); it++){
    active_ptrs->push_back(*it);
  }

  kraken = Kraken::get_instance(this);
  active_ptrs->push_back(kraken);
  object_ptrs->push_back(kraken);
 
  cout << "Model default constructed" << endl;

}

// destructor deallocates all the dynamic memory from the pointer arrays and deletes all game objects
Model::~Model(){

  kraken->chronicleOfTheKraken();

  for(list<Sailor*>::iterator it = sailor_ptrs->begin(); it != sailor_ptrs->end(); it++){
    delete *it;
  }

  for(list<Dock*>::iterator it = dock_ptrs->begin(); it != dock_ptrs->end(); it++){
    delete *it;
  }

  for(list<Port*>::iterator it = port_ptrs->begin(); it != port_ptrs->end(); it++){
    delete *it;
  }

  cout << "Model destructed" << endl;

  delete kraken;

  

}

// getter function for specific sailor object, iterates over the array of sailor pointers and returns pointer with matching id number, returns null if there is no match (this should never happen)
// uses linear search to go through the array
Sailor* Model::get_Sailor_ptr(int id_num){
  for (list<Sailor*>::iterator it = sailor_ptrs->begin(); it != sailor_ptrs->end(); it++){
    if (id_num == (*it)->get_id()){
      return *it;
    }
  }

  return NULL;
}

// getter function for specific port object, similar to the sailor getter
Port* Model::get_Port_ptr(int id_num){
  for (list<Port*>::iterator it = port_ptrs->begin(); it != port_ptrs->end(); it++){
    if (id_num == (*it)->get_id()){
      return *it;
    }
  }

  return NULL;
}

// getter function for specific dock object
Dock* Model::get_Dock_ptr(int id_num){
  for (list<Dock*>::iterator it = dock_ptrs->begin(); it != dock_ptrs->end(); it++){
    if (id_num == (*it)->get_id()){
      return *it;
    }
  }
  return NULL;
}

// services main program, increments time and updates every game object (works because it is a virtual function)
bool Model::update(){
  (this->time)++;
  srand(time);
  bool returnBool = false;
  /*
  if(this->kraken->update()){
    returnBool = true;
    } */

  for (list<GameObject*>::iterator it = active_ptrs->begin(); it!= active_ptrs->end(); it++){
    if ((*it)->get_state() == 'x'){
     it = active_ptrs->erase(it);
    }
  }
  for (list<GameObject*>::iterator it = active_ptrs->begin(); it != active_ptrs->end(); it++){
    if ((*it)->update()){
      returnBool = true;
    }

  }
 
  return returnBool;
}

// outputs status for all the game objects by calling their show status function  (this works because it is a virtual function)
void Model::show_status(){
  for(list<GameObject*>::iterator it = active_ptrs->begin(); it != active_ptrs->end(); it++){
    (*it)->show_status();
  }
  /*
  for (list<GameObject*>::iterator it = active_ptrs->begin(); it != active_ptrs->end(); it++){
    if((*it)->get_display() == 'd' || (*it)->get_display() == 'D'){
    (*it)->show_status();
    }
  }

  for (list<GameObject*>::iterator it = active_ptrs->begin(); it != active_ptrs->end(); it++){
    if((*it)->get_display() == 'P' || (*it)->get_display() == 'p'){
    (*it)->show_status();
    }
  }

for (list<GameObject*>::iterator it = active_ptrs->begin(); it != active_ptrs->end(); it++){
    if((*it)->get_display() == 'M' || (*it)->get_display() == 'R'){
    (*it)->show_status();
    }
  }
  */
}

// services main program by outputting the time and the updated view display for all the game objects
void Model::display(View* view){
  cout << "Time: " << this->time << endl;
  view->clear();
  for (list<GameObject*>::iterator it = active_ptrs->begin(); it != active_ptrs->end(); it++){
    view->plot(*it);
  }
  view->draw();

}


Sailor* Model::find_Sailor_mate(Sailor* lookingForMate){
  Sailor* sailor_mate = NULL;
  for(list<Sailor*>::iterator it = sailor_ptrs->begin(); it != sailor_ptrs->end(); it++){
    if ((*it)->get_display() == 'M' && (*it)->get_id() != lookingForMate->get_id() 
	&& (*it)->get_hideout() == lookingForMate->get_hideout() && (*it)->is_hidden() == true && (*it)->get_state() == 'a' ){
      sailor_mate = (*it);
      return sailor_mate;
    }
  }
  return sailor_mate;
}

void Model::spawn_Merchant(Sailor* merchantMom){
  int i = 1;
  int newID;
  Sailor* sailor = this->get_Sailor_ptr(i);
  while(sailor != NULL){
    i++;
    sailor = this->get_Sailor_ptr(i);
  }
  newID = i;
  Dock* newDockPtr = merchantMom->get_hideout();
  Merchant* newMerch = new Merchant(newID, newDockPtr, this);
  sailor_ptrs->push_back(newMerch);
  object_ptrs->push_back(newMerch);
  active_ptrs->push_back(newMerch);

  cout << merchantMom->get_display() << merchantMom->get_id() << ": I found a new recruit!" << endl;
}

bool Model::we_have_privacy(Sailor* sailor){
  int numSailors = 0;
  for(list<Sailor*>::iterator it = sailor_ptrs->begin(); it != sailor_ptrs->end(); it++){
    if((*it)->get_location() == sailor->get_location()){
      numSailors++;
    }
  }
  if (numSailors > 2){
    return false;
  }
  else{
    return true;
  }
}

void Model::add_new_object(GameObject* newObject){

  object_ptrs->push_back(newObject);
  active_ptrs->push_back(newObject);

  char TYPE = newObject->get_display();
  switch(TYPE){
  case 'P': port_ptrs->push_back(dynamic_cast<Port*>(newObject)); break;
  case 'd': dock_ptrs->push_back(dynamic_cast<Dock*>(newObject)); break;
  case 'M': sailor_ptrs->push_back(dynamic_cast<Sailor*>(newObject)); break;
  case 'R': sailor_ptrs->push_back(dynamic_cast<Sailor*>(newObject)); break;
  }

}

bool Model::check_ID(char TYPE, int ID){
 bool duplicateID = false;
 if (TYPE == 'M' || TYPE == 'R'){
   TYPE = 'S';
 }

  switch(TYPE){
  case 'P': 
    for (list<Port*>::iterator it = port_ptrs->begin(); it != port_ptrs->end(); it++){
      if ((*it)->get_id() == ID){
	duplicateID = true;
      }
    }
    break;
  case 'D':
    for (list<Dock*>::iterator it = dock_ptrs->begin(); it != dock_ptrs->end(); it++){
      if ((*it)->get_id() == ID){
	duplicateID = true;
      }
    }
    break;
  case 'S':
    for (list<Sailor*>::iterator it = sailor_ptrs->begin(); it != sailor_ptrs->end(); it++){
      if ((*it)->get_id() == ID && (*it)->get_state() != 'x'){
	duplicateID = true;
      }
    }
    break;
  } 
      
  return duplicateID;
}


bool Model::sailor_at_sea(int ID){
  bool sailorAtSea = true;
  for(list<Dock*>::iterator dockIt = dock_ptrs->begin(); dockIt != dock_ptrs->end(); dockIt++){
    if((*dockIt)->get_location() == get_Sailor_ptr(ID)->get_location()){
      sailorAtSea = false;
    }
  }

  return sailorAtSea;
}

void Model::dock_check(){
  int ID;
  for(list<Sailor*>::iterator sailIt = sailor_ptrs->begin(); sailIt != sailor_ptrs->end(); sailIt++){
    ID = (*sailIt)->get_id();
    if(sailor_at_sea(ID) == true && (*sailIt)->get_state() != 'x'){
      unprotected_sailors->push_back(*sailIt);
    }
  }
}

void Model::save(ofstream& file){
  file << "O " << this->time << endl;
  for(list<GameObject*>::iterator it = active_ptrs->begin(); it != active_ptrs->end(); it++){
    switch((*it)->get_display()){
    case 'D': file << "D "; break;
    case 'd': file << "D "; break;
    case 'P': file << "P "; break;
    case 'p': file << "p "; break;
    case 'M': file << "M "; break;
    case 'R': file << "R "; break;
    case '.': file << "K "; break;
    }
    (*it)->save(file);
  }
}

void Model::restore(ifstream& file){
  for(list<GameObject*>::iterator it = object_ptrs->begin(); it != object_ptrs->end(); it++){
    delete *it;
  }

  object_ptrs->clear();
  active_ptrs->clear();
  sailor_ptrs->clear();
  dock_ptrs->clear();
  port_ptrs->clear();

  char restoreCode;
  int restoreTime;
  while(file >> restoreCode){
    if (restoreCode == 'O'){
      file >> restoreTime; this->time = restoreTime;
    }

    else if(restoreCode == 'D'){
      int dockID;
      double dx, dy;
      file >> dockID >> dx >> dy;
      Dock* restoreDock = new Dock(dockID, CartPoint(dx, dy));
      dock_ptrs->push_back(restoreDock);
      active_ptrs->push_back(restoreDock);
      object_ptrs->push_back(restoreDock);
      // newDock->restore(file, this);
     
    }

    else if(restoreCode == 'P'){
      int pID;
      double px, py;
      file >> pID >> px >> py;
      Port* newPort = new Port(pID, CartPoint(px, py));
      port_ptrs->push_back(newPort);
      active_ptrs->push_back(newPort);
      object_ptrs->push_back(newPort);
      // newPort->restore(file, this);
    }

    else if(restoreCode == 'M'){
      int mID, msize, mpresize, mhold, mcargo;
      double mhealth, mx, my, mdestx, mdesty, mdeltax, mdeltay;
      char mdisplay, mstate;
      file >> mID >> mx >> my >> mdisplay >> mstate >> mhealth >> msize >> mpresize >> mhold >> mcargo
	   >> mdestx >> mdesty >> mdeltax >> mdeltay;
      Merchant* newMerchant = new Merchant('M', get_Dock_ptr(1), this);
      sailor_ptrs->push_back(newMerchant);
      object_ptrs->push_back(newMerchant);
      active_ptrs->push_back(newMerchant);

    }

    else if(restoreCode == 'R'){
      int rId;
      file >> rId;
      Pirate* newPirate = new Pirate(rId, this);
      sailor_ptrs->push_back(newPirate);
      object_ptrs->push_back(newPirate);
      active_ptrs->push_back(newPirate);

    }

    else if(restoreCode == 'K'){
      int kID, kx, ky;
      file >> kID >> kx >> ky;
      this->kraken = Kraken::get_instance(this);
      object_ptrs->push_back(kraken);
      active_ptrs->push_back(kraken);
    }
  }
}
