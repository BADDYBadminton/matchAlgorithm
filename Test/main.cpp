#include "match.h"
#include "team.h"
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

bool cmp(const Match match1, const Match match2) {
  return match1.count() > match2.count();
};

int main() {

  const int total_team_event_cnt = 1;
  const int gym_court_cnt = 3;
  const int leastGameNum = 4;
  map<string, int> key_apply_cnt{{"혼합단체전 1부", 9}};
  map<string, map<string, vector<Team>>> groupedTeams;

  for (int i = 0; i < key_apply_cnt.size(); i++) {
    auto it = key_apply_cnt.begin();
    advance(it, i);
    groupedTeams.insert({it->first, {}});
    int teamNum = it->second;
    vector<Team> teamList;
    for (int j = 0; j < teamNum; ++j) {
      teamList.push_back(Team(it->first + " " + (char)(j + 65) + "팀"));
    }

    if (teamNum == 8) {
      vector<Team> vec1;
      vector<Team> vec2;
      vec1 = vector<Team>(teamList.begin(), teamList.begin() + 4);
      vec2 = vector<Team>(teamList.begin() + 4, teamList.begin() + 8);
      for (int j = 0; j < 2; ++j) {
        groupedTeams.at(it->first).insert(
            {{to_string(j + 1) + "조", vec1}, {"2조", vec2}});
      }
    } else if (teamNum <= 5) {
      groupedTeams.at(it->first).insert({"1조", teamList});
    } else {
      int teamExtraNum = (teamNum % leastGameNum);
      int teamNorNum = teamNum / leastGameNum - teamExtraNum;
      for (int j = 0; j < teamExtraNum + teamNorNum; ++j) {
        if (j < teamNorNum) {
          vector<Team> slicedvector;
          auto start = teamList.begin() + 4 * j;
          slicedvector = vector<Team>(start, start + leastGameNum);
          groupedTeams.at(it->first).insert(
              {to_string(j + 1) + "조", slicedvector});
        } else {
          vector<Team> slicedvector;
          auto start = teamList.begin() + 4 * j + j - teamNorNum;
          slicedvector = vector<Team>(start, start + leastGameNum + 1);
          groupedTeams.at(it->first).insert(
              {to_string(j + 1) + "조", slicedvector});
        }
      }
    }
  }


  // Team team1 = Team("1팀");
  // Team team2 = Team("2팀");
  // Team team3 = Team("3팀");
  // matches.push_back(Match(&team1, &team2, false));
  // matches.push_back(Match(&team3, &team2, false));
  // matches.push_back(Match(&team1, &team3, false));
  // team1.count ++;
  vector<Match> matches;
  vector<Team> teamList;
  int index = 0;
  for (auto it : groupedTeams) {
    for (auto secIt : it.second) {
        vector<Team> v = secIt.second;
        teamList.insert( teamList.end(),v.begin(), v.end());
      for (int j = index; j < teamList.size() - 1; j++) {
        for (int k = j + 1; k < teamList.size(); k++) {
          matches.emplace_back(&teamList[j], &teamList[k], false);
        }
      }
      index += secIt.second.size();
    }
  }

  sort(matches.begin(), matches.end(), cmp);
}
