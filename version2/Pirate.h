#ifndef PIRATE_H
#define PIRATE_H
#include <fstream>
#include "Sailor.h"

class Sailor;
class Model;

class Pirate: public Sailor {
 public: 
  Pirate(Model* world);
  Pirate(int in_id, Model* world);
  //  ~Pirate();

  double get_speed();
  void start_plunder(Sailor* target);
  bool update();
  void show_status();
  void save(std::ofstream& file);

 private:
  int attack_strength;
  double range;
  Sailor* target;
  

};

#endif
