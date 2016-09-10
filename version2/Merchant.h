#ifndef MERCHANT_H
#define MERCHANT_H
#include <fstream>
#include "Sailor.h"

class Dock;
class Model;

class Merchant:public Sailor {

 public:
  Merchant(Model* world);
  Merchant(int id, Dock* home, Model* world);
  // ~Merchant();  
  double get_speed();
  bool start_recruiting(Merchant* sailor_mate);
  bool update();
  void show_status();
  void save(std::ofstream& file);

 private:
  int recruitTime;
};


#endif
