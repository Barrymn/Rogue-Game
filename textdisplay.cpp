//
//  textdisplay.cpp
//  cc3k
//
//  Created by Ziquan Wang on 2013-07-20.
//  Copyright (c) 2013 Ziquan Wang. All rights reserved.
//

#include "textdisplay.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

TextDisplay::TextDisplay(int w, int l): w(w), l(l), action("") {
  display = new char*[w];
  for (int i = 0; i < w; i++) {
    display[i] = new char[l];
  }
}

TextDisplay::~TextDisplay(){
  for (int i = 0; i < w; i++) {
    delete[] display[i];
  }
  delete[] display;
}

void TextDisplay::notify(int r, int c, char ch) {
  display[r][c] = ch;
}

void TextDisplay::pcUpdate(PC* pc, int numP) {
  this->numP = numP;
  this->race = pc->getRace();
  this->gold = pc->getGold();
  this->hp = pc->getHp();
  this->atk = pc->getAtk();
  this->def = pc->getDef();
}

void TextDisplay::actionUpdate(string action) {
  this->action = action;
}

void TextDisplay::floorUpdate(int floor) {
  this->floor = floor;
}

ostream& operator<<(ostream &out, const TextDisplay &td) {
  out << "Floor " << td.floor << endl;
  for (int i = 0; i < td.w; i++) {
    for (int j = 0; j < td.l; j++) {
      out << td.display[i][j];
    }
    out << endl;
  }
  out << "Race: " << td.race << " Gold: " << td.gold << endl;
  out << "HP: " << td.hp << endl;
  out << "Atk: " << td.atk << endl;
  out << "Def: " << td.def << endl;
  out << "Action: " << td.action << endl;
  out << "Potions: " << td.numP << " (max 5)" << endl;
  return out;
}
