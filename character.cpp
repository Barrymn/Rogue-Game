//
//  character.cpp
//  cc3k
//
//  Created by Ning Ma on 7/20/13.
//  Copyright (c) 2013 Ning Ma. All rights reserved.
//

#include "character.h"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

Character:: Character(char n, int hp, int atk, int def, bool alive, string race): Object(n), race(race), hp(hp), atk(atk), def(def), alive(alive){}

Character:: ~Character(){}

void Character:: setHp(int newHp){hp=newHp;}

void Character:: setAtk(int newAtk){atk=newAtk;}

void Character:: setDef(int newDef){def=newDef;}

void Character:: setAlive(bool newAlive){
  alive = newAlive;
}

int Character:: getHp(){return hp;}

int Character:: getAtk(){return atk;}

int Character:: getDef(){return def;}

bool Character:: getAlive(){return alive;}

string Character:: getRace(){return race;}

int Character:: attack(){return atk;}

string Character:: attacked(int n){
  string s;
  stringstream ss;
  float d = static_cast<float>(def);
  int damage = (100/(100+d))*n;
  ss << damage;
  ss >> s;
  hp = hp-damage;
  if(hp <= 0){alive = false;}
  return s;
}


