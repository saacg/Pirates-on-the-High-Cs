#include <iostream>
#include <cstring>
#include "InputHandling.h"
#include "CartVector.h"
#include "CartPoint.h"
#include "GameObject.h"
#include "Port.h"
#include "Dock.h"
#include "Sailor.h"
#include "GameCommand.h"
#include "Model.h"
#include "View.h"

using namespace std;

// main function for game
// prints out header message
// creates Model and View objects on the heap
// takes in user commands, switch statement processes commands and directs program to correct functions
// destructs all game objects and deallocates all memory on the heap
int main(){

  cout << "EC327: Introduction to Software Engineering" << endl << "Fall 2015" << endl << "Programming Assignment 3" << endl;

  Model* model = new Model();

  View* view = new View ();

  
  model->show_status();
  model->display(view);

  char commandChar;

  while (commandChar != 'q'){
    
    cout << "Enter command: ";
    cin >> commandChar;

    try{
      switch(commandChar){
      case 's': do_sail_command(model); model->display(view); break;
      case 'p': do_port_command(model); model->display(view); break;
      case 'a': do_anchor_command(model);model->display(view); break;
      case 'd': do_dock_command(model); model->display(view);break;
      case 'h': do_hide_command(model); model->display(view);break;
      case 'g': do_go_command(model); model->display(view);break;
      case 'r': do_run_command(model); model->display(view);break;
      case 'l': do_list_command(model); model->display(view);break;
      case 'u': do_plunder_command(model);model->display(view);break;
      case 'n': handle_new_command(model);model->display(view); break;
      case 'S': do_save_command(model); break;
      case 'R': do_restore_command(model); break;
      case 'q': cout << "Terminating Program" << endl; model->display(view);break;
      default: throw InvalidInput("Invalid command"); break;
      }
    }
    catch (InvalidInput& except){
      cout << "Invalid input - " << except.msg_ptr << endl;
      model->display(view);
      cin.clear();
      cin.ignore(1000, '\n');
    }
    
  }

  delete view;
  delete model;

  return 0;
}
