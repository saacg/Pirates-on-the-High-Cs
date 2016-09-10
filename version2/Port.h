#ifndef PORT_H
#define PORT_H
#include <iostream>
#include <fstream>
#include "GameObject.h"
#include "CartPoint.h"

class Model;
// class derived from GameObject - contains limited amount of supplies for Sailors
class Port: public GameObject {
  
 public:

  Port();
  Port(int in_id, CartPoint in_loc);
  ~Port();
  
  bool is_empty();
  double provide_supplies(double amount_to_provide = 50.0);
  bool update();
  void show_status();
  void save(std::ofstream& file);
  //void restore(std::ifstream& file, Model* model);
 private:
  
  double inventory;

};





#endif
