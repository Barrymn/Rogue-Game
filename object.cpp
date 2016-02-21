//
//  object.cpp
//  cc3k
//
//  Created by Ning Ma on 7/20/13.
//  Copyright (c) 2013 Ning Ma. All rights reserved.
//

#include "object.h"

#include <iostream>

Object:: Object(char n): name(n){}

Object::~Object(){}

char Object:: getName(){
  return name;
}