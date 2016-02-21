//
//  treasure.cpp
//  cc3k
//
//  Created by Ning Ma on 7/21/13.
//  Copyright (c) 2013 Ning Ma. All rights reserved.
//

#include "treasure.h"

Treasure:: Treasure(int gold): Item('G'), gold(gold){}

Treasure:: ~Treasure(){}

void Treasure:: function(PC* pc){
  if(pc->getRace() == "Dwarf"){
    int n = pc->getGold();
    n = n+(gold*2);
    pc->setGold(n);
  }
  else if(pc->getRace() == "Orc"){
    int n = pc->getGold();
    n = n+(gold/2);
    pc->setGold(n);
  }
  else{
    int n = pc->getGold();
    n = n+gold;
    pc->setGold(n);
  }
}

int Treasure::getGold(){
  return gold;
}