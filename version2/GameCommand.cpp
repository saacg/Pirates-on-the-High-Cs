#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include "InputHandling.h"
#include "Model.h"
#include "GameCommand.h"
#include "CartPoint.h"
#include "CartVector.h"
#include "GameObject.h"
#include "Port.h"
#include "Dock.h"
#include "Sailor.h"
#include "View.h"
#include "Merchant.h"
#include "Pirate.h"

using namespace std;

// represents the Controller of the MVC pattern, provides functions that interpret user input to perform the requested actions

// commands sailor to move to specified location
// runs the start sailing function
void do_sail_command(Model* model){
  int iD;
  double x, y;
  if (!(cin >> iD)){
    throw InvalidInput("Was expecting an integer");
  }
  if (!(cin >> x >> y)){
    throw InvalidInput("Was expecting a double");
  }
  Sailor* sailor = model->get_Sailor_ptr(iD);
  if (sailor == (Sailor*)NULL){
    throw InvalidInput ("Invalid Sailor ID");
  }
  sailor->start_sailing(CartPoint (x, y));

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
  if(!(cin >> iD1 >> iD2)){
    throw InvalidInput("Was expecting an integer");
  }
  Sailor* sailor = model->get_Sailor_ptr(iD1);
  if(sailor == (Sailor*)NULL){
    throw InvalidInput("Invalid sailor ID");
  }
  Port* port = model->get_Port_ptr(iD2);
  if(port == (Port*)NULL){
    throw InvalidInput("Invalid port ID");
  }
  sailor->start_supplying(port);
}


// commands sailor to hide
// runs start hiding function
void do_hide_command(Model* model){
  int iD;
  if(!(cin >> iD)){
    throw InvalidInput ("Was expecting an integer");
  }
  Sailor* sailor = model->get_Sailor_ptr(iD);
  if(sailor == (Sailor*)NULL){
    throw InvalidInput("Invalid Sailor ID");
  }
  sailor->start_hiding();
}

// commands sailor to stop and drop anchor
// runs the anchor function
void do_anchor_command(Model* model){
  int iD;
  if(!(cin >> iD)){
    throw InvalidInput ("Was expecting an integer");
  }
  Sailor* sailor = model->get_Sailor_ptr(iD);
  if(sailor == (Sailor*)NULL){
    throw InvalidInput("Invalid Sailor ID");
  }
  sailor->anchor();
}

// inspires mass confusion on piazza for infrequent users
void do_list_command(Model* model){
  model->show_status();
}

// commands sailor to move to dock
// runs start docking function
void do_dock_command(Model* model){
  int iD1, iD2;
  if (!(cin >> iD1 >> iD2)){
    throw InvalidInput("Was expecting integer");
  }
  Sailor* sailor = model->get_Sailor_ptr(iD1);
  if(sailor == (Sailor*)NULL){
    throw InvalidInput("Invalid Sailor ID");
  }
  Dock* dock = model->get_Dock_ptr(iD2);
  if(dock == (Dock*)NULL){
    throw InvalidInput("Invalid Dock ID");
  }
  sailor->start_docking(dock);
}

void do_plunder_command(Model* model){
  int iD1, iD2;
  if (!(cin >> iD1 >> iD2)){
    throw InvalidInput("Was expecting integer");
  }
  Sailor* toPlunder = model->get_Sailor_ptr(iD1);
  if(toPlunder == (Sailor*)NULL){
    throw InvalidInput("Invalid sailor ID");
  }
  Sailor* toBePlundered = model->get_Sailor_ptr(iD2);
  if (toPlunder == (Sailor*)NULL){
    throw InvalidInput("Invalid sailor ID");
  }
  toPlunder->start_plunder(toBePlundered);
}

void handle_new_command(Model* model){
  char TYPE;
  int ID, ID_HOME;
  double X, Y;

  if(!(cin >> TYPE)){
    throw InvalidInput("Was expecting character");
  }

  switch(TYPE){
  case 'P': {
    if(!(cin >> ID >> X >> Y)){
      throw InvalidInput("Was expecting integer followed by two doubles");
    }
    if(model->check_ID(TYPE, ID)){
      throw InvalidInput("Duplicate ID");
    }
    Port* newPort = new Port(ID, CartPoint(X, Y));
    model->add_new_object(newPort);
    break;
  }
  case 'D': {
    if(!(cin >> ID >> X >> Y)){
      throw InvalidInput("Was expecting integer followed by two doubles");
    }
    if(model->check_ID(TYPE, ID)){
      throw InvalidInput("Duplicate ID");
    }
    Dock* newDock = new Dock(ID, CartPoint(X, Y));
    model->add_new_object(newDock);
    break;
  }
  case 'M': {
    if(!(cin >> ID >> ID_HOME)){
      throw InvalidInput("Was expecting two integers");
    }
    if(model->check_ID(TYPE, ID)){
      throw InvalidInput("Duplicate ID");
    }
    Dock* newHome = model->get_Dock_ptr(ID_HOME);
    if(newHome == (Dock*)NULL){
      throw InvalidInput("Invalid Dock ID");
    }
    Sailor* newMerchant = new Merchant(ID, model->get_Dock_ptr(ID_HOME), model);
    model->add_new_object(newMerchant);
    break;
  }
  case 'R':{
    if(!(cin >> ID)){
      throw InvalidInput("Was expecting integer");
    }
    if(model->check_ID(TYPE, ID)){
      throw InvalidInput("Duplicate ID");
    }
    Sailor* newPirate = new Pirate(ID, model);
    model->add_new_object(newPirate);
    break;
  }
  }
}

void do_save_command(Model* model){
  ofstream file;  
  string fileName;
  cin >> fileName;  
  file.open(fileName.c_str());
  model->save(file);
  file.close();
}

void do_restore_command(Model* model){
  ifstream file;
  string fileName;
  cin >> fileName;
  file.open(fileName.c_str());
  if(!(file.is_open())){
    throw InvalidInput("File does not exist in directory");
  }
  model->restore(file);
  file.close();
}
