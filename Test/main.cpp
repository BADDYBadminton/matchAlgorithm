#include "match.h"
#include "team.h"
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

bool cmp(const Match match1, const Match match2);
Match getPriorityMatch();
string getTeamName();
static vector<vector<vector<Team>>> teams;
static vector<Match> matches;
static int teamCount = 0;
int main() {
  const int total_team_event_cnt = 1;
  const int gym_court_cnt = 9;
  const int leastGameNum = 4;
  map<string, int> key_apply_cnt{
      {"XT 1부", 9},
      {"MT 2부", 9},
      {"WT 2부", 9},
  };
  map<string, map<string, vector<Team>>> groupedTeams;
  teams.reserve(key_apply_cnt.size());
  for (int i = 0; i < key_apply_cnt.size(); i++) {
    auto it = key_apply_cnt.begin();
    advance(it, i);
    groupedTeams.insert({it->first, {}});
    int teamNum = it->second;
    vector<vector<Team>> tempTeams;
    if (teamNum == 8) {
      vector<Team> vec1;
      vector<Team> vec2;
      for (int j = 0; j < 4; ++j) {
        //        string teamName = "";
        //        teamName += (char)(j + 65);
        //        teamName += "팀";
        Team(it->first, getTeamName(), 1);
      }
      for (int j = 4; j < teamNum; ++j) {
        string teamName = "";
        teamName += (char)(j + 65);
        teamName += "팀";
        vec2.emplace_back(Team(it->first, getTeamName(), 2));
      }
      tempTeams.emplace_back(vec1);
      tempTeams.emplace_back(vec2);
      for (int j = 0; j < 2; ++j) {
        groupedTeams.at(it->first).insert(
            {{to_string(j + 1) + "조", vec1}, {"2조", vec2}});
      }
    } else if (teamNum <= 5) {
      vector<Team> teamList;
      for (int j = 0; j < teamNum; ++j) {
        string teamName = "";
        teamName += (char)(j + 65);
        teamName += "팀";
        teamList.emplace_back(Team(it->first, getTeamName(), 1));
      }
      tempTeams.emplace_back(teamList);
      groupedTeams.at(it->first).insert({"1조", teamList});
    } else {
      int teamExtraNum = (teamNum % leastGameNum);
      int teamNorNum = teamNum / leastGameNum - teamExtraNum;
      for (int j = 0; j < teamExtraNum + teamNorNum; ++j) {
        if (j < teamNorNum) {
          vector<Team> slicedvector;
          int start = leastGameNum * j;
          for (int k = start; k < start + leastGameNum; ++k) {
            //            string teamName = "";
            //            teamName += (char)(k + 65);
            //            teamName += "팀";
            slicedvector.emplace_back(Team(it->first, getTeamName(), j + 1));
          }
          tempTeams.emplace_back(slicedvector);
          groupedTeams.at(it->first).insert(
              {to_string(j + 1) + "조", slicedvector});
        } else {
          vector<Team> slicedvector;
          int start = leastGameNum * j + j - teamNorNum;
          for (int k = start; k < start + leastGameNum + 1; ++k) {
            //            string teamName = "";
            //            teamName += (char)(k + 65);
            //            teamName += "팀";
            slicedvector.emplace_back(Team(it->first, getTeamName(), j + 1));
          }
          tempTeams.emplace_back(slicedvector);
          groupedTeams.at(it->first).insert(
              {to_string(j + 1) + "조", slicedvector});
        }
      }
    }
    teams.emplace_back(tempTeams);
  }

  for (int i = 0; i < teams.size(); i++) {
    for (int j = 0; j < teams.at(i).size(); ++j) {
      for (int k = 0; k < teams.at(i).at(j).size() - 1; k++) {
        for (int l = k + 1; l < teams.at(i).at(j).size(); l++) {
          matches.emplace_back(
              Match(&teams.at(i).at(j).at(k), &teams.at(i).at(j).at(l), false));
        }
      }
    }
  }

  int returnMatchCount = matches.size();


    vector<vector<Match>> newMatches;
  while (!matches.empty()) {
    vector<Match> tempMatches;
    for (int i = 0; i < gym_court_cnt; ++i) {
      if (matches.empty())
        break;
      tempMatches.emplace_back(getPriorityMatch());
    }
    newMatches.emplace_back(tempMatches);
  }


  vector<vector<string>> returnMatchList;
  for (auto it1 : newMatches) {
    vector<string> v;

    for (auto it2 : it1) {
      v.emplace_back(it2.team1->teamName + " vs " + it2.team2->teamName);
    }
    returnMatchList.emplace_back(v);
  }

  for (int i = 0; i < newMatches.size(); ++i) {
    for (int j = 0; j < newMatches.at(i).size(); ++j) {
      cout << returnMatchList.at(i).at(j) << " ";
    }
    cout << endl;
  }

  vector<vector<vector<string>>> returnTeamList;
  for (auto it1 : groupedTeams) {
    vector<vector<string>> v1;
    for (auto it2 : it1.second) {
      vector<string> v2;
      for (auto it3 : it2.second) {
        v2.emplace_back(it3.teamName);
      }
      v1.emplace_back(v2);
    }
    returnTeamList.emplace_back(v1);
  }

  //  for (int i = 0; i < gym_court_cnt + 1; i++) {
  //    if (i == 0) {
  //      cout << "        ";
  //    } else {
  //      cout << i << "코트                    ";
  //    }
  //  }
  //  cout << endl;
  //
  //  for (int i = 0; i < newMatches.size(); i++) {
  //    if (i % gym_court_cnt == 0) {
  //      cout << i / gym_court_cnt + 1 << "번 경기  ";
  //    }
  //    newMatches[i].printMatch();
  //    cout << "  ";
  //    if (i % gym_court_cnt == gym_court_cnt - 1) {
  //      cout << endl;
  //    }
  //  }

  //    return  {
  //            "team_event_group_list",groupedTeams,
  //  };
  return 0;
}

