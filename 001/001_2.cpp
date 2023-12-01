#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

const std::string INPUT = "./input";
const std::vector<std::string> NUMBER_WORDS{
    "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

int main() {
  std::ifstream file{INPUT};
  int n{0};
  for (std::string line; std::getline(file, line);) {

    int first_word_digit = 0;
    auto first_word_digit_it = line.end();
    for (auto word : NUMBER_WORDS) {
      auto i = line.find(word);
      auto it = line.begin();
      if (i != std::string::npos) {
        std::advance(it, i);
      } else {
        continue;
      }
      if (it < first_word_digit_it) {
        first_word_digit_it = it;
        first_word_digit =
            static_cast<int>(std::distance(
                NUMBER_WORDS.begin(),
                std::find(NUMBER_WORDS.begin(), NUMBER_WORDS.end(), word))) +
            1;
      }
    }

    int last_word_digit = 0;
    auto last_word_digit_it = line.rend();
    for (auto word : NUMBER_WORDS) {
      auto i = line.rfind(word);
      auto it_forward = line.begin();
      auto it = line.rbegin();
      if (i != std::string::npos) {
        std::advance(it_forward, i);
        it = --std::make_reverse_iterator(it_forward);
      } else {
        continue;
      }
      if (std::distance(line.rbegin(), it) <
          std::distance(line.rbegin(), last_word_digit_it)) {
        last_word_digit_it = it;
        last_word_digit =
            static_cast<int>(std::distance(
                NUMBER_WORDS.begin(),
                std::find(NUMBER_WORDS.begin(), NUMBER_WORDS.end(), word))) +
            1;
      }
    }

    auto first_digit = std::find_if(line.begin(), line.end(),
                                    [](auto x) { return std::isdigit(x); });
    auto last_digit = std::find_if(line.rbegin(), line.rend(),
                                   [](auto x) { return std::isdigit(x); });
    std::string nr{""};
    if (first_word_digit_it < first_digit) {
      nr.append(std::to_string(first_word_digit));
    } else {
      nr.push_back(*first_digit);
    }

    if (std::distance(line.rend(), last_word_digit_it) <=
        std::distance(line.rend(), last_digit)) {
      nr.append(std::to_string(last_word_digit));
    } else {
      nr.push_back(*last_digit);
    }
    std::cout << nr << std::endl;
    n += std::stoi(nr);
  }
  std::cout << n << std::endl;
}
