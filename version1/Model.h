#ifndef MODEL_H
#define MODEL_H
#include <iostream>
#include <list>
#include "GameObject.h"
#include "Sailor.h"
#include "Dock.h"
#include "Port.h"
#include "GameCommand.h"
#include "View.h"

class Sailor;
class Port;
class Dock;
class View;

class Model {

 public:

  Model();
  ~Model();

  Sailor* get_Sailor_ptr(int id_num);
  Port* get_Port_ptr(int id_num);
  Dock* get_Dock_ptr(int id_num);
  bool update();
  void display(View* view);
  void show_status();

 private:

  int time;
  std::list<GameObject*>* object_ptrs;
  std::list<Sailor*>* sailor_ptrs;
  std::list<Dock*>* dock_ptrs;
  std::list<Port*>* port_ptrs;

  Model(const Model&);

};

#endif
