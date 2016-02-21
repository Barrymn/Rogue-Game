//
//  floor.cpp
//  cc3k
//
//  Created by Ziquan Wang on 2013-07-20.
//  Copyright (c) 2013 Ziquan Wang. All rights reserved.
//

#include "floor.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <sstream>
using namespace std;

PC* character;	// global variable, shared by main and floors

Floor::Floor(int w, int l): f(0), w(w), l(l), r(0), c(0), numP(0) {
  po = new Potion*[5];
  chamber = new Chamber[numChamber];
  theFloor = new Cell*[w];
  for (int i = 0; i < w; i++) {
    theFloor[i] = new Cell[l];
  }
  td = new TextDisplay(w, l);
}


Floor::~Floor() {
  for (int i = 0; i < w; i++) {
    delete[] theFloor[i];
  }
  delete[] theFloor;
  for (int i = 0; i < numP; i++) {
    delete po[i];
  }
  delete[] po;
  delete td;
}

void Floor::init(string map){
  this->map = map;
  ifstream in(map.c_str());
  string s;
  
  for (int i = 0; i < w; i++) {
    getline(in, s);
    for (int j = 0; j < l; j++) {
      theFloor[i][j].set(s[j], i, j);
      if (48 <= s[j] && s[j] <= 52) {
        chamber[s[j] - 48].addCell(&theFloor[i][j]);
      }
    }
  }
}

void Floor::newGame(Object* pc) {
  f = 1;
  pcSpawn(pc);
  potionSpawn();
  treasureSpawn();
  enemySpawn();
}


void Floor::newLevel() {
  int HP = character->getHp();
  int gold = character->getGold();
  string race = character->getRace();
  
  for (int i = 0; i < w; i++) {
    for (int j = 0; j < l; j++) {
      theFloor[i][j].remove();
    }
  }
  init(map);
  f += 1;
  if (race == "Human") {
    character = new Human(HP,gold);
    pcSpawn(character);
  }
  else if (race == "Elves") {
    character = new Elves(HP,gold);
    pcSpawn(character);
  }
  else if (race == "Dwarf") {
    character = new Dwarf(HP,gold);
    pcSpawn(character);
  }
  else if (race == "Ironman") {
    character = new Ironman(HP,gold);
    pcSpawn(character);
  }
  else /* (race == "Orc") */ {
    character = new Orc(HP,gold);
    pcSpawn(character);
  }
  potionSpawn();
  treasureSpawn();
  enemySpawn();
}

int Floor::getF() {
  return f;
}

void Floor::notifyTd() {
  for (int i = 0; i < w; i++) {
    for (int j = 0; j < l; j++) {
      td->notify(i, j, theFloor[i][j].getname());
    }
  }
  pcNotify();
  floorNotify();
}

void Floor::pcNotify() {
  td->pcUpdate(character, numP);
}

void Floor::floorNotify() {
  td->floorUpdate(f);
}

void Floor::actionNotify(string s) {
  td->actionUpdate(s);
}

Cell* Floor::randomCell() {
  Cell* c;
  int i = rand() % numChamber;
  int j = rand() % chamber[i].getNum();
  c = chamber[i].getCell(j);
  return c;
}

void Floor::pcSpawn(Object* pc) {
  srand(time(NULL));
  int i;		// pc chamber
  int j;		// stair location
  int k;		// tail in chamber
  i = rand() % numChamber;	// determine pc chamber
  
  while (true) {		// determine stair chamber
    j = rand() % numChamber;
    if (j != i) break;
  }
  
  k = rand() % chamber[i].getNum();	// spawn pc
  (chamber[i].getCell(k))->occupy(pc);
  r = (chamber[i].getCell(k))->getR();
  c = (chamber[i].getCell(k))->getC();
  
  k = rand() % chamber[j].getNum();	// spawn stair
  (chamber[j].getCell(k))->occupy(new Stair);
  actionNotify("Player character has spawned");
}


void Floor::potionSpawn() {
  int type;
  for (int i = 0; i < numPotion; i++) {
    type = rand() % 6;
    Cell* c;		// find a unoccupied tile
    while (true) {
      c = randomCell();
      if (c->getname() == '.') {
        break;
      }
    }
    switch(type) {		// add a pointer of potion
      case 0:
        c->occupy(new Potion("RH"));
        break;
      case 1:
        c->occupy(new Potion("BA"));
        break;
      case 2:
        c->occupy(new Potion("BD"));
        break;
      case 3:
        c->occupy(new Potion("PH"));
        break;
      case 4:
        c->occupy(new Potion("WA"));
        break;
      case 5:
        c->occupy(new Potion("WD"));
        break;
    }
  }
}

void Floor::treasureSpawn() {
  int type;
  for (int i = 0; i < numTreasure; i++) {
    type = rand() % 8;
    Cell* c;
    while (true) {
      c = randomCell();
      if (c->getname() == '.') {
        break;
      }
    }
    switch(type) {
      case 0:
      case 1:
      case 2:
      case 3:
      case 4:
        c->occupy(new Treasure(2));
        break;
      case 5:
      case 6:
        c->occupy(new Treasure(1));
        break;
      case 7:
        int i = c->getR();
        int j = c->getC();
        Cell* tCell = NULL;	// find an empty cell to put treasure
        if (theFloor[i - 1][j - 1].getname() == '.') {
          tCell = &theFloor[i - 1][j - 1];
        }
        else if (theFloor[i - 1][j].getname() == '.') {
          tCell = &theFloor[i - 1][j];
        }
        else if (theFloor[i - 1][j + 1].getname() == '.') {
          tCell = &theFloor[i - 1][j + 1];
        }
        else if (theFloor[i][j - 1].getname() == '.') {
          tCell = &theFloor[i][j - 1];
        }
        else if (theFloor[i][j + 1].getname() == '.') {
          tCell = &theFloor[i][j + 1];
        }
        else if (theFloor[i + 1][j - 1].getname() == '.') {
          tCell = &theFloor[i + 1][j - 1];
        }
        else if (theFloor[i + 1][j].getname() == '.') {
          tCell = &theFloor[i + 1][j];
        }
        else /* (theFloor[i + 1][j + 1].getname() == '.') */{
          tCell = &theFloor[i + 1][j + 1];
        }
        if (tCell != NULL) {
          DTreasure* dt = new DTreasure;
          Dragon* d = new Dragon(dt);
          tCell->occupy(d);
          c->occupy(dt);
        }
        break;
    }
  }
}

