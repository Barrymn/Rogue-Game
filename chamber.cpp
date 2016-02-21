//
//  chamber.cpp
//  cc3k
//
//  Created by Ziquan Wang on 2013-07-21.
//  Copyright (c) 2013 Ziquan Wang. All rights reserved.
//

#include "chamber.h"
#include <cstdlib>
using namespace std;

Chamber::Chamber(): theChamber(NULL), numCell(0), capacity(0) {}

Chamber::~Chamber() {
  delete[] theChamber;
}

void Chamber::expand_capacity() {	//expand chamber i's capacity
  if (capacity == 0) {
    capacity = 1;
  } else {
    capacity = 2 * capacity;
  }
  
  theChamber = static_cast<Cell**>(realloc(theChamber, capacity * sizeof(Cell*)));
  if (theChamber == NULL) {
    cout << "Reallocate Failed, Exit" << endl;
    exit(EXIT_FAILURE);	// if reallocating failed, program
  }		// terminates with status FAILURE
}

void Chamber::addCell(Cell* c) {
  if (numCell >= capacity - 1) {
    expand_capacity();
  }
  theChamber[numCell] = c;
  numCell++;
}

int Chamber::getNum() {
  return numCell;
}

Cell* Chamber::getCell(int i) {
  return theChamber[i];
}

