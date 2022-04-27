//
// Created by 최유진 on 2022/04/26.
//

#ifndef TEST_TEAM_H
#define TEST_TEAM_H

#include <string>

using namespace std;

class Team {

public:

    string teamName;
    int count;
    Team(string teamName) {
        this->teamName = teamName;
        count = 0;
    }
    Team(){}
    void didGame();
    void printTeam();
    bool operator==(const Team &team) const;
};

#endif //TEST_TEAM_H
