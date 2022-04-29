#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

class Team {

public:
  string teamName;
  int teamEventPk;
  int groupNumber;
  int count;
  Team(int teamEventPk, string teamName, int groupNumber)
      : teamEventPk(teamEventPk), teamName(teamName), groupNumber(groupNumber) {
    count = 0;
  }
  Team() {}
  void didGame() { this->count = 0; }
  bool operator==(const Team &team) const {
    return team.teamEventPk == this->teamEventPk &&
           team.teamName == this->teamName &&
           team.groupNumber == this->groupNumber;
  }
  bool operator!=(const Team &team) const { return !(team == *this); }
  void printTeam() { cout << this->teamEventPk << " " << this->teamName; }
};

class Match {

public:
  Team *team1;
  Team *team2;
  bool isMain;
  int groupNumber;
  int teamEventPk;
  Match(Team *newTeam1, Team *newTeam2, bool isMain)
      : team1(newTeam1), team2(newTeam2), isMain(isMain),
        groupNumber(team1->groupNumber), teamEventPk(newTeam1->teamEventPk) {}
  void didGame() {
    this->team1->didGame();
    this->team2->didGame();
  }

  void printMatch() const {
    this->team1->printTeam();
    cout << " vs ";
    this->team2->printTeam();
  }

  bool hasTeam(const Team &team) const {
    return team == *(this->team1) || team == *(this->team2);
  }
  int count() const { return this->team1->count + this->team2->count; }

  bool operator==(const Match &match) const {
    return match.team1 == this->team1 && match.team2 == this->team2;
  }

  bool operator!=(const Match &match) const { return !(match == *this); }

  bool operator>=(const Match &match) const {
    return (match.team1->teamName + match.team2->teamName) >=
           (this->team1->teamName + this->team2->teamName);
  }

  bool operator<=(const Match &match) const { return !(match > *this); }

  bool operator>(const Match &match) const {
    return match <= *this && (match != *this);
  }
  bool operator<(const Match &match) const { return !(match >= *this); }
};

bool cmp(const Match match1, const Match match2);
Match getPriorityMatch();
string getTeamName();
static vector<vector<vector<Team>>> teams;
static vector<Match> matches;
static int teamCount = 0;
int main(int argc, char **argv) {
    const int leastGameNum = 4;

  if (argc < 3) {
    fputs("에러! 옵션이 제대로 입력되지 않았습니다!...\n", stderr);
    exit(1);
  }

    map<int, int> key_apply_cnt;
  int gym_court_cnt = atoi(argv[1]);

  for (int i = 1; i < argc / 2; i++) {
    int teamEventPk = atoi(argv[i]);
    int teamNum = atoi(argv[i + 1]);
    key_apply_cnt.insert({teamEventPk, teamNum});
  }

//    map<int,int> key_apply_cnt{{123,9},{124,9},{125,9}};
//    int gym_court_cnt = 9;

  map<int, map<string, vector<Team>>> groupedTeams;
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
      int teamExtraNum = teamNum % leastGameNum;
      int teamNorNum = teamNum / leastGameNum - teamExtraNum;
      for (int j = 0; j < teamExtraNum + teamNorNum; ++j) {
        if (j < teamNorNum) {
          vector<Team> slicedvector;
          int start = leastGameNum * j;
          for (int k = start; k < start + leastGameNum; ++k) {
            slicedvector.emplace_back(Team(it->first, getTeamName(), j + 1));
          }
          tempTeams.emplace_back(slicedvector);
          groupedTeams.at(it->first).insert(
              {to_string(j + 1) + "조", slicedvector});
        } else {
          vector<Team> slicedvector;
          int start = leastGameNum * j + j - teamNorNum;
          for (int k = start; k < start + leastGameNum + 1; ++k) {
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

  for (auto it1 : groupedTeams) {
    cout << it1.first << endl;
    for (auto it2 : it1.second) {
      cout << it2.first << endl;
      for (auto it3 : it2.second) {
        cout << it3.teamName << " ";
      }
      cout << endl;
    }
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

  //    for (int i = 0; i < gym_court_cnt + 1; i++) {
  //      if (i == 0) {
  //        cout << "        ";
  //      } else {
  //        cout << i << "코트                    ";
  //      }
  //    }
  //    cout << endl;
  //
  //    for (int i = 0; i < newMatches.size(); i++) {
  //      if (i % gym_court_cnt == 0) {
  //        cout << i / gym_court_cnt + 1 << "번 경기  ";
  //      }
  //      newMatches[i].printMatch();
  //      cout << "  ";
  //      if (i % gym_court_cnt == gym_court_cnt - 1) {
  //        cout << endl;
  //      }
  //    }

  //    return  {
  //            "team_event_group_list",groupedTeams,
  //  };
  return 0;
}

bool cmp(const Match match1, const Match match2) {
  int group1 = match1.groupNumber;
  int group2 = match2.groupNumber;
  int teamEvent1 = match1.teamEventPk;
  int teamEvent2 = match2.teamEventPk;
  if (match1.count() == match2.count()) {
    if (!(group1 == group2 && teamEvent2 == teamEvent1)) {
      int count1 = 0;
      int count2 = 0;
      for (auto it : matches) {
        if (it.groupNumber == group1 && it.teamEventPk == teamEvent1) {
          count1 += 1;
        } else if (it.groupNumber == group2 && it.teamEventPk == teamEvent2) {
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
