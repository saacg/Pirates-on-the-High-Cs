#include <iostream>
#include <list>
#include <iterator>
#include "CartPoint.h"
#include "CartVector.h"
#include "GameObject.h"
#include "Port.h"
#include "Dock.h"
#include "Sailor.h"
#include "Model.h"
#include "View.h"

using namespace std;

// class stores all game objects in memory and interacts with the Controller and View components

// default constructor instantiates 10 game objects on the heap using arrays of pointers
// changed structures from arrays to STL linked lists
Model::Model(){

  time = 0;

  object_ptrs = new list<GameObject*>;
  port_ptrs = new list<Port*>;
  dock_ptrs = new list<Dock*>;
  sailor_ptrs = new list<Sailor*>;
  
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


  sailor_ptrs->push_back(new Sailor(1, get_Dock_ptr(1)));
  sailor_ptrs->push_back(new Sailor(2, get_Dock_ptr(2)));
  sailor_ptrs->push_back(new Sailor(3, get_Dock_ptr(3)));

  for(list<Sailor*>::iterator it = sailor_ptrs->begin(); it != sailor_ptrs->end(); it++){
    object_ptrs->push_back(*it);
  }
 
  cout << "Model default constructed" << endl;

}

// destructor deallocates all the dynamic memory from the pointer arrays and deletes all game objects
Model::~Model(){
  for(list<Dock*>::iterator it = dock_ptrs->begin(); it != dock_ptrs->end(); it++){
    delete *it;
  }

  for(list<Sailor*>::iterator it = sailor_ptrs->begin(); it != sailor_ptrs->end(); it++){
    delete *it;
  }

  for(list<Port*>::iterator it = port_ptrs->begin(); it != port_ptrs->end(); it++){
    delete *it;
  }

  cout << "Model destructed" << endl;

}

// getter function for specific sailor object, iterates over the array of sailor pointers and returns pointer with matching id number, returns null if there is no match (this should never happen)
// uses linear search to go through the list
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
  bool returnBool = false;
  for (list<GameObject*>::iterator it = object_ptrs->begin(); it != object_ptrs->end(); it++){
    if ((*it)->update()){
      returnBool = true;
    }
  }
  return returnBool;
}

// outputs status for all the game objects by calling their show status function  (this works because it is a virtual function)
void Model::show_status(){

  for (list<Dock*>::iterator it = dock_ptrs->begin(); it != dock_ptrs->end(); it++){
    (*it)->show_status();
  }

  for (list<Sailor*>::iterator it = sailor_ptrs->begin(); it != sailor_ptrs->end(); it++){
    (*it)->show_status();
  }

  for (list<Port*>::iterator it = port_ptrs->begin(); it != port_ptrs->end(); it++){
    (*it)->show_status();
  }

}

// services main program by outputting the time and the updated view display for all the game objects
void Model::display(View* view){
  cout << "Time: " << this->time << endl;
  view->clear();
  for (list<GameObject*>::iterator it = object_ptrs->begin(); it != object_ptrs->end(); it++){
    view->plot(*it);
  }
  view->draw();

}
