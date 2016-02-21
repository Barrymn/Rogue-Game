//
//  floor.h
//  cc3k
//
//  Created by Ziquan Wang on 2013-07-20.
//  Copyright (c) 2013 Ziquan Wang. All rights reserved.
//

#ifndef __cc3k__floor__
#define __cc3k__floor__

#include <iostream>
#include "cell.h"
#include "textdisplay.h"
#include "chamber.h"
#include "object.h"
#include "3p.h"
#include "enemy.h"
#include "7e.h"
#include "treasure.h"
#include "dtreasure.h"
#include "ntreasure.h"
#include "potion.h"
#include "stair.h"
#include <string>

const int numChamber = 5;
const int numPotion = 10;
const int numTreasure = 10;
const int numEnemy = 20;
const int numFloor = 10;

class Floor {
  std::string map;
  TextDisplay* td;
  Chamber* chamber;
  Cell** theFloor;
  int f;	// current floor
  int w;	// width
  int l;	// length
  int r;	// pc coordinate
  int c;	// pc coordinate
  Potion** po;	// potions pc have
  int numP;
  
  void pcSpawn(Object* pc); // spawn both pc and stair
  void potionSpawn();
  void treasureSpawn();
  void enemySpawn();
  
  void newLevel();
  
  void pcNotify();
  void floorNotify();
  void actionNotify(std::string s);
  
  Cell* randomCell(); // generate a random Cell, occupied or unoccupied
public:
  Floor(int w, int l);
  void init(std::string map);
  ~Floor();
  
  int getF();
  
  void notifyTd();
  
  void newGame(Object* pc);
  
  void enemyMove();
  
  void pcMove(int i);
  void pcAttack(int i);
  void pcUse(int i);
  void pcGet(int i);
  void pcBuy(int poType, int poNum);
  void pcDrink();
  
  friend std::ostream& operator<<(std::ostream &out, const Floor &f);
};

  
#endif /* defined(__cc3k__floor__) */
