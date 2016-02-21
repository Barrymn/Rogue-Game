//
//  cell.cpp
//  cc3k
//
//  Created by Ning Ma on 2013-07-20.
//  Copyright (c) 2013 Ning Ma. All rights reserved.
//

#include "cell.h"

Cell::Cell(): type('\0'), obj(NULL), r(0), c(0), occupied(true) {}

Cell::~Cell() {
  delete obj;
}

void Cell::set(char type, int r, int c) {
  this->type = type;
  this->r = r;
  this->c = c;
  if ((48 <= type && type <= 52) || type == '#' || type == '+') {
    occupied = false;
  } else {
    occupied = true;
  }
}

char Cell::getname() {
  if (obj != NULL) {
    return obj->getName();
  }
  else if (48 <= type && type <= 52) {
    return '.';
  }
  else {
    return type;
  }
}

Object* Cell::getObj() {
  return obj;
}

int Cell::getR() {
  return r;
}

int Cell::getC() {
  return c;
}

void Cell::occupy(Object* obj) {
  this->obj = obj;
  occupied = true;
}

Object* Cell::disoccupy() {
  Object* temp = obj;
  obj = NULL;
  occupied = false;
  return temp;
}

void Cell::remove() {
  delete obj;
  obj = NULL;
  occupied = false;
}

bool Cell::occupant() {
  return occupied;
}