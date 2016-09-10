#ifndef DOCK_H
#define DOCK_H
#include <iostream>
#include <fstream>
#include "GameObject.h"
#include "CartPoint.h"
#include "Sailor.h"

class Model;
class Sailor;
// class represents home for Sailor. Derived from GameObject, has a location and number of berths
class Dock: public GameObject {

 public:
  
  Dock();
  Dock(int in_id, CartPoint in_loc);
  ~Dock();

  bool dock_boat(Sailor* sailor_to_dock);
  bool set_sail(Sailor* sailor_to_sail);
  bool update();
  void show_status();
  double get_berths();
  void save(std::ofstream& file);
  //void restore(std::ifstream& file, Model* model);
 private:

  double berths;

};




#endif
