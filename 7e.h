//
//  7e.h
//  cc3k
//
//  Created by Ning Ma on 7/22/13.
//  Copyright (c) 2013 Ning Ma. All rights reserved.
//

#ifndef __cc3k___e__
#define __cc3k___e__

#include <iostream>
#include "enemy.h"
#include "dtreasure.h"

class Dragon: public Enemy{
protected:
  const bool moved;
  DTreasure* dt;
public:
  Dragon(DTreasure* dt);
  std::string attacked(int n);
};

class Merchant: public Enemy{
protected:
  static bool hostile;
public:
  Merchant();
  bool getHostile();
  int attack();
  std::string attacked(int n);
};

class Goblin: public Enemy{  
public:
  Goblin();
};

class Vampire: public Enemy{
public:
  Vampire();
};

class Werewolf: public Enemy{
public:
  Werewolf();
};

class Troll: public Enemy{
public:
  Troll();
};

class Phoenix: public Enemy{
public:
  Phoenix();
};

class Snake: public Enemy{
public:
  Snake();
};


#endif /* defined(__cc3k___e__) */
