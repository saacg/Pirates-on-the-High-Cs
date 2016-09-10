#ifndef SAILOR_H
#define SAILOR_H
#include <iostream>
#include <fstream>
#include "GameObject.h"
#include "CartPoint.h"
#include "CartVector.h"
#include "Port.h"
#include "Dock.h"
#include "Model.h"


class CartPoint;
class Dock;
class Port;
class Model;
// class represents a simulated character in the game. Can move, supply, dock, etc
class Sailor: public GameObject {

 public:

  Sailor(char, Model* world);
  Sailor(char, int in_id, Dock* hideout, Model* world);
  Sailor(char, int in_id, CartPoint location, Model* world);
  ~Sailor();

  bool update();
  double get_size();
  double get_preSize();
  double get_cargo();
  double get_health();
  void start_sailing(CartPoint dest);
  void start_supplying(Port* destPort);
  void start_hiding();
  bool is_hidden();
  void start_docking(Dock* destDock);
  void anchor();
  void show_status();
 // double get_speed();
  virtual void start_plunder(Sailor*);
  virtual bool start_recruiting(Sailor*);
  void get_plundered(int attack_strength);
  virtual double get_speed() = 0;
  Dock* get_hideout(); 
  void save(std::ofstream& file);

 protected:
  Model* world;
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
