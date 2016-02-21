//
//  main.cpp
//  cc3k
//
//  Created by Ning Ma on 2013-07-18.
//  Copyright (c) 2013 Ning Ma. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include "floor.h"
using namespace std;

extern PC* character;

int main(int argc, const char * argv[]) {
  char command;
  char dir;
  char race;
  string s;
  Floor* f;
  bool end = false;
  int score;
  
  ifstream in("welcome.txt");	// welcome page
  while (getline(in, s)) {
    cout << s << endl;
  }
  
  while (true) {		// determine if whitespace is pressed
    cin >> command;
    if (command == 'c') {
      break;
    }
    if (command == 'q') {
      return 0;
    }
  }
  
  f = new Floor(25, 79);	// choose race
  f->init(argv[1]);
  cout << "please choose your race" << endl;
  cout << "h: human" << endl;
  cout << "d: dwarf" << endl;
  cout << "e: evlves" << endl;
  cout << "o: orc" << endl;
  cout << "i: ironman" << endl;
  
  while (true) {
    cin >> race;	// specify race
    if (race == 'q') return 0;
    else if (race == 'h' || race == 'e' || race == 'd' || race == 'o' ||
             race == 'i') break;
    else cout << "no such race" << endl;
  }
  
  switch(race) {	// spawn pc and stair
    case 'h':
      character = new Human;
      f->newGame(character);
      break;
    case 'e':
      character = new Elves;
      f->newGame(character);
      break;
    case 'd':
      character = new Dwarf;
      f->newGame(character);
      break;
    case 'o':
      character = new Orc;
      f->newGame(character);
      break;
    case 'i':
      character = new Ironman;
      f->newGame(character);
      break;
  }
  f->enemyMove();
  f->notifyTd();
  cout << *f;
  
  while (true) {
    if (character->getHp() <= 0) {	// determine if PC is dead
      ifstream in("lose.txt");
      while(getline(in, s)) {
        cout << s << endl;
      }
      score = character->getGold();
      if (character->getRace() == "human") {
        score += score / 2;
      }
      cout << "Your Score is: " << score << endl;
      end = true;
    }
    
    cin >> command;
    
    if (end == true) {	// wait for r or q after previous game
      while (command != 'r' && command != 'q') {
        cin >> command;
      }
      end = false;
    }
    
    switch(command) {
      case 'n':		// move
        cin >> dir;
        switch(dir) {
          case 'w':	
            f->pcMove(0);
            break;
          case 'o':
            f->pcMove(1);
            break;
          case 'e':
            f->pcMove(2);
            break;
          default:
            cout << "invalid command" << endl;
            break;
        }
        break;
      case 'w':
        cin >> dir;
        if (dir == 'e') {
          f->pcMove(3);
        } else {
          cout << "invalid command" << endl;
        }
        break;
      case 'e':
        cin >> dir;
        if (dir == 'a') {
          f->pcMove(4);
        } else {
          cout << "invalid command" << endl;
        }
        break;
      case 's':
        cin >> dir;
        switch(dir) {
          case 'w':
            f->pcMove(5);
            break;
          case 'o':
            f->pcMove(6);
            break;
          case 'e':
            f->pcMove(7);
            break;
          default:
            cout << "invalid command" << endl;
            break;
        }
        break;
        
      case 'u':		// drink potion
        cin >> command;
        switch(command) {
          case 'n':	
            cin >> dir;
            switch(dir) {
              case 'w':
                f->pcUse(0);
                break;
              case 'o':
                f->pcUse(1);
                break;
              case 'e':
                f->pcUse(2);
                break;
              default:
                cout << "invalide command" << endl;
                break;
            }
            break;
          case 'w':
            cin >> dir;
            if (dir == 'e') {
              f->pcUse(3);
            } else {
              cout << "invalid command" << endl;
            }
            break;
          case 'e':
            cin >> dir;
            if (dir == 'a') {
              f->pcUse(4);
            } else {
              cout << "invalid command" << endl;
              break;
            }
            break;
          case 's':
            cin >> dir;
            switch(dir) {
              case 'w':
                f->pcUse(5);
                break;
              case 'o':
                f->pcUse(6);
                break;
              case 'e':
                f->pcUse(7);
                break;
              default:
                cout << "invalid command" << endl;
                break;
            }
            break;
        }
        break;
        
      case 'g':		// get potion
        cin >> command;
        switch(command) {
          case 'n':
            cin >> dir;
            switch(dir) {
              case 'w':
                f->pcGet(0);
                break;
              case 'o':
                f->pcGet(1);
                break;
              case 'e':
                f->pcGet(2);
                break;
              default:
                cout << "invalide command" << endl;
                break;
            }
            break;
          case 'w':
            cin >> dir;
            if (dir == 'e') {
              f->pcGet(3);
            } else {
              cout << "invalid command" << endl;
            }
            break;
          case 'e':
            cin >> dir;
            if (dir == 'a') {
              f->pcGet(4);
            } else {
              cout << "invalid command" << endl;
              break;
            }
            break;
          case 's':
            cin >> dir;
            switch(dir) {
              case 'w':
                f->pcGet(5);
                break;
              case 'o':
                f->pcGet(6);
                break;
              case 'e':
                f->pcGet(7);
                break;
              default:
                cout << "invalid command" << endl;
                break;
            }
            break;
        }
        break;

      case 'a':		// attack enemy
        cin >> command;
        switch(command) {
          case 'n':
            cin >> dir;
            switch(dir) {
              case 'w':
                f->pcAttack(0);
                break;
              case 'o':
                f->pcAttack(1);
                break;
              case 'e':
                f->pcAttack(2);
                break;
              default:
                cout << "invalid command" << endl;
                break;
            }
            break;
          case 'w':
            cin >> dir;
            if (dir == 'e') {
              f->pcAttack(3);
            } else {
              cout << "invalid command" << endl;
            }
            break;
          case 'e':
            cin >> dir;
            if (dir == 'a') {
              f->pcAttack(4);
            } else {
              cout << "invalid command" << endl;
            }
            break;
          case 's':
            cin >> dir;
            switch(dir) {
              case 'w':
                f->pcAttack(5);
                break;
              case 'o':
                f->pcAttack(6);
                break;
              case 'e':
                f->pcAttack(7);
                break;
              default:
                cout << "invalid command" << endl;
                break;
            }
            break;
        }
        break;
        
      case 'b':
        int i;
        cin >> i;
        cin >> command;
        f->pcBuy(command, i);
        break;
        
      case 'd':		// drink potion
        f->pcDrink();
        break;

      case 'r':		// restart game
        end = false;
        delete f;
        f = new Floor(25, 79);
        f->init(argv[1]);
        cout << "please choose your race" << endl;
        cout << "h: human" << endl;
        cout << "d: dwarf" << endl;
        cout << "e: evlves" << endl;
        cout << "o: orc" << endl;
        cout << "i: ironman" << endl;
        while (true) {
          cin >> race;	// specify race
          if (race == 'q') return 0;
          else if (race == 'h' || race == 'e' || race == 'd' || race == 'o'
                   || race == 'i') break;
          else cout << "no such race" << endl;
        }
        switch(race) {
          case 'h':
            character = new Human;
            f->newGame(character);
            break;
          case 'e':
            character = new Elves;
            f->newGame(character);
            break;
          case 'd':
            character = new Dwarf;
            f->newGame(character);
            break;
          case 'o':
            character = new Orc;
            f->newGame(character);
            break;
          case 'i':
            character = new Ironman;
            f->newGame(character);
            break;
        }
        break;
        
      case 'q':
        cout << "you give up, try harder next time." << endl;
        delete f;
        return 0;
        
      default:
        continue;
    }
    if (f->getF() >= numFloor) {
      ifstream in("win.txt");
      while (getline(in, s)) {
        cout << s << endl;
      }
      score = character->getGold();
      if (character->getRace() == "human") {
        score += score / 2;
      }
      cout << "Your Score is: " << score << endl;
      end = true;
      continue;
    }
    f->enemyMove();
    f->notifyTd();
    cout << *f;
  }
  return 0;
}

