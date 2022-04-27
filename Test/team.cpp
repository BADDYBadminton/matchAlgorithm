//
// Created by 최유진 on 2022/04/26.
//

#include "team.h"
#include <iostream>
#include <string>
using namespace std;

void Team::didGame() { this->count = 0; }
bool Team::operator==(const Team &team) const {
  return team.teamEventName == this->teamName && team.teamEventName == this->teamName &&
         team.groupNumber == this->groupNumber;
}
bool Team::operator!=(const Team &team) const { return !(team == *this); }
void Team::printTeam() { cout  << this->teamEventName << " "<< this->teamName; }
