#include <array>
#include <cstdio>
#include <fstream>
#include <vector>

struct Element {
  std::pair<std::pair<int, int>, std::pair<int, int>> member{{}, {}};
};

constexpr auto fieldSize = 1000u;
using ArrayInt = std::array<std::array<int, fieldSize>, fieldSize>;

int main() {
  std::ifstream infile("input.txt");
  std::string line = "";
  std::string delimiter = " -> ";
  std::string splitDelimiter = ",";

  std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>
      leftToRight{};

  while (std::getline(infile, line)) {
    size_t pos = line.find(delimiter);
    auto tokenLeft = line.substr(0, pos);
    auto tokenRight = line.substr(pos + delimiter.length(), line.length());

    pos = tokenLeft.find(splitDelimiter);
    auto tokenLeftLeft = tokenLeft.substr(0, pos);
    auto tokenLeftRight =
        tokenLeft.substr(pos + splitDelimiter.length(), tokenLeft.length());

    pos = tokenRight.find(splitDelimiter);
    auto tokenRightLeft = tokenRight.substr(0, pos);
    auto tokenRightRight =
        tokenRight.substr(pos + splitDelimiter.length(), tokenRight.length());

    Element element{};
    element.member.first.first = std::stoi(tokenLeftLeft);
    element.member.first.second = std::stoi(tokenLeftRight);
    element.member.second.first = std::stoi(tokenRightLeft);
    element.member.second.second = std::stoi(tokenRightRight);
    leftToRight.push_back(element.member);
  }

  /*
  for(auto it : leftToRight) {
    printf("%d,%d -> %d,%d\n", it.first.first, it.first.second, it.second.first,
  it.second.second);
  }
  */

  ArrayInt field{{}};
  for (auto it : leftToRight) {
    if (it.first.first == it.second.first ||
        it.first.second == it.second.second) {
      if (it.first.first == it.second.first) {
        for (auto i = it.first.second; i <= it.second.second; i++) {
          field[it.first.first][i]++;
        }
        for (auto i = it.first.second; i >= it.second.second; i--) {
          field[it.first.first][i]++;
        }
      }
      if (it.first.second == it.second.second) {
        for (auto i = it.first.first; i <= it.second.first; i++) {
          field[i][it.first.second]++;
        }
        for (auto i = it.first.first; i >= it.second.first; i--) {
          field[i][it.first.second]++;
        }
      }
    }
  }

  auto numIntersections = 0u;
  for (auto i = 0u; i < field.size(); i++) {
    for (auto j = 0u; j < field[0].size(); j++) {
      if (field[j][i] >= 2) {
        numIntersections++;
      }
    }
  }

  printf("numIntersections: %d\n", numIntersections);

  /*
  for (auto i = 0u; i < field.size(); i++) {
    for (auto j = 0u; j < field[0].size(); j++) {
      if (field[j][i] == 0) {
        printf(".");
      } else {
        printf("%d", field[j][i]);
      }
    }
    printf("\n");
  }
  */
}
