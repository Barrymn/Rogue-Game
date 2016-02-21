//
//  3p.cpp
//  cc3k
//
//  Created by Ning Ma on 7/21/13.
//  Copyright (c) 2013 Ning Ma. All rights reserved.
//

#include "3p.h"
#include "potion.h"

Human:: Human(): PC(140,20,20, "Human"){}

Human:: Human(int hp, int gold):PC(hp,20,20,"Human"){this->gold = gold;}

Elves:: Elves(): PC(140,30,10, "Elves"){}

Elves:: Elves(int hp, int gold): PC(hp,30,10,"Elves"){this->gold = gold;}

Orc:: Orc(): PC(180,30,25, "Orc"){}

Orc:: Orc(int hp, int gold):PC(hp,30,25,"Orc"){this->gold = gold;}

Dwarf:: Dwarf(): PC(100,20,30, "Dwarf"){}

Dwarf:: Dwarf(int hp, int gold): PC(hp,20,30,"Dwarf"){this->gold = gold;}

Ironman:: Ironman(): PC(200, 100, 100, "Ironman"){}

Ironman:: Ironman(int hp, int gold): PC(hp, 100, 100, "Ironman"){this->gold = gold;}