void Floor::enemySpawn() {
  int type;
  for (int i = 0; i < numEnemy; i++) {	// spawn enemy
    type = rand() % 18;
    Cell* c;
    while (true) {
      c = randomCell();
      if (c->getname() == '.') {
        break;
      }
    }
    switch(type) {
      case 0:
      case 1:
      case 2:
        c->occupy(new Werewolf);
        break;
      case 3:
      case 4:
      case 5:
        c->occupy(new Vampire);
        break;
      case 6:
      case 7:
      case 8:
      case 9:
        c->occupy(new Goblin);
        break;
      case 10:
      case 11:
        c->occupy(new Snake);
        break;
      case 12:
      case 13:
        c->occupy(new Troll);
        break;
      case 14:
      case 15:
        c->occupy(new Phoenix);
        break;
      case 16:
      case 17:
        c->occupy(new Merchant);
        break;
    }
  }
}


void Floor::enemyMove() {
  char name;
  int random;
  for (int i = 0; i < w; i++) {
    for (int j = 0; j < l; j++) {
      name = theFloor[i][j].getname();
      if ((name == 'V' || name == 'W' || name == 'N' ||
          name == 'M' || name == 'X' || name == 'T' || name == 'S') &&
          !(dynamic_cast<Enemy*>(theFloor[i][j].getObj())->getMoved())) {
        dynamic_cast<Enemy*>(theFloor[i][j].getObj())->move();
        random = rand() % 8;
        for (int k = random; k < random + 8; k++) { // if the enemy is not been moved before, move it to an adjacent cell
          if (k % 8 == 0 && theFloor[i - 1][j - 1].getname() == '.') {
            theFloor[i - 1][j - 1].occupy(theFloor[i][j].disoccupy());
            break;
          }
          if (k % 8 == 1 && theFloor[i - 1][j].getname() == '.') {
            theFloor[i - 1][j].occupy(theFloor[i][j].disoccupy());
            break;
          }
          if (k % 8 == 2 && theFloor[i - 1][j + 1].getname() == '.') {
            theFloor[i - 1][j + 1].occupy(theFloor[i][j].disoccupy());
            break;
          }
          if (k % 8 == 3 && theFloor[i][j - 1].getname() == '.') {
            theFloor[i][j - 1].occupy(theFloor[i][j].disoccupy());
            break;
          }
          if (k % 8 == 4 && theFloor[i][j + 1].getname() == '.') {
            theFloor[i][j + 1].occupy(theFloor[i][j].disoccupy());
            break;
          }
          if (k % 8 == 5 && theFloor[i + 1][j - 1].getname() == '.') {
            theFloor[i + 1][j - 1].occupy(theFloor[i][j].disoccupy());
            break;
          }
          if (k % 8 == 6 && theFloor[i + 1][j].getname() == '.') {
            theFloor[i + 1][j].occupy(theFloor[i][j].disoccupy());
            break;
          }
          if (k % 8 == 7 && theFloor[i + 1][j + 1].getname() == '.'){
            theFloor[i + 1][j + 1].occupy(theFloor[i][j].disoccupy());
            break;
          }
        } // for
      } // if
    } // for
  } // for
  for (int i = 0; i < w; i++) {// change all moved state again for next turn
    for (int j = 0; j < l; j++) {
      name = theFloor[i][j].getname();
      if (name == 'V' || name == 'W' || name == 'N' || name == 'M' ||
          name == 'X' || name == 'T' || name == 'S' ) {
        dynamic_cast<Enemy*>(theFloor[i][j].getObj())->move();
      } // if
    } // for
  } // for
}


