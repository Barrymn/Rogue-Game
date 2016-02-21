//
//  chamber.h
//  cc3k
//
//  Created by Ziquan Wang on 2013-07-21.
//  Copyright (c) 2013 Ziquan Wang. All rights reserved.
//

#ifndef __cc3k__chamber__
#define __cc3k__chamber__

#include <iostream>
#include "cell.h"

class Chamber {
  Cell** theChamber;
  int numCell;
  int capacity;
  void expand_capacity();
public:
  Chamber();
  ~Chamber();
  void addCell(Cell* c);
  int getNum();
  Cell* getCell(int i);
};

#endif /* defined(__cc3k__chamber__) */
