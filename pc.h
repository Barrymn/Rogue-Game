//
//  pc.h
//  cc3k
//
//  Created by Ning Ma on 7/21/13.
//  Copyright (c) 2013 Ning Ma. All rights reserved.
//

#ifndef __cc3k__pc__
#define __cc3k__pc__

#include <iostream>
#include "character.h"


class Treasure;
class Potion;

class PC: public Character{
protected:
  int gold;
public:
  PC(int hp, int atk, int def, std::string race);
  ~PC();
  int getGold();
  void setGold(int newGold);
  void drinkP(Potion* p);
  void getT(Treasure* t);
};


#endif /* defined(__cc3k__pc__) */
