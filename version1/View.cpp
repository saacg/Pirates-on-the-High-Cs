#include <iostream>
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

// class represents the graphical display of the game

// default constructor
View::View(){

  this->size = 11;
  this->scale = 2;
  this->origin = CartPoint (0,0);

}

// destructor
View::~View(){

  cout << "View destructed." << endl;

}

// sets all the cells of the grid to the background pattern (just periods and spaces)
void View::clear() {

  for (int i = 0; i < this->size; i++){
    for (int j = 0; j < this-> size; j++){
      for (int k = 0; k < 1; k++){
	grid[i][j][k] = '.';
	grid[i][j][k + 1] = ' ';
      }
    }
  }
}

// plots the pointed to object in the appropriate grid cell, calls get subscripts to validate the values and the drawself function to insert the corresponding ASCII values into the array cells
void View::plot(GameObject* ptr){
  int ix, iy;
  if (this->get_subscripts(ix, iy, ptr->get_location())){
    ptr->drawself(&grid[iy][ix][0]);
  }
  
}

// outputs grid array to produce the graphical display to match the sample output
void View::draw(){

  char axis[24] = {' ', ' ', '0', ' ', ' ', ' ', '4', ' ', ' ', ' ', '8', ' ', ' ', ' ', '1', '2', ' ', ' ', '1', '6', ' ', ' ',
		   '2', '0'}; 

  for (int i = this->size - 1, y1 = 23, y2 = 22; i >= 0; i--){
    cout << axis [y2] << axis [y1];
    y2 -= 2;
    y1 -= 2;
    for (int j = 0; j < this->size; j++){
      for (int k = 0; k < 1; k++){
	cout << grid [i][j][k] << grid[i][j][k + 1];
      }
    }
    cout << endl;
  }

  for (int i = 0; i < 24; i++){
    cout << axis [i];
  }

  cout << " " << endl;

}


// calculates the column and row subscripts of the grid array corresponding to the correct location
// if location is off grid, prints out message
bool View::get_subscripts(int &ix, int &iy, CartPoint location){
  CartVector subscripts;
  subscripts = ((location - this->origin) / this->scale);
  ix = static_cast<int>(subscripts.x);
  iy = static_cast<int>(subscripts.y);
  if (ix < this->size && iy < this->size){
    return true;
  }
  else{
    cout << "An object is outside the display" << endl;
    return false;
  }
}