void Floor::pcMove(int i) { // update display!!!!!
  PC* pc = dynamic_cast<PC*> (theFloor[r][c].getObj());
  Treasure* t;
  DTreasure* d;
  Enemy* e;
  Merchant* m;
  Potion* p;
  Stair* st;
  stringstream ss1;
  stringstream ss2;
  stringstream ss3;
  stringstream ss4;
  string damage;
  int pnum = 0;
  string nump;
  string gold;
  string s;
  string s1 = "";
  string s2 = "";
  string s3 = "";
  string s4 = "";
  string s5 = "";
  switch(i) {
    case 0:
      st = dynamic_cast<Stair*>(theFloor[r - 1][c - 1].getObj());
      if (st != NULL) {
        newLevel();
        actionNotify("PC arrived next floor");
        return;
      }
      t = dynamic_cast<Treasure*>(theFloor[r - 1][c - 1].getObj());
      if (t != NULL) {	// step on treasure
        
        d = dynamic_cast<DTreasure*>(t); // see whether dragon hoard
        if (d != NULL && !d->getDead()) {
          s1 = "You must kill dragon to get the treasure.";
          break;
        }
        
        t->function(pc);
        ss1 << t->getGold();
        ss1 >> gold;
        s2 = " PC gets "+gold+" gold.";
        theFloor[r - 1][c - 1].remove();
      }
      if (!theFloor[r - 1][c - 1].occupant()) { // move
        theFloor[r - 1][c - 1].occupy(theFloor[r][c].disoccupy());
        r = r - 1;
        c = c - 1;
        s1 = "PC moves north west.";
      }
      break;
      
    case 1:
      st = dynamic_cast<Stair*>(theFloor[r - 1][c].getObj());
      if (st != NULL) {
        newLevel();
        actionNotify("PC arrived next floor");
        return;
      }
      t = dynamic_cast<Treasure*>(theFloor[r - 1][c].getObj());
      if (t != NULL) {
        
        d = dynamic_cast<DTreasure*>(t); // see whether dragon hoard
        if (d != NULL && !d->getDead()) {
          s1 = "You must kill dragon to get the treasure.";
          break;
        }
        
        t->function(pc);
        ss1 << t->getGold();
        ss1 >> gold;
        s2 = " PC gets "+gold+" gold.";
        theFloor[r - 1][c].remove();
      }
      if (!theFloor[r - 1][c].occupant()) {
        theFloor[r - 1][c].occupy(theFloor[r][c].disoccupy());
        r = r - 1;
        s1 = "PC moves north.";
      }
      break;
      
    case 2:
      st = dynamic_cast<Stair*>(theFloor[r - 1][c + 1].getObj());
      if (st != NULL) {
        newLevel();
        actionNotify("PC arrived next floor");
        return;
      }
      t = dynamic_cast<Treasure*>(theFloor[r - 1][c + 1].getObj());
      if (t != NULL) {
        
        d = dynamic_cast<DTreasure*>(t); // see whether dragon hoard
        if (d != NULL && !d->getDead()) {
          s1 = "You must kill dragon to get the treasure.";
          break;
        }
        
        t->function(pc);
        ss1 << t->getGold();
        ss1 >> gold;
        s2 = " PC gets "+gold+" gold.";
        theFloor[r - 1][c + 1].remove();
      }
      if (!theFloor[r - 1][c + 1].occupant()) {
        theFloor[r - 1][c + 1].occupy(theFloor[r][c].disoccupy());
        r = r - 1;
        c = c + 1;
        s1 = "PC moves north east.";
      }
      break;
      
    case 3:
      st = dynamic_cast<Stair*>(theFloor[r][c - 1].getObj());
      if (st != NULL) {
        newLevel();
        actionNotify("PC arrived next floor");
        return;
      }
      t = dynamic_cast<Treasure*>(theFloor[r][c - 1].getObj());
      if (t != NULL) {
        
        d = dynamic_cast<DTreasure*>(t); // see whether dragon hoard
        if (d != NULL && !d->getDead()) {
          s1 = "You must kill dragon to get the treasure.";
          break;
        }
        
        t->function(pc);
        ss1 << t->getGold();
        ss1 >> gold;
        s2 = " PC gets "+gold+" gold.";
        theFloor[r][c - 1].remove();
      }
      if (!theFloor[r][c - 1].occupant()) {
        theFloor[r][c - 1].occupy(theFloor[r][c].disoccupy());
        c = c - 1;
        s1 = "PC moves west.";
      }
      break;
      
    case 4:
      st = dynamic_cast<Stair*>(theFloor[r][c + 1].getObj());
      if (st != NULL) {
        newLevel();
        actionNotify("PC arrived next floor");
        return;
      }
      t = dynamic_cast<Treasure*>(theFloor[r][c + 1].getObj());
      if (t != NULL) {
        
        d = dynamic_cast<DTreasure*>(t); // see whether dragon hoard
        if (d != NULL && !d->getDead()) {
          s1 = "You must kill dragon to get the treasure.";
          break;
        }
        
        t->function(pc);
        ss1 << t->getGold();
        ss1 >> gold;
        s2 = " PC gets "+gold+" gold.";
        theFloor[r][c + 1].remove();
      }
      if (!theFloor[r][c + 1].occupant()) {
        theFloor[r][c + 1].occupy(theFloor[r][c].disoccupy());
        c = c + 1;
        s1 = "PC moves east.";
      }
      break;
      
    case 5:
      st = dynamic_cast<Stair*>(theFloor[r + 1][c - 1].getObj());
      if (st != NULL) {
        newLevel();
        actionNotify("PC arrived next floor");
        return;
      }
      t = dynamic_cast<Treasure*>(theFloor[r + 1][c - 1].getObj());
      if (t != NULL) {
        
        d = dynamic_cast<DTreasure*>(t); // see whether dragon hoard
        if (d != NULL && !d->getDead()) {
          s1 = "You must kill dragon to get the treasure.";
          break;
        }
        
        t->function(pc);
        ss1 << t->getGold();
        ss1 >> gold;
        s2 = " PC gets "+gold+" gold.";
        theFloor[r + 1][c - 1].remove();
      }
      if (!theFloor[r + 1][c - 1].occupant()) {
        theFloor[r + 1][c - 1].occupy(theFloor[r][c].disoccupy());
        r = r + 1;
        c = c - 1;
        s1 = "PC moves south west.";
      }
      break;
      
    case 6:
      st = dynamic_cast<Stair*>(theFloor[r + 1][c].getObj());
      if (st != NULL) {
        newLevel();
        actionNotify("PC arrived next floor");
        return;
      }
      t = dynamic_cast<Treasure*>(theFloor[r + 1][c].getObj());
      if (t != NULL) {
        
        d = dynamic_cast<DTreasure*>(t); // see whether dragon hoard
        if (d != NULL && !d->getDead()) {
          s1 = "You must kill dragon to get the treasure.";
          break;
        }
        
        t->function(pc);
        ss1 << t->getGold();
        ss1 >> gold;
        s2 = " PC gets "+gold+" gold.";
        theFloor[r + 1][c].remove();
      }
      if (!theFloor[r + 1][c].occupant()) {
        theFloor[r + 1][c].occupy(theFloor[r][c].disoccupy());
        r = r + 1;
        s1 = "PC moves south.";
      }
      break;
      
    case 7:
      st = dynamic_cast<Stair*>(theFloor[r + 1][c + 1].getObj());
      if (st != NULL) {
        newLevel();
        actionNotify("PC arrived next floor");
        return;
      }
      t = dynamic_cast<Treasure*>(theFloor[r + 1][c + 1].getObj());
      if (t != NULL) {
        
        d = dynamic_cast<DTreasure*>(t); // see whether dragon hoard
        if (d != NULL && !d->getDead()) {
          s1 = "You must kill dragon to get the treasure.";
          break;
        }
        
        t->function(pc);
        ss1 << t->getGold();
        ss1 >> gold;
        s2 = " PC gets "+gold+" gold.";
        theFloor[r + 1][c + 1].remove();
      }
      if (!theFloor[r + 1][c + 1].occupant()) {
        theFloor[r + 1][c + 1].occupy(theFloor[r][c].disoccupy());
        r = r + 1;
        c = c + 1;
        s1 = "PC moves south east.";
      }
      break;
  }
  // enemy attack loop
  for (int i = r - 1; i <= r + 1; i++) { // get attacked by enemies around pc
    for (int j = c - 1; j <= c + 1; j++) {
      p = dynamic_cast<Potion*>(theFloor[i][j].getObj());
      if (p != NULL) {
        pnum++;
      } else {
        e = dynamic_cast<Enemy*>(theFloor[i][j].getObj());
        if (e != NULL){
          m = dynamic_cast<Merchant*>(e); // determine if merchant if hostile
          if (m != NULL && m->getHostile() == false) {
            break;
          }
          damage = pc->attacked(e->attack());
          if(e->getRace() == "Goblin" && damage != "0"){
            if(pc->getGold() == 0){
              s4 = s4 + " Goblin steals nothing.";
            }
            else{
              pc->setGold(pc->getGold()-1);
              s4 = s4 + " Goblin steals 1 gold.";
            }
          }
          if(e->getRace() == "Vampire" && damage != "0"){
            pc->setHp(pc->getHp()-5);
            e->setHp(e->getHp()+5);
            s4 = s4 + " Vampire steals 5 HP.";
          }
          if(e->getRace() == "Werewolf" && rand() % 2 == 0 && damage != "0"){
            int x;
            ss3 << damage;
            ss3 >> x;
            x = x*2;
            ss4 << x;
            ss4 >> damage;
            s5 = " Werewolf deals 2X damage! ";
          }
          if(damage == "0"){
            s4 = s4+" "+e->getRace()+" misses.";
          } else{
            s4 = s4+" "+e->getRace()+" deals "+damage+" damage to PC.";
          } // if
        } // if
      } // if
    } // for
  } // for
  
  if (pnum != 0) {	// see potions
    ss2 << pnum;
    ss2 >> nump;
    s3 = " PC sees "+nump+" potion";
    if(nump == "1"){
      s3 = s3 + ".";
    }
    else{
      s3 = s3 + "s.";
    }
  }
  
  s = s1 + s2 + s3 + s5 + s4;
  actionNotify(s);
  
}


