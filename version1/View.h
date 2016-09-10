#ifndef VIEW_H
#define VIEW_H
#include "CartVector.h"
#include "CartPoint.h"
#include "GameObject.h"
#include "Port.h"
#include "Dock.h"
#include "Sailor.h"
#include "GameCommand.h"
#include "Model.h"

class CartPoint;
class GameObject;

const int view_maxsize = 20;

class View {

 public:

  View();
  ~View();

  void clear();
  void draw();
  void plot(GameObject* ptr);

 private:

  int size;
  double scale;
  CartPoint origin;
  char grid[view_maxsize][view_maxsize][2];
  bool get_subscripts(int &ix, int &iy, CartPoint location);

};


#endif
