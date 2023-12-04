#include <algorithm>
#include <cctype>
#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

auto parseInput(std::string fileName) -> std::vector<std::string> {
  std::ifstream input{fileName};
  if (!input) {
    throw std::runtime_error("File could not be opened.");
  }

  std::vector<std::string> schematics;
  std::string tmp;
  while (getline(input, tmp)) {
    schematics.push_back(tmp);
  }
  return schematics;
}

auto isSymbol(char c) -> bool { return (!std::isdigit(c) && c != '.'); }

auto solve_puzzle_1(const std::vector<std::string> &input) -> int {
  int sum{0};
  for (size_t i{0}; i < input.size(); ++i) {
    for (size_t j{0}; j < input[i].size(); ++j) {
      if (!std::isdigit(input[i][j]))
        continue;
      size_t len{0};
      int number = std::stoi(input[i].substr(j), &len);

      bool isValid{false};
      for (size_t i_t{(i == 0) ? 0 : i - 1};
           i_t <= std::min(i + 1, input.size() - 1); ++i_t) {
        for (size_t j_t{(j == 0) ? 0 : j - 1};
             j_t <= std::min(j + len, input[i].size() - 1); ++j_t) {
          if (isSymbol(input[i_t][j_t])) {
            isValid = true;
            break;
          }
        }
        if (isValid)
          break;
      }
      if (isValid) {
        sum += number;
      }
      j += len;
    }
  }
  return sum;
}

auto solve_puzzle_2(const std::vector<std::string> &input) -> int {
  int sum{0};
  for (size_t i{0}; i < input.size(); ++i) {
    for (size_t j{0}; j < input[i].size(); ++j) {
      if (input[i][j] != '*')
        continue;

      int adjacentNr{0};
      int cogNr{1};
      for (size_t i_t{(i == 0) ? 0 : i - 1};
           i_t <= std::min(i + 1, input.size() - 1); ++i_t) {
        for (size_t j_t{(j == 0) ? 0 : j - 1};
             j_t <= std::min(j + 1, input[i].size() - 1); ++j_t) {
          if (!std::isdigit(input[i_t][j_t]))
            continue;

          size_t t{j_t};

          while (true) {
            if (std::isdigit(input[i_t][t - 1]))
              t--;
            else
              break;
          }
          size_t len{0};
          int nr = std::stoi(input[i_t].substr(t), &len);
          adjacentNr++;
          cogNr *= nr;
          std::cout << j_t << " " << t << std::endl;
          if (t < j_t) {
            j_t += j_t - t - 1;
          } else {
            j_t += len - 1;
          }
        }
      }
      if (adjacentNr == 2) {
        sum += cogNr;
        std::cout << "Valid at: " << i + 1 << "-" << j << " with value "
                  << cogNr << std::endl;
      }
    }
  }
  return sum;
}

int main() {
  try {
    auto input = parseInput("./input_simple");
    int solution1 = solve_puzzle_1(input);
    std::cout << "Solution 1: " << solution1 << std::endl;
    int solution2 = solve_puzzle_2(input);
    std::cout << "Solution 2: " << solution2 << std::endl;
  } catch (std::exception &e) {
    std::cout << "Exception: " << e.what() << std::endl;
  }
  return 0;
}
