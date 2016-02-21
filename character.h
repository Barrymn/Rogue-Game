//
//  character.h
//  cc3k
//
//  Created by Ning Ma on 7/20/13.
//  Copyright (c) 2013 Ning Ma. All rights reserved.
//

#ifndef __cc3k__character__
#define __cc3k__character__

#include <iostream>
#include <string>
#include "object.h"

class Character: public Object{
protected:
  std::string race;
  int hp;
  int atk;
  int def;
  bool alive;
  
public:
  Character(char n, int hp, int atk, int def, bool alive, std::string race);
  virtual ~Character();
  void setHp(int newHp);
  void setAtk(int newAtk);
  void setDef(int newDef);
  void setAlive(bool newAlive);
  int getHp();
  int getAtk();
  int getDef();
  bool getAlive();
  std::string getRace();
  virtual int attack();
  virtual std::string attacked(int n);
};


#endif /* defined(__cc3k__character__) */
