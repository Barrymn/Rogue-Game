//
//  item.h
//  cc3k
//
//  Created by Ning Ma on 7/20/13.
//  Copyright (c) 2013 Ning Ma. All rights reserved.
//

#ifndef __cc3k__item__
#define __cc3k__item__

#include <iostream>
#include "pc.h"
#include "object.h"

class Item: public Object{
  
public:
  Item(char n);
  virtual ~Item();
  virtual void function(PC* pc) = 0;
};



#endif /* defined(__cc3k__item__) */
