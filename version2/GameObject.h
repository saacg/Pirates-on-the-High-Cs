#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <iostream>
#include <fstream>
#include "CartPoint.h"

class GameObject {

 public:
  CartPoint location;
  // default constructor: initializes the display_code, id_num, and location to (0,0), outputs confirmation message
  GameObject(char in_code, int in_id);

  //initializes display_code, id_num, and location, outputs confirmation message
  GameObject(char in_code, int in_id, CartPoint in_loc);

  virtual ~GameObject();

  virtual bool update() = 0; // declares a pure virtual function, defining GameObject as an abstract class
                             // this function will never be implemented in the GameObject.cpp

  // returns the location for the object
  CartPoint get_location();

  // returns the id_num for the object
  int get_id();

  char get_display();

  char get_state();
  void set_state(char stateChar);
  void set_location(double x, double y);
  // outputs the information contained in this class
  virtual void show_status();

  void drawself(char* grid);

  virtual void save(std::ofstream& file);
  //virtual void restore(std::ifstream& file, Model* model);

 protected:
  // location of the object
 // CartPoint location;
 // int id_num;
  // how the object is represented in the View
  char display_code;
  
  // state of the object
  char state;

 private:
  int id_num;

};




#endif
