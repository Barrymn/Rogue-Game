//
//  textdisplay.h
//  cc3k
//
//  Created by Ziquan Wang on 2013-07-20.
//  Copyright (c) 2013 Ziquan Wang. All rights reserved.
//

#ifndef __cc3k__textdisplay__
#define __cc3k__textdisplay__

#include <iostream>
#include "pc.h"

class TextDisplay {
  char** display;
  const int w;
  const int l;
  
  std::string race;
  int floor;
  int gold;
  int hp;
  int atk;
  int def;
  int numP;
  std::string action;
public:
  TextDisplay(int w, int l);
  ~TextDisplay();
  
  void notify(int r, int c, char ch);
  
  void pcUpdate(PC* pc, int numP);
  void actionUpdate(std::string action);
  void floorUpdate(int floor);
  
  void win();
  void lose();
  
  friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif /* defined(__cc3k__textdisplay__) */
