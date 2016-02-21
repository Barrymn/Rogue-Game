//
//  treasure.h
//  cc3k
//
//  Created by Ning Ma on 7/21/13.
//  Copyright (c) 2013 Ning Ma. All rights reserved.
//

#ifndef __cc3k__treasure__
#define __cc3k__treasure__

#include <iostream>
#include "item.h"

class PC;
class Treasure: public Item{
protected:
  const int gold;

public:
  Treasure(int gold);
  virtual ~Treasure();
  void function(PC* pc);
  int getGold();
};


#endif /* defined(__cc3k__treasure__) */
