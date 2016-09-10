#include <iostream>
#include <list>
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
Model::Model(){

  time = 0;
  this->num_objects = 10;
  this->num_ports = 4;
  this->num_docks = 3;
  this->num_sailors = 3;



  this->object_ptrs = new GameObject* [num_objects];
  this->port_ptrs = new Port* [num_ports];
  this->dock_ptrs = new Dock* [num_docks];
  this->sailor_ptrs = new Sailor* [num_sailors];

  this->dock_ptrs[0] = new Dock (1, CartPoint (5, 1));
  this->dock_ptrs[1] = new Dock (2, CartPoint (6, 2));
  this->dock_ptrs[2] = new Dock (3, CartPoint (1, 8));
  this->object_ptrs[0] = dock_ptrs[0];
  this->object_ptrs[1] = dock_ptrs[1];
  this->object_ptrs[2] = dock_ptrs[2];


  this->port_ptrs[0] = new Port (1, CartPoint (1, 20));
  this->port_ptrs[1] = new Port (2, CartPoint (20, 1));
  this->port_ptrs[2] = new Port (3, CartPoint (20, 20));
  this->port_ptrs[3] = new Port (4, CartPoint (7, 2));
  this->object_ptrs[6] = this->port_ptrs[0];
  this->object_ptrs[7] = this->port_ptrs[1];
  this->object_ptrs[8] = this->port_ptrs[2];
  this->object_ptrs[9] = this->port_ptrs[3];



  this->sailor_ptrs[0] = new Sailor (1, dock_ptrs[0]);
  this->sailor_ptrs[1] = new Sailor (2, dock_ptrs[1]);
  this->sailor_ptrs[2] = new Sailor (3, dock_ptrs[2]);
  this->object_ptrs[3] = this->sailor_ptrs[0];
  this->object_ptrs[4] = this->sailor_ptrs[1];
  this->object_ptrs[5] = this->sailor_ptrs[2];

 
  cout << "Model default constructed" << endl;

}

// destructor deallocates all the dynamic memory from the pointer arrays and deletes all game objects
Model::~Model(){
  
  delete dock_ptrs[0];
  delete dock_ptrs[1];
  delete dock_ptrs[2];
  delete sailor_ptrs[0];
  delete sailor_ptrs[1];
  delete sailor_ptrs[2];
  delete port_ptrs[0];
  delete port_ptrs[1];
  delete port_ptrs[2];
  delete port_ptrs[3];
  delete[] object_ptrs;

  cout << "Model destructed" << endl;

}

// getter function for specific sailor object, iterates over the array of sailor pointers and returns pointer with matching id number, returns null if there is no match (this should never happen)
// uses linear search to go through the array
Sailor* Model::get_Sailor_ptr(int id_num){
  for (int i = 0; i < num_sailors; i++){
    if (id_num == sailor_ptrs[i]->get_id()){
      return sailor_ptrs[i];
    }
  }

  return NULL;
}

// getter function for specific port object, similar to the sailor getter
Port* Model::get_Port_ptr(int id_num){
  for (int i = 0; i < num_ports; i++){
    if (id_num == port_ptrs[i]->get_id()){
      return port_ptrs[i];
    }
  }

  return NULL;
}

// getter function for specific dock object
Dock* Model::get_Dock_ptr(int id_num){
  for (int i = 0; i < num_docks; i++){
    if (id_num == dock_ptrs[i]->get_id()){
      return dock_ptrs[i];
    }
  }
  return NULL;
}

// services main program, increments time and updates every game object (works because it is a virtual function)
bool Model::update(){
  (this->time)++;
  bool returnBool = false;
  for (int i = 0; i < num_objects; i++){
    if (this->object_ptrs[i]->update()){
      returnBool = true;
    }
  }
  return returnBool;
}

// outputs status for all the game objects by calling their show status function  (this works because it is a virtual function)
void Model::show_status(){

  for (int i = 0; i < num_docks; i++){
    this->dock_ptrs[i]->show_status();
  }

  for (int i = 0; i < num_sailors; i++){
    this->sailor_ptrs[i]->show_status();
  }

  for (int i = 0; i < num_ports; i++){
    this->port_ptrs[i]->show_status();
  }

}

// services main program by outputting the time and the updated view display for all the game objects
void Model::display(View* view){
  cout << "Time: " << this->time << endl;
  view->clear();
  for (int i = 0; i < num_objects; i++){
    view->plot(object_ptrs[i]);
  }
  view->draw();

}
