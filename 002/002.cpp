#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct Cubes {
  uint red{0}, green{0}, blue{0};
  auto is_impossible(const Cubes &possibleCubes) const -> bool {
    return (red > possibleCubes.red || blue > possibleCubes.blue ||
            green > possibleCubes.green);
  }
};

struct Game {
  uint id{0};
  std::vector<Cubes> revealed_cubes;
};

auto splitOn(std::string s, char seperator) -> std::vector<std::string> {
  std::vector<std::string> vec;
  std::string tmp;
  std::stringstream ss(s);
  while (getline(ss, tmp, seperator)) {
    vec.push_back(tmp);
  }
  return vec;
}

auto parseGames(std::string fileName) -> std::vector<Game> {
  std::ifstream input(fileName);
  if (!input) {
    throw std::runtime_error("File could not be opened.");
  }

  std::vector<Game> rounds;
  while (!input.eof()) {
    std::string line;
    std::getline(input, line);
    if (line.empty())
      continue;

    Game game;
    game.id = static_cast<uint>(std::stoi(std::string(line.substr(5))));

    std::string reveals = line.substr(line.find(':') + 1);

    auto cube_vec = splitOn(reveals, ';');
    for (const auto &cubeList : cube_vec) {
      Cubes cubes;
      auto colorsVec = splitOn(cubeList, ',');
      for (const auto &color : colorsVec) {
        auto nr = splitOn(color, ' ');
        if (nr.size() != 3)
          continue;

        if (nr[2].starts_with("red")) {
          cubes.red = static_cast<uint>(std::stoi(nr[1]));
        } else if (nr[2].starts_with("green")) {
          cubes.green = static_cast<uint>(std::stoi(nr[1]));
        } else if (nr[2].starts_with("blue")) {
          cubes.blue = static_cast<uint>(std::stoi(nr[1]));
        }
      }
      game.revealed_cubes.push_back(cubes);
    }
    rounds.push_back(game);
  }
  return rounds;
}

auto solve_puzzle_1(std::vector<Game> input) -> int {
  Cubes max_cubes{12, 13, 14};

  int sum{0};
  for (auto game : input) {
    bool possible{true};
    for (const auto &cubes : game.revealed_cubes) {
      if (cubes.is_impossible(max_cubes)) {
        possible = false;
        break;
      }
    }
    if (possible) {
      sum += game.id;
    }
  }
  return sum;
}

auto solve_puzzle_2(std::vector<Game> input) -> int {
  int sum{0};
  for (auto game : input) {
    Cubes min_cubes;
    for (const Cubes &cubes : game.revealed_cubes) {
      if (cubes.red > min_cubes.red)
        min_cubes.red = cubes.red;
      if (cubes.green > min_cubes.green)
        min_cubes.green = cubes.green;
      if (cubes.blue > min_cubes.blue)
        min_cubes.blue = cubes.blue;
    }
    sum += (min_cubes.red * min_cubes.green * min_cubes.blue);
  }
  return sum;
}

int main() {
  try {
    auto puzzle = parseGames("./input");
    int solution1 = solve_puzzle_1(puzzle);
    std::cout << "Solution 1: " << solution1 << std::endl;
    int solution2 = solve_puzzle_2(puzzle);
    std::cout << "Solution 2: " << solution2 << std::endl;
  } catch (std::exception &e) {
    std::cout << "Exception: " << e.what() << std::endl;
  }
  return 0;
}