void Floor::pcAttack(int i) {
  Enemy* e;
  Merchant* m;
  string s = "";
  string s1 = "";
  string s2 = "";
  string s3 = "";
  stringstream ss1;
  stringstream ss2;
  stringstream ss3;
  stringstream ss4;
  string damage1;
  string damage2;
  string enemy;
  string hp;
  PC* pc = dynamic_cast<PC*> (theFloor[r][c].getObj());
  switch(i) {
    case 0:
      e = dynamic_cast<Enemy*> (theFloor[r - 1][c - 1].getObj());
      if (e != NULL) {
        damage1 = e->attacked(pc->attack());
        ss1 << e->getHp();
        ss1 >> hp;
        ss2 << e->getName();
        ss2 >> enemy;
        if (!e->getAlive()){
          s1 = "PC deals "+damage1+" damage to "+enemy+" (killed). PC gets 1 gold.";
          if(pc->getRace() == "Dwarf"){
            pc->setGold(pc->getGold()+2);
          }
          if(pc->getRace() != "Dwarf" && pc->getRace() != "Orc" ){
            pc->setGold((pc->getGold()+1));
          }
          if (dynamic_cast<Merchant*>(e) != NULL) { // put merchant horde
            theFloor[r - 1][c - 1].remove();
            theFloor[r - 1][c - 1].occupy(new Treasure(4));
            s1 = s1 + " merchant drops a treasure.";
          } else {
            theFloor[r - 1][c - 1].remove();
          }
        } else{
          s1 = "PC deals "+damage1+" damage to "+enemy+" ("+hp+" HP).";
        }
      }
      break;
    case 1:
      e = dynamic_cast<Enemy*> (theFloor[r - 1][c].getObj());
      if (e != NULL) {
        damage1 = e->attacked(pc->attack());
        ss1 << e->getHp();
        ss1 >> hp;
        ss2 << e->getName();
        ss2 >> enemy;
        if (!e->getAlive()){
          s1 = "PC deals "+damage1+" damage to "+enemy+" (killed). PC gets 1 gold.";
          if(pc->getRace() == "Dwarf"){
            pc->setGold(pc->getGold()+2);
          }
          if(pc->getRace() != "Dwarf" && pc->getRace() != "Orc" ){
            pc->setGold((pc->getGold()+1));
          }
          if (dynamic_cast<Merchant*>(e) != NULL) {
            theFloor[r - 1][c].remove();
            theFloor[r - 1][c].occupy(new Treasure(4));
            s1 = s1 + " merchant drops a treasure.";
          } else {
            theFloor[r - 1][c].remove();
          }
        } else{
          s1 = "PC deals "+damage1+" damage to "+enemy+" ("+hp+" HP).";
        }
      }
      break;
    case 2:
      e = dynamic_cast<Enemy*> (theFloor[r - 1][c + 1].getObj());
      if (e != NULL) {
        damage1 = e->attacked(pc->attack());
        ss1 << e->getHp();
        ss1 >> hp;
        ss2 << e->getName();
        ss2 >> enemy;
        if (!e->getAlive()){
          s1 = "PC deals "+damage1+" damage to "+enemy+" (killed). PC gets 1 gold.";
          if(pc->getRace() == "Dwarf"){
            pc->setGold(pc->getGold()+2);
          }
          if(pc->getRace() != "Dwarf" && pc->getRace() != "Orc" ){
            pc->setGold((pc->getGold()+1));
          }
          if (dynamic_cast<Merchant*>(e) != NULL) {
            theFloor[r - 1][c + 1].remove();
            theFloor[r - 1][c + 1].occupy(new Treasure(4));
            s1 = s1 + " merchant drops a treasure.";
          } else {
            theFloor[r - 1][c + 1].remove();
          }
        } else{
          s1 = "PC deals "+damage1+" damage to "+enemy+" ("+hp+" HP).";
        }
      }
      break;
    case 3:
      e = dynamic_cast<Enemy*> (theFloor[r][c - 1].getObj());
      if (e != NULL) {
        damage1 = e->attacked(pc->attack());
        ss1 << e->getHp();
        ss1 >> hp;
        ss2 << e->getName();
        ss2 >> enemy;
        if (!e->getAlive()){
          s1 = "PC deals "+damage1+" damage to "+enemy+" (killed). PC gets 1 gold.";
          if(pc->getRace() == "Dwarf"){
            pc->setGold(pc->getGold()+2);
          }
          if(pc->getRace() != "Dwarf" && pc->getRace() != "Orc" ){
            pc->setGold((pc->getGold()+1));
          }
          if (dynamic_cast<Merchant*>(e) != NULL) {
            theFloor[r][c - 1].remove();
            theFloor[r][c - 1].occupy(new Treasure(4));
            s1 = s1 + " merchant drops a treasure.";
          } else {
            theFloor[r][c - 1].remove();
          }
        } else{
          s1 = "PC deals "+damage1+" damage to "+enemy+" ("+hp+" HP).";
        }
      }
      break;
    case 4:
      e = dynamic_cast<Enemy*> (theFloor[r][c + 1].getObj());
      if (e != NULL) {
        damage1 = e->attacked(pc->attack());
        ss1 << e->getHp();
        ss1 >> hp;
        ss2 << e->getName();
        ss2 >> enemy;
        if (!e->getAlive()){
          s1 = "PC deals "+damage1+" damage to "+enemy+" (killed). PC gets 1 gold.";
          if(pc->getRace() == "Dwarf"){
            pc->setGold(pc->getGold()+2);
          }
          if(pc->getRace() != "Dwarf" && pc->getRace() != "Orc" ){
            pc->setGold((pc->getGold()+1));
          }
          if (dynamic_cast<Merchant*>(e) != NULL) {
            theFloor[r][c + 1].remove();
            theFloor[r][c + 1].occupy(new Treasure(4));
            s1 = s1 + " merchant drops a treasure.";
          } else {
            theFloor[r][c + 1].remove();
          }
        } else{
          s1 = "PC deals "+damage1+" damage to "+enemy+" ("+hp+" HP).";
        }
      }
      break;
    case 5:
      e = dynamic_cast<Enemy*> (theFloor[r + 1][c - 1].getObj());
      if (e != NULL) {
        damage1 = e->attacked(pc->attack());
        ss1 << e->getHp();
        ss1 >> hp;
        ss2 << e->getName();
        ss2 >> enemy;
        if (!e->getAlive()){
          s1 = "PC deals "+damage1+" damage to "+enemy+" (killed). PC gets 1 gold.";
          if(pc->getRace() == "Dwarf"){
            pc->setGold(pc->getGold()+2);
          }
          if(pc->getRace() != "Dwarf" && pc->getRace() != "Orc" ){
            pc->setGold((pc->getGold()+1));
          }
          if (dynamic_cast<Merchant*>(e) != NULL) {
            theFloor[r + 1][c - 1].remove();
            theFloor[r + 1][c - 1].occupy(new Treasure(4));
            s1 = s1 + " merchant drops a treasure.";
          } else {
            theFloor[r + 1][c - 1].remove();
          }
        } else{
          s1 = "PC deals "+damage1+" damage to "+enemy+" ("+hp+" HP).";
        }
      }
      break;
    case 6:
      e = dynamic_cast<Enemy*> (theFloor[r + 1][c].getObj());
      if (e != NULL) {
        damage1 = e->attacked(pc->attack());
        ss1 << e->getHp();
        ss1 >> hp;
        ss2 << e->getName();
        ss2 >> enemy;
        if (!e->getAlive()){
          s1 = "PC deals "+damage1+" damage to "+enemy+" (killed). PC gets 1 gold.";
          if(pc->getRace() == "Dwarf"){
            pc->setGold(pc->getGold()+2);
          }
          if(pc->getRace() != "Dwarf" && pc->getRace() != "Orc" ){
            pc->setGold((pc->getGold()+1));
          }
          if (dynamic_cast<Merchant*>(e) != NULL) {
            theFloor[r + 1][c].remove();
            theFloor[r + 1][c].occupy(new Treasure(4));
            s1 = s1 + " merchant drops a treasure.";
          } else {
            theFloor[r + 1][c].remove();
          }
        } else{
          s1 = "PC deals "+damage1+" damage to "+enemy+" ("+hp+" HP).";
        }
      }
      break;
    case 7:
      e = dynamic_cast<Enemy*> (theFloor[r + 1][c + 1].getObj());
      if (e != NULL) {
        damage1 = e->attacked(pc->attack());
        ss1 << e->getHp();
        ss1 >> hp;
        ss2 << e->getName();
        ss2 >> enemy;
        if (!e->getAlive()){
          s1 = "PC deals "+damage1+" damage to "+enemy+" (killed). PC gets 1 gold.";
          if(pc->getRace() == "Dwarf"){
            pc->setGold(pc->getGold()+2);
          }
          if(pc->getRace() != "Dwarf" && pc->getRace() != "Orc" ){
            pc->setGold((pc->getGold()+1));
          }
          if (dynamic_cast<Merchant*>(e) != NULL) {
            theFloor[r + 1][c + 1].remove();
            theFloor[r + 1][c + 1].occupy(new Treasure(4));
            s1 = s1 + " merchant drops a treasure.";
          } else {
            theFloor[r + 1][c + 1].remove();
          }
        } else{
          s1 = "PC deals "+damage1+" damage to "+enemy+" ("+hp+" HP).";
        }
      }
      break;
  }
  
  for (int i = r - 1; i <= r + 1; i++) { // get attacked by enemies around pc
    for (int j = c - 1; j <= c + 1; j++) {
      e = dynamic_cast<Enemy*>(theFloor[i][j].getObj());
      if (e != NULL) {
        m = dynamic_cast<Merchant*>(e); // determine if merchant is hostile
        if(m != NULL && m->getHostile() == false) {
          break;
        }
        damage2 = pc->attacked(e->attack());
        if(e->getRace() == "Goblin" && damage2 != "0"){
          if(pc->getGold() == 0){
            s2 = s2 + " Goblin steals nothing.";
          }
          else{
            pc->setGold(pc->getGold()-1);
            s2 = s2 + " Goblin steals 1 gold.";
          }
        }
        if(e->getRace() == "Vampire" && damage2 != "0"){
          pc->setHp(pc->getHp()-5);
          e->setHp(e->getHp()+5);
          s2 = s2 + " Vampire steals 5 HP.";
        }
        if(e->getRace() == "Werewolf" && rand() % 2 == 0 && damage2 != "0"){
          int x;
          ss3 << damage2;
          ss3 >> x;
          x = x*2;
          ss4 << x;
          ss4 >> damage2;
          s3 = " Werewolf deals 2X damage! ";
        }
        if(damage2 == "0"){
          s2 = s2+" "+e->getRace()+" misses.";
        }
        else{
          s2 = s2+" "+e->getRace()+" deals "+damage2+" damage to PC.";
        }
      } // if
    } // for
  } // for
  
  s = s1 + s3 + s2;
  actionNotify(s);
}


