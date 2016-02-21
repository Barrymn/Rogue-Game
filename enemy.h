//
//  enemy.h
//  cc3k
//
//  Created by Ning Ma on 7/21/13.
//  Copyright (c) 2013 Ning Ma. All rights reserved.
//

#ifndef __cc3k__enemy__
#define __cc3k__enemy__

#include <iostream>
#include "character.h"
#include <string>

class Enemy: public Character{
protected:
  bool moved;
public:
  Enemy(char n, int hp, int atk, int def, bool alive, bool moved, std::string race);
  ~Enemy();
  void move();
  bool getMoved();
  virtual int attack();
};


#endif /* defined(__cc3k__enemy__) */
