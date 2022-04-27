//
// Created by 최유진 on 2022/04/26.
//

#ifndef TEST_MATCH_H
#define TEST_MATCH_H

#include "team.h"
#include <string>
#include <vector>

using namespace std;

class Match {

public:
  Team *team1;
  Team *team2;
  bool isMain;
  int groupNumber;
  string teamEvent;
  Match(Team *newTeam1, Team *newTeam2, bool isMain)
      : team1(newTeam1), team2(newTeam2), isMain(isMain),
        groupNumber(team1->groupNumber),teamEvent(newTeam1->teamEventName) {}
  void printMatch() const;
  void didGame();
  int count() const;
  bool operator==(const Match &match) const;
  bool operator!=(const Match &match) const;
  bool operator>=(const Match &match) const;
  bool operator<=(const Match &match) const;
  bool operator>(const Match &match) const;
  bool operator<(const Match &match) const;

    bool hasTeam(const Team &team) const;
};
#endif // TEST_MATCH_H
