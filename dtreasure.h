//
//  dtreasure.h
//  cc3k
//
//  Created by Ning Ma on 7/21/13.
//  Copyright (c) 2013 Ning Ma. All rights reserved.
//

#ifndef __cc3k__dtreasure__
#define __cc3k__dtreasure__

#include <iostream>
#include "treasure.h"

class DTreasure: public Treasure{
protected:
  bool dead;
public:
  DTreasure();
  ~DTreasure();
  void setDead();
  bool getDead();
};

#endif /* defined(__cc3k__dtreasure__) */