void Floor::pcUse(int i) {
  Enemy* e;
  Merchant* m;
  Potion* p;
  PC* pc = dynamic_cast<PC*> (theFloor[r][c].getObj());
  string damage;
  string s = "";
  string s1 = "";
  string s2 = "";
  string s3 = "";
  stringstream ss1;
  stringstream ss2;
  switch(i) {
    case 0:
      p = dynamic_cast<Potion*> (theFloor[r - 1][c - 1].getObj());
      if (p != NULL) {
        p->function(character);
        s1 = "PC uses "+p->getType()+".";
        theFloor[r - 1][c - 1].remove();
      }
      break;
    case 1:
      p = dynamic_cast<Potion*> (theFloor[r - 1][c].getObj());
      if (p != NULL) {
        p->function(character);
        s1 = "PC uses "+p->getType()+".";
        theFloor[r - 1][c].remove();
      }
      break;
    case 2:
      p = dynamic_cast<Potion*> (theFloor[r - 1][c + 1].getObj());
      if (p != NULL) {
        p->function(character);
        s1 = "PC uses "+p->getType()+".";
        theFloor[r - 1][c + 1].remove();
      }
      break;
    case 3:
      p = dynamic_cast<Potion*> (theFloor[r][c - 1].getObj());
      if (p != NULL) {
        p->function(character);
        s1 = "PC uses "+p->getType()+".";
        theFloor[r][c - 1].remove();
      }
      break;
    case 4:
      p = dynamic_cast<Potion*> (theFloor[r][c + 1].getObj());
      if (p != NULL) {
        p->function(character);
        s1 = "PC uses "+p->getType()+".";
        theFloor[r][c + 1].remove();
      }
      break;
    case 5:
      p = dynamic_cast<Potion*> (theFloor[r + 1][c - 1].getObj());
      if (p != NULL) {
        p->function(character);
        s1 = "PC uses "+p->getType()+".";
        theFloor[r + 1][c - 1].remove();
      }
      break;
    case 6:
      p = dynamic_cast<Potion*> (theFloor[r + 1][c].getObj());
      if (p != NULL) {
        p->function(character);
        s1 = "PC uses "+p->getType()+".";
        theFloor[r + 1][c].remove();
      }
      break;
    case 7:
      p = dynamic_cast<Potion*> (theFloor[r + 1][c + 1].getObj());
      if (p != NULL) {
        p->function(character);
        s1 = "PC uses "+p->getType()+".";
        theFloor[r + 1][c + 1].remove();
      }
      break;
  } //switch
  
  // enemy attack loop
  for (int i = r - 1; i <= r + 1; i++) { // get attacked by enemies around pc
    for (int j = c - 1; j <= c + 1; j++) {
      e = dynamic_cast<Enemy*>(theFloor[i][j].getObj());
      if (e != NULL) {
        m = dynamic_cast<Merchant*>(e); // determine if merchant is hostile
        if(m != NULL && m->getHostile() == false) {
          break;
        }
        damage = pc->attacked(e->attack());
        if(e->getRace() == "Goblin" && damage != "0"){
          if(pc->getGold() == 0){
            s2 = s2 + " Goblin steals nothing.";
          }
          else{
            pc->setGold(pc->getGold()-1);
            s2 = s2 + " Goblin steals 1 gold.";
          }
        }
        if(e->getRace() == "Vampire" && damage != "0"){
          pc->setHp(pc->getHp()-5);
          e->setHp(e->getHp()+5);
          s2 = s2 + " Vampire steals 5 HP.";
        }
        if(e->getRace() == "Werewolf" && rand() % 2 == 0 && damage != "0"){
          int x;
          ss1 << damage;
          ss1 >> x;
          x = x*2;
          ss2 << x;
          ss2 >> damage;
          s3 = " Werewolf deals 2X damage! ";
        }
        if(damage == "0"){
          s2 = s2+" "+e->getRace()+" misses.";
        }
        else{
          s2 = s2+" "+e->getRace()+" deals "+damage+" damage to PC.";
        }
      } // if
    } // for
  } // for
  
  s = s1 + s3 + s2;
  actionNotify(s);
}


