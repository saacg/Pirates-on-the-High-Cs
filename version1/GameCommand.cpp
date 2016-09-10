#include <iostream>
#include "Model.h"
#include "GameCommand.h"
#include "CartPoint.h"
#include "CartVector.h"
#include "GameObject.h"
#include "Port.h"
#include "Dock.h"
#include "Sailor.h"
#include "View.h"

using namespace std;

// represents the Controller of the MVC pattern, provides functions that interpret user input to perform the requested actions

// commands sailor to move to specified location
// runs the start sailing function
void do_sail_command(Model* model){
  int iD;
  double x, y;
  cin >> iD >> x >> y;
  model->get_Sailor_ptr(iD)->start_sailing(CartPoint (x, y));

}

// advances time by one step, updates each object once
void do_go_command(Model* model){
  cout << "Advancing time one tick" << endl;
  model->update();
  model->show_status();
}

// advances time one step and updates each object until update function returns true (at least one object changes state) or until time has progressed 5 steps
void do_run_command(Model* model){
  cout << "Advancing to next event or 5 ticks" << endl;
  int i = 0;
  bool updateBool = false;
  while (i < 5 && updateBool == false){
    updateBool = model->update();
    i++;
  }
  model->show_status();
}

// commands sailor to supply at port
// runs start supplying function
void do_port_command(Model* model){
  int iD1, iD2;
  cin >> iD1 >> iD2;
  model->get_Sailor_ptr(iD1)->start_supplying(model->get_Port_ptr(iD2));
}

// commands sailor to hide
// runs start hiding function
void do_hide_command(Model* model){
  int iD;
  cin >> iD;
  model->get_Sailor_ptr(iD)->start_hiding();
}

// commands sailor to stop and drop anchor
// runs the anchor function
void do_anchor_command(Model* model){
  int iD;
  cin >> iD;
  model->get_Sailor_ptr(iD)->anchor();
}

// inspires mass confusion on piazza for infrequent users
void do_list_command(Model* model){
  model->show_status();
}

// commands sailor to move to dock
// runs start docking function
void do_dock_command(Model* model){
  int iD1, iD2;
  cin >> iD1 >> iD2;
  ( model->get_Sailor_ptr(iD1))->start_docking((model->get_Dock_ptr(iD2)));
}
