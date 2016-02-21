//
//  cell.h
//  cc3k
//
//  Created by Ning Ma on 2013-07-20.
//  Copyright (c) 2013 Ning Ma. All rights reserved.
//

#ifndef __cc3k__cell__
#define __cc3k__cell__

#include <iostream>
#include "object.h"

class Cell {
  char type;
  Object* obj;
  int r;
  int c;
  bool occupied;
public:
  Cell();
  ~Cell();
  void set(char type, int r, int c);
  
  char getname();
  Object* getObj();
  
  int getR();
  int getC();
  
  bool occupant();
  void occupy(Object* obj);
  Object* disoccupy();
  void remove();
};

#endif /* defined(__cc3k__cell__) */
