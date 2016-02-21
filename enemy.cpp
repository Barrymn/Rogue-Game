//
//  enemy.cpp
//  cc3k
//
//  Created by Ning Ma on 7/21/13.
//  Copyright (c) 2013 Ning Ma. All rights reserved.
//

#include "enemy.h"
#include <cstdlib>
using namespace std;
Enemy:: Enemy(char n, int hp, int atk, int def, bool alive, bool moved, string race): Character(n,hp,atk,def,alive,race), moved(false){}

Enemy:: ~Enemy(){}

int Enemy:: attack(){
  moved = true;
  int n = rand() % 2;
  if(n == 0){
    return 0;
  }
  else{
    return atk;
  }
}

void Enemy:: move(){
  if(moved == false){
    moved = true;
  }
  else{
    moved = false;
  }
}

bool Enemy:: getMoved(){return moved;}