void Floor::pcGet(int i) {
  Enemy* e;
  Merchant* m;
  Potion* p;
  PC* pc = dynamic_cast<PC*> (theFloor[r][c].getObj());
  string damage;
  stringstream ss1;
  stringstream ss2;
  string s = "";
  string s1 = "";
  string s2 = "";
  string s3 = "";
  switch(i) {
    case 0:
      p = dynamic_cast<Potion*> (theFloor[r - 1][c - 1].getObj());
      if (p != NULL) {
        if (numP == 5) {
          s1 = "You can't get any more potion";
          break;
        }
        po[numP] = p;
        numP++;
        s1 = "PC gets an unknown potion";
        theFloor[r - 1][c - 1].disoccupy();
      }
      break;
    case 1:
      p = dynamic_cast<Potion*> (theFloor[r - 1][c].getObj());
      if (p != NULL) {
        if (numP == 5) {
          s1 = "You can't get any more potion";
          break;
        }
        po[numP] = p;
        numP++;
        s1 = "PC gets an unknown potion";
        theFloor[r - 1][c].disoccupy();
      }
      break;
    case 2:
      p = dynamic_cast<Potion*> (theFloor[r - 1][c + 1].getObj());
      if (p != NULL) {
        if (numP == 5) {
          s1 = "You can't get any more potion";
          break;
        }
        po[numP] = p;
        numP++;
        s1 = "PC gets an unknown potion";
        theFloor[r - 1][c + 1].disoccupy();
      }
      break;
    case 3:
      p = dynamic_cast<Potion*> (theFloor[r][c - 1].getObj());
      if (p != NULL) {
        if (numP == 5) {
          s1 = "You can't get any more potion";
          break;
        }
        po[numP] = p;
        numP++;
        s1 = "PC gets an unknown potion";
        theFloor[r][c - 1].disoccupy();
      }
      break;
    case 4:
      p = dynamic_cast<Potion*> (theFloor[r][c + 1].getObj());
      if (p != NULL) {
        if (numP == 5) {
          s1 = "You can't get any more potion";
          break;
        }
        po[numP] = p;
        numP++;
        s1 = "PC gets an unknown potion";
        theFloor[r][c + 1].disoccupy();
      }
      break;
    case 5:
      p = dynamic_cast<Potion*> (theFloor[r + 1][c - 1].getObj());
      if (p != NULL) {
        if (numP == 5) {
          s1 = "You can't get any more potion";
          break;
        }
        po[numP] = p;
        numP++;
        s1 = "PC gets an unknown potion";
        theFloor[r + 1][c - 1].disoccupy();
      }
      break;
    case 6:
      p = dynamic_cast<Potion*> (theFloor[r + 1][c].getObj());
      if (p != NULL) {
        if (numP == 5) {
          s1 = "You can't get any more potion";
          break;
        }
        po[numP] = p;
        numP++;
        s1 = "PC gets an unknown potion";
        theFloor[r + 1][c].disoccupy();
      }
      break;
    case 7:
      p = dynamic_cast<Potion*> (theFloor[r + 1][c + 1].getObj());
      if (p != NULL) {
        if (numP == 5) {
          s1 = "You can't get any more potion";
          break;
        }
        po[numP] = p;
        numP++;
        s1 = "PC gets an unknown potion";
        theFloor[r + 1][c + 1].disoccupy();
      }
      break;
  } //switch
  
  // enemy attack loop
  for (int i = r - 1; i <= r + 1; i++) { // get attacked by enemies around pc
    for (int j = c - 1; j <= c + 1; j++) {
      e = dynamic_cast<Enemy*>(theFloor[i][j].getObj());
      if (e != NULL) {
        m = dynamic_cast<Merchant*>(e); // determine if merchant is hostile
        if(m != NULL && m->getHostile() == false) {
          break;
        }
        damage = pc->attacked(e->attack());
        if(e->getRace() == "Goblin" && damage != "0"){
          if(pc->getGold() == 0){
            s2 = s2 + " Goblin steals nothing.";
          }
          else{
            pc->setGold(pc->getGold()-1);
            s2 = s2 + " Goblin steals 1 gold.";
          }
        }
        if(e->getRace() == "Vampire" && damage != "0"){
          pc->setHp(pc->getHp()-5);
          e->setHp(e->getHp()+5);
          s2 = s2 + " Vampire steals 5 HP.";
        }
        if(e->getRace() == "Werewolf" && rand() % 2 == 0 && damage != "0"){
          int x;
          ss1 << damage;
          ss1 >> x;
          x = x*2;
          ss2 << x;
          ss2 >> damage;
          s3 = " Werewolf deals 2X damage! ";
        }
        if(damage == "0"){
          s2 = s2+" "+e->getRace()+" misses.";
        }
        else{
          s2 = s2+" "+e->getRace()+" deals "+damage+" damage to PC.";
        }
      } // if
    } // for
  }// for
  
  s = s1 + s3 + s2;
  actionNotify(s);
}


