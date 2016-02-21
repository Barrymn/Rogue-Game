//
//  dtreasure.cpp
//  cc3k
//
//  Created by Ning Ma on 7/21/13.
//  Copyright (c) 2013 Ning Ma. All rights reserved.
//

#include "dtreasure.h"

DTreasure:: DTreasure(): Treasure(6), dead(false){}

DTreasure:: ~DTreasure(){}

void DTreasure::setDead(){
  dead = true;
}

bool DTreasure::getDead(){
  return dead;
}