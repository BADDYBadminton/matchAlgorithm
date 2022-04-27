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
  string teamEventName;
  int groupNumber;
  int count;
  Team(string teamEventName,string teamName ,int groupNumber)
      : teamEventName(teamEventName), teamName(teamName),groupNumber(groupNumber) {
    count = 0;
  }
  Team() {}
  void didGame();
  void printTeam();
  bool operator==(const Team &team) const;
  bool operator!=(const Team &team) const;
};

#endif // TEST_TEAM_H
