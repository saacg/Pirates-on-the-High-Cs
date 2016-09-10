#include <iostream>
#include<cstdlib>
#include "Pirate.h"
#include "Model.h"
#include "CartPoint.h"

using namespace std;

Pirate::Pirate(Model* world):Sailor('R', world){
  this->size = 20;
  this->preSize = 20;
  this->range = 1;
}

Pirate::Pirate(int in_id, Model* world):Sailor('R', in_id, CartPoint(rand() % 20, rand() % 20), world){
  this->size = 15;
  this->preSize = 15;
  this ->range = 1;

  // cout << "Pirate constructed" << endl;
}

/*
Pirate::~Pirate(){
 cout << "Pirate destructed" << endl;
}
*/

double Pirate::get_speed(){
  double speed = 0;
  return speed;
}

void Pirate::start_plunder(Sailor* target){
  if (cart_distance(this->get_location(), target->get_location()) <= this->range){
    cout << this->get_display() << this->get_id() << ": Arrrggghhhh!" << endl;
    this->target = target;
    this->set_state('p');
  }  

  else {
    cout << this->get_display() << this->get_id() << ": I will be back for you!" << endl;
  }
}

bool Pirate::update(){
  bool returnBool = false;
  switch(this->get_state()){
   case 'x': break;
   case 'a': break;
   case 'p': 
     if (cart_distance(this->get_location(), target->get_location()) > this->range) {
       cout << this->get_display() << this->get_id() << ": Darn! It escaped." << endl;
       this->target = NULL;
       this->set_state('a');
       returnBool = true;
       break;
     }
     else {
       if (this->target->get_state() == 'x'){
         cout << this->get_display() << this->get_id() << ": I triumph!" << endl;
         this->set_state('a');
         returnBool = true;
         break;
       } 
       else {
         cout << this->get_display() << this->get_id() << ": Arrghh matey!" << endl;
         this->target->get_plundered(this->attack_strength);
         if (this->target->get_state() == 'x'){
           this->health += 5;
         }
         break;
       }
     }
  }
  return returnBool;
}

void Pirate::show_status(){
  if(this->state == 'x'){
  }
  else{
    cout << "Pirate status: " << this->display_code << " with ID " << this->get_id() << " at location " << this->location;
    switch(this->state){
    case 'a': 
      cout << " is anchored. Has a size of: " << this->size << ", cargo of: " << this->cargo << ", hold of: "
	   << this->hold << ", and health of: " << this->health << endl; break;
    case 'p':
      cout << " Currently attacking " << this->target->get_id() << endl; break;
    }
  }
}

void Pirate::save(ofstream& file){
  int nullTarget = -1;
  Sailor::save(file);
  file << this->attack_strength << " " << this->range << " ";

  if(!(this->target)){
    file << nullTarget << endl;
  }
  else{
    file << this->target->get_id() << endl;
  }
}
