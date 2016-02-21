//
//  3p.h
//  cc3k
//
//  Created by Ning Ma on 7/21/13.
//  Copyright (c) 2013 Ning Ma. All rights reserved.
//

#ifndef __cc3k___p__
#define __cc3k___p__

#include <iostream>
#include "pc.h"

class Human: public PC{
public:
  Human();
  Human(int hp, int gold);
};

class Elves: public PC{
public:
  Elves();
  Elves(int hp, int gold);
};

class Orc: public PC{
public:
  Orc();
  Orc(int hp, int gold);
};

class Dwarf: public PC{
public:
  Dwarf();
  Dwarf(int hp, int gold);
};

class Ironman: public PC{
public:
  Ironman();
  Ironman(int hp, int gold);
};

#endif /* defined(__cc3k___p__) */
