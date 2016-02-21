//
//  pc.cpp
//  cc3k
//
//  Created by Ning Ma on 7/21/13.
//  Copyright (c) 2013 Ning Ma. All rights reserved.
//

#include "pc.h"
#include "potion.h"
#include "treasure.h"
#include <iostream>
using namespace std;

PC:: PC(int hp, int atk, int def, string race): Character('@',hp,atk,def,true,race), gold(0){}

PC:: ~PC(){}

int PC:: getGold(){return gold;}

void PC:: setGold(int newGold){gold=newGold;}

void PC:: drinkP(Potion* p){
  p->function(this);
}

void PC:: getT(Treasure* t){
  t->function(this);
}
