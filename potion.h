//
//  potion.h
//  cc3k
//
//  Created by Ning Ma on 7/21/13.
//  Copyright (c) 2013 Ning Ma. All rights reserved.
//

#ifndef __cc3k__potion__
#define __cc3k__potion__

#include <iostream>
#include <string>
#include "item.h"

class PC;
class Potion: public Item{
protected:
  std::string type;
  
public:
  Potion(std::string s);
  ~Potion();
  std::string getType();
  void function(PC* pc);
};



#endif /* defined(__cc3k__potion__) */