bool cmp(const Match match1, const Match match2) {
  int group1 = match1.groupNumber;
  int group2 = match2.groupNumber;
  string teamEvent1 = match1.teamEvent;
  string teamEvent2 = match2.teamEvent;
  if (match1.count() == match2.count()) {
    if (!(group1 == group2 && teamEvent2 == teamEvent1)) {
      int count1 = 0;
      int count2 = 0;
      for (auto it : matches) {
        if (it.groupNumber == group1 && it.teamEvent == teamEvent1) {
          count1 += 1;
        } else if (it.groupNumber == group2 && it.teamEvent == teamEvent2) {
          count2 += 1;
        }
      }
      return count1 > count2;
    } else {
      int count1 = 0;
      int count2 = 0;
      for (auto it : matches) {
        if (it.hasTeam(*match1.team1) || it.hasTeam(*match1.team2)) {
          count1++;
        }
        if (it.hasTeam(*match2.team1) || it.hasTeam(*match2.team2)) {
          count2++;
        }
      }
      return count1 > count2;
    }
  }
  return match1.count() > match2.count();
}

Match getPriorityMatch() {
  if (matches.size() == 1) {
    Match retMatch(matches.at(0));
    matches.erase(matches.begin());
    return retMatch;
  }
  sort(matches.begin(), matches.end(), cmp);
  Team *team1 = matches.at(0).team1;
  Team *team2 = matches.at(0).team2;
  for (int i = 0; i < teams.size(); i++) {
    for (int j = 0; j < teams.at(i).size(); j++) {
      for (int k = 0; k < teams.at(i).at(j).size(); k++) {
        if (teams.at(i).at(j).at(k) != *team1 &&
            teams.at(i).at(j).at(k) != *team2) {
          teams.at(i).at(j).at(k).count++;
        }
      }
    }
  }
  Match retMatch(matches.at(0));
  retMatch.didGame();
  matches.erase(matches.begin());
  return retMatch;
}

string getTeamName() {
  int fstNum = teamCount / 26;
  int secNum = teamCount % 26;
  teamCount++;
  string teamName = "";
  teamName += (char)(fstNum + 65);
  teamName += (char)(secNum + 65);
  teamName += "팀";
  return teamName;
}
