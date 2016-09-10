#ifndef SAILOR_H
#define SAILOR_H
#include <iostream>
#include "GameObject.h"
#include "CartPoint.h"
#include "CartVector.h"
#include "Port.h"
#include "Dock.h"

class Dock;
class Port;
// class represents a simulated character in the game. Can move, supply, dock, etc
class Sailor: public GameObject {

 public:

  Sailor();
  Sailor(int in_id, Dock* hideout);
  ~Sailor();

  bool update();
  double get_size();
  double get_preSize();
  double get_cargo();
  void start_sailing(CartPoint dest);
  void start_supplying(Port* destPort);
  void start_hiding();
  bool is_hidden();
  void start_docking(Dock* destDock);
  void anchor();
  void show_status();
  double get_speed();

 private:

  double health;
  double size;
  double preSize;
  double hold;
  double cargo;
  CartPoint destination;
  CartVector delta;
  Port* port;
  Dock* dock;
  Dock* hideout;

  bool update_location();
  void setup_destination(CartPoint dest);

};

#endif
