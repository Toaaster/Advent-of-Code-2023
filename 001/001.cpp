#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

const std::string INPUT = "./input";

int main() {
  std::ifstream file{INPUT};
  int n{0};
  for (std::string line; std::getline(file, line);) {
    auto first_digit = *std::find_if(line.begin(), line.end(),
                                     [](auto x) { return std::isdigit(x); });
    auto last_digit = *std::find_if(line.rbegin(), line.rend(),
                                    [](auto x) { return std::isdigit(x); });
    std::string nr{""};
    nr.push_back(first_digit);
    nr.push_back(last_digit);
    n += std::stoi(nr);
  }
  std::cout << n << std::endl;
}