void Floor::pcBuy(int poType, int poNum) { // buy potions from merchant
  bool flag = false;
  Enemy* e;
  Merchant* m;
  PC* pc = dynamic_cast<PC*> (theFloor[r][c].getObj());
  stringstream ss;
  stringstream ss1;
  stringstream ss2;
  string num;
  string damage;
  string s = "";
  string s1 = "";
  string s2 = "";
  string s3 = "";
  for (int i = r - 1; i <= r + 1; i++) { // find merchant
    for (int j = c - 1; j <= c + 1; j++) {
      m = dynamic_cast<Merchant*>(theFloor[i][j].getObj());
      if (m != NULL) {
        flag = true;
        break;
      }
    }
    if (flag) break;	// break from nested for loops
  }
    
  if (m == NULL) {
    s1 = "No merchant around.";
  }
  else if (m->getHostile()) {
    s1 = "Merchant refuses to sell potions to you.";
  }
  else if (poNum + numP > 5) {
    s1 = "Don't have enough space.";
  }
  else if (character->getGold() < poNum * 2) {
    s1 = "Don't have enough money.";
  }
  else {
    switch(poType) {
      case 'h':
        while (poNum > 0) {
          po[numP] = new Potion("RH");
          numP++;
          poNum--;
        }
        character->setGold(character->getGold() - numP * 2);
        ss << poNum;
        ss >> num;
        s1 = "PC buys "+num+" RH.";
        break;
      case 'a':
        while (poNum > 0) {
          po[numP] = new Potion("BA");
          numP++;
          poNum--;
        }
        character->setGold(character->getGold() - numP * 2);
        ss << poNum;
        ss >> num;
        s1 = "PC buys "+num+" BA.";
        break;
      case 'd':
        while (poNum > 0) {
          po[numP] = new Potion("BD");
          numP++;
          poNum--;
        }
        character->setGold(character->getGold() - numP * 2);
        ss << poNum;
        ss >> num;
        s1 = "PC buys "+num+" BD.";
        break;
      default:
        s1 = "No such potion.";
    } // switch
  } // if
  
  // enemy attack loop
  for (int i = r - 1; i <= r + 1; i++) { // get attacked by enemies around pc
    for (int j = c - 1; j <= c + 1; j++) {
      e = dynamic_cast<Enemy*>(theFloor[i][j].getObj());
      if (e != NULL) {
        m = dynamic_cast<Merchant*>(e); // determine if merchant is hostile
        if(m != NULL && m->getHostile() == false) {
          break;
        }
        damage = pc->attacked(e->attack());
        if(e->getRace() == "Goblin" && damage != "0"){
          if(pc->getGold() == 0){
            s2 = s2 + " Goblin steals nothing.";
          }
          else{
            pc->setGold(pc->getGold()-1);
            s2 = s2 + " Goblin steals 1 gold.";
          }
        }
        if(e->getRace() == "Vampire" && damage != "0"){
          pc->setHp(pc->getHp()-5);
          e->setHp(e->getHp()+5);
          s2 = s2 + " Vampire steals 5 HP.";
        }
        if(e->getRace() == "Werewolf" && rand() % 2 == 0 && damage != "0"){
          int x;
          ss1 << damage;
          ss1 >> x;
          x = x*2;
          ss2 << x;
          ss2 >> damage;
          s3 = " Werewolf deals 2X damage! ";
        }
        if(damage == "0"){
          s2 = s2+" "+e->getRace()+" misses.";
        }
        else{
          s2 = s2+" "+e->getRace()+" deals "+damage+" damage to PC.";
        }
      } // if
    } // for
  } // for
  
  s = s1 + s3 + s2;
  actionNotify(s);
}


