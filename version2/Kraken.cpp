#include <iostream>
#include <fstream>
#include "GameObject.h"
#include "Kraken.h"
#include "CartPoint.h"
#include "Model.h"

using namespace std;

Kraken* Kraken::instance = NULL;

Kraken::Kraken(Model* world):GameObject('.', 0, CartPoint(0, 0)){
  this->world = world;
  this->callOfTheKraken = 0;
  this->state = 'w';
  lostToKraken = new list<Sailor*>;
}

Kraken::~Kraken(){
  cout << "Kraken destructed" << endl;
}

Kraken* Kraken::get_instance(Model* world){

  if(!instance){
    instance = new Kraken(world);
  }

  return instance;
}

bool Kraken::update(){
  bool krakenAwakening = false;
  if (callOfTheKraken < 14){
    callOfTheKraken++;
    if (callOfTheKraken == 10){
      cout << "The Kraken is coming!" << endl;
      krakenAwakening = true;
    }
  }
  else {
    cout << "The Kraken is upon us!" << endl;
    this->callOfTheKraken = 0;
    world->dock_check();
    this->theKrakening();
    krakenAwakening = true;
  }

  return krakenAwakening;
}

void Kraken::theKrakening(){
  int i = 1;
  cout << "----------The Kraken Claimed----------" << endl;

  if(!(world->unprotected_sailors->empty())){
    for(list<Sailor*>::iterator it = world->unprotected_sailors->begin(); it != world->unprotected_sailors->end(); it++){
      (*it)->set_state('x');
      this->lostToKraken->push_back(*it);
      cout << "(" << i << ")" << " - " << (*it)->get_display() << (*it)->get_id() << endl;
      i++;
    }
    world->unprotected_sailors->clear();
  }
  cout << "----------------------------------------" << endl;
}

void Kraken::chronicleOfTheKraken(){
  cout << "----------The History of Kraken's Wrath---------- " << endl;
  if(!(lostToKraken->empty())){
    int i = 1;
    for(list<Sailor*>::iterator it = lostToKraken->begin(); it != lostToKraken->end(); it++){
      cout << "(" << i << ")" << " - " << (*it)->get_display() << (*it)->get_id() << endl;
      i++;
    }
  }
  cout << "---------------------------------------------------- " << endl;
}

void Kraken::save(ofstream& file){
  GameObject::save(file);
  file << " " << this->callOfTheKraken << endl;
  if(!(lostToKraken->empty())){
    for(list<Sailor*>::iterator it = lostToKraken->begin(); it != lostToKraken->end(); it++){
      file << "d ";
      (*it)->save(file);
    }
  }
  else {
    file << "e " << endl;
  }
}
