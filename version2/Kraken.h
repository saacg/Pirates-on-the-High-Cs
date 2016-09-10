#ifndef KRAKEN_H
#define KRAKEN_H
#include <fstream>
#include <list>
#include "GameObject.h"


class Model;
class Sailor;

class Kraken: public GameObject {

 public:

  static Kraken* get_instance(Model* world);
  bool update();
  void show_status(){};
  void chronicleOfTheKraken();
  ~Kraken();
  void save(std::ofstream& file);
 
 private:

  Model* world;
  int callOfTheKraken;
  Kraken(Model* world);
  Kraken();
  static Kraken* instance;
  std::list<Sailor*>* lostToKraken;
  void theKrakening();
  Kraken(Kraken const&);

};


#endif
