//
//  7e.cpp
//  cc3k
//
//  Created by Ning Ma on 7/22/13.
//  Copyright (c) 2013 Ning Ma. All rights reserved.
//

#include "7e.h"
#include <string>
#include <sstream>
#include <cstdlib>
using namespace std;

Dragon:: Dragon(DTreasure* dt): Enemy('D',150,20,25,true,moved,"Dragon"), moved(true){
  this->dt = dt;
}

string Dragon:: attacked(int n){
  string s;
  stringstream ss;
  float d = static_cast<float>(def);
  int damage = (100/(100+d))*n;
  ss << damage;
  ss >> s;
  hp = hp-damage;
  if(hp <= 0){
    alive = false;
    dt->setDead();
  }
  return s;
}


Merchant:: Merchant(): Enemy('M',30,70,5,true,false,"Merchant"){}

bool Merchant:: hostile = false;

bool Merchant:: getHostile(){return hostile;}

int Merchant:: attack(){
  moved = true;
  if(hostile == true){
    int n = rand() % 2;
    if(n == 0){
      return 0;
    }
    else{
      return atk;
    }
  }
  else{return 0;}
}

string Merchant:: attacked(int n){
  string s;
  stringstream ss;
  float d = static_cast<float>(def);
  int damage = (100/(100+d))*n;
  ss << damage;
  ss >> s;
  hp = hp-damage;
  if(hp <= 0){alive = false;}
  hostile = true;
  return s;
}

Goblin:: Goblin(): Enemy('N',70,5,10,true,false,"Goblin"){}

Vampire:: Vampire(): Enemy('V',50,25,25,true,false,"Vampire"){}

Werewolf:: Werewolf(): Enemy('W',120,30,5,true,false,"Werewolf"){}

Troll:: Troll(): Enemy('T',120,25,15,true,false,"Troll"){}

Phoenix:: Phoenix(): Enemy('X',50,35,20,true,false,"Phoenix"){}

Snake:: Snake(): Enemy('S', 40, 20, 20, true, false, "Snake"){}

