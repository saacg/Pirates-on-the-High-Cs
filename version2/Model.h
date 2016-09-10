#ifndef MODEL_H
#define MODEL_H
#include <iostream>
#include <list>
#include <fstream>
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
class Kraken;

class Model {

 public:

  Model();
  ~Model();

  std::list<Sailor*>* unprotected_sailors; 

  Sailor* get_Sailor_ptr(int id_num);
  Port* get_Port_ptr(int id_num);
  Dock* get_Dock_ptr(int id_num);
  Sailor* find_Sailor_mate(Sailor* sailor_mate);
  bool update();
  void display(View* view);
  void show_status();
  void spawn_Merchant(Sailor* merchantMom);
  bool we_have_privacy(Sailor* sailor);
  void add_new_object(GameObject* newObject);
  bool check_ID(char TYPE, int ID);
  bool sailor_at_sea(int ID);
  void dock_check();
  void save(std::ofstream& file);
  void restore(std::ifstream& file);  

  

 private:

  int time;
  std::list<GameObject*>* object_ptrs;
  std::list<GameObject*>* active_ptrs;
  std::list<Sailor*>* sailor_ptrs;
  std::list<Dock*>* dock_ptrs;
  std::list<Port*>* port_ptrs;
  Kraken* kraken;

  Model(const Model&);

};

#endif