void Floor::pcDrink() {
  stringstream ss1;
  stringstream ss2;
  string s;
  string s1;
  string s2;
  string s3;
  string damage;
  PC* pc = dynamic_cast<PC*> (theFloor[r][c].getObj());
  Enemy* e;
  Merchant* m;
  if (numP == 0) {
    s1 = "You currently don't have any potion.";
  } else {
    po[numP - 1]->function(character);
    s1 = "PC uses "+po[numP - 1]->getType()+".";
    delete po[numP - 1];
    numP--;
  }
  
  // enemy attack loop
  for (int i = r - 1; i <= r + 1; i++) { // get attacked by enemies around pc
    for (int j = c - 1; j <= c + 1; j++) {
      e = dynamic_cast<Enemy*>(theFloor[i][j].getObj());
      if (e != NULL) {
        m = dynamic_cast<Merchant*>(e); // determine if merchant is hostile
        if(m != NULL && m->getHostile() == false) {
          break;
        }
        damage = pc->attacked(e->attack());
        if(e->getRace() == "Goblin" && damage != "0"){
          if(pc->getGold() == 0){
            s2 = s2 + " Goblin steals nothing.";
          }
          else{
            pc->setGold(pc->getGold()-1);
            s2 = s2 + " Goblin steals 1 gold.";
          }
        }
        if(e->getRace() == "Vampire" && damage != "0"){
          pc->setHp(pc->getHp()-5);
          e->setHp(e->getHp()+5);
          s2 = s2 + " Vampire steals 5 HP.";
        }
        if(e->getRace() == "Werewolf" && rand() % 2 == 0 && damage != "0"){
          int x;
          ss1 << damage;
          ss1 >> x;
          x = x*2;
          ss2 << x;
          ss2 >> damage;
          s3 = " Werewolf deals 2X damage! ";
        }
        if(damage == "0"){
          s2 = s2+" "+e->getRace()+" misses.";
        }
        else{
          s2 = s2+" "+e->getRace()+" deals "+damage+" damage to PC.";
        }
      } // if
    } // for
  } // for
  
  s = s1 + s3 + s2;
  actionNotify(s);
  
}


ostream& operator<<(ostream& out, const Floor& f) {
  out << *(f.td);
  return out;
}

