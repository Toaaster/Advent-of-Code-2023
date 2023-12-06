#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

struct Round {
  int nr{0};
  int matches{0};
  std::vector<int> winning;
  std::vector<int> drawn;
};

auto parseInput(std::string fileName) -> std::vector<Round> {
  std::ifstream input{fileName};
  if (!input) {
    throw std::runtime_error("File could not be opened.");
  }

  std::vector<Round> rounds;
  std::string tmp;
  while (getline(input, tmp)) {
    if (!tmp.starts_with("Card"))
      continue;

    Round r{};

    r.nr = std::stoi(tmp.substr(tmp.find('d') + 1, tmp.find(':')));

    tmp = tmp.substr(tmp.find(':') + 1);

    std::istringstream winningStream{tmp.substr(0, tmp.find('|'))};
    std::istringstream drawnStream{tmp.substr(tmp.find('|') + 1)};

    int x;
    while (winningStream >> x)
      r.winning.push_back(x);

    while (drawnStream >> x) {
      r.drawn.push_back(x);
    }

    rounds.push_back(r);
  }
  return rounds;
}

int solve_1(std::vector<Round> &rounds) {
  int sum{0};
  for (auto &round : rounds) {
    int points{0};
    for (auto w : round.winning) {
      auto it = std::find(round.drawn.begin(), round.drawn.end(), w);
      if (it != round.drawn.end()) {
        round.matches++;
        points = points == 0 ? 1 : points * 2;
      }
    }
    sum += points;
  }
  return sum;
}

int solve_2(std::vector<Round> &rounds) {
  int sum{0};
  std::unordered_map<int, int> nrCards;
  for (auto r : rounds) {
    nrCards.insert(std::make_pair(r.nr, 1));
  }
  for (auto r : rounds) {
    if (r.matches == 0)
      continue;
    for (int x = r.nr + 1; x <= (r.nr + r.matches); ++x) {
      nrCards[x] += nrCards[r.nr];
    }
  }
  for (auto p : nrCards) {
    sum += p.second;
  }
  return sum;
}

int main() {
  auto game = parseInput("./input");

  int solution1 = solve_1(game);
  std::cout << "Solution 1: " << solution1 << std::endl;
  int solution2 = solve_2(game);
  std::cout << "Solution 2: " << solution2 << std::endl;
  return 0;
}
