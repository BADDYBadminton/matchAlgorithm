//
// Created by 최유진 on 2022/04/26.
//

#include "team.h"
#include <string>
#include <iostream>
using namespace std;

void Team::didGame() { this->count = 0; }
bool Team::operator==(const Team &team) const {
    return team.teamName == this->teamName;
}
void Team::printTeam() {
    cout<< this->teamName<<endl;
}
