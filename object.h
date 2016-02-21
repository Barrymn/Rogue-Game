//
//  object.h
//  cc3k
//
//  Created by Ning Ma on 7/20/13.
//  Copyright (c) 2013 Ning Ma. All rights reserved.
//

#ifndef __cc3k__object__
#define __cc3k__object__

#include <iostream>
class Object{
protected:
  char name;
  
public:
  Object(char n);
  virtual ~Object();
  char getName();
};


#endif /* defined(__cc3k__object__) */
