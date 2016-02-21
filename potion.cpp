//
//  potion.cpp
//  cc3k
//
//  Created by Ning Ma on 7/21/13.
//  Copyright (c) 2013 Ning Ma. All rights reserved.
//

#include "potion.h"
#include <iostream>
using namespace std;

Potion:: Potion(string s):Item('P'),type(s){}

Potion:: ~Potion(){}

string Potion:: getType(){return type;}

void Potion:: function(PC* pc){
  if(type == "RH"){
    pc->setHp(pc->getHp()+10);
  }
  else if(type == "BA"){
    pc->setAtk(pc->getAtk()+5);
  }
  else if(type == "BD"){
    pc->setDef(pc->getDef()+5);
  }
  else if(type == "PH"){
    if(pc->getRace() == "Elves"){
      pc->setHp(pc->getHp()+10);
    }
    else{
    pc->setHp(pc->getHp()-10);
    }
  }
  else if(type == "WD"){
    if(pc->getRace() == "Elves"){
      pc->setDef(pc->getDef()+5);
    }
    else{
    pc->setDef(pc->getDef()-5);
    }
  }
  else if(type == "WA"){
    if(pc->getRace() == "Elves"){
      pc->setAtk(pc->getAtk()+5);
    }
    else{
    pc->setAtk(pc->getAtk()-5);
    }
  }
  if(pc->getRace()=="Human" && pc->getHp() > 140){
    pc->setHp(140);
  }
  if(pc->getRace()=="Orc" && pc->getHp() > 180){
    pc->setHp(180);
  }
  if(pc->getRace()=="Elves" && pc->getHp() > 140){
    pc->setHp(140);
  }
  if(pc->getRace()=="Dwarf" && pc->getHp() > 100){
    pc->setHp(100);
  }
}
  
