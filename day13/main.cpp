#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <vector>

constexpr auto fieldSize = 20u;

std::array<std::array<char, fieldSize>, fieldSize> arr{{}};
std::array<std::array<char, fieldSize>, fieldSize> arr2{{}};
std::vector<std::pair<bool, int>> instruction{};

void removeTopLeft() {
  int moveX = arr.size() - 1;
  int moveY = arr[0].size() - 1;

  for (auto i = 0; i < arr.size(); i++) {
    for (int j = 0; j < arr[0].size(); j++) {
      if (arr[i][j] == '#') {
        moveX = std::min(moveX, i);
        moveY = std::min(moveY, j);
        break;
      }
    }
  }

  for (auto i = 0; i < arr.size() - moveX; i++) {
    for (auto j = 0; j < arr[i].size() - moveY; j++) {
      arr[i][j] = arr[i + moveX][j + moveY];
    }
  }
}

void processInstruction(std::pair<bool, int> inst) {
  if (inst.first) {
    for (int i = 0; i < arr.size(); i++) {
      for (int j = 0; j < arr[i].size(); j++) {
        auto pos = std::abs(j - inst.second);
        if (arr[i][j] == '#') {
          arr2[i][pos] = arr[i][j];
          arr[i][j] = '.';
        }
      }
    }
  } else {
    for (int i = 0; i < arr.size(); i++) {
      for (int j = 0; j < arr[i].size(); j++) {
        auto pos = std::abs(i - inst.second);
        if (arr[i][j] == '#') {
          arr2[pos][j] = arr[i][j];
          arr[i][j] = '.';
        }
      }
    }
  }

  // arr = arr2
  for (int i = 0u; i < arr.size(); i++) {
    for (int j = 0u; j < arr[i].size(); j++) {
      arr[i][j] = arr2[i][j];
    }
  }

  // clear arr2
  std::fill(&arr2[0][0], &arr2[0][0] + sizeof(arr2), '.');
}

int main() {
  std::ifstream infile("input.txt");
  std::string line = "";
  std::string delimiter = ",";
  std::string foldAlongDelimiter = "fold along ";
  std::fill(&arr[0][0], &arr[0][0] + sizeof(arr), '.');
  std::fill(&arr2[0][0], &arr2[0][0] + sizeof(arr2), '.');

  while (std::getline(infile, line)) {
    if (line.find(delimiter) == std::string::npos) {
      break;
    }
    int x = std::stoi(line.substr(0, line.find(delimiter)));
    int y = std::stoi(
        line.substr(line.find(delimiter) + delimiter.length(), line.length()));
    arr[y][x] = '#';
  }

  while (std::getline(infile, line)) {
    auto token = line.substr(foldAlongDelimiter.length(), line.length());
    if (token.find("x") != std::string::npos) {
      instruction.push_back(std::make_pair<bool, int>(
          true, std::stoi(token.substr(token.find("=") + 1, token.length()))));
    } else {
      instruction.push_back(std::make_pair<bool, int>(
          false, std::stoi(token.substr(token.find("=") + 1, token.length()))));
    }
    // printf("%s\n", token.c_str());
  }

  for (auto it : instruction) {
    for (int i = 0; i < arr.size(); i++) {
      for (int j = 0; j < arr[i].size(); j++) {
        printf("%c", arr[i][j]);
      }
      printf("\n");
    }

    removeTopLeft();
    printf("%s : %d\n", it.first ? "true" : "false", it.second);
    processInstruction(it);
    removeTopLeft();

    for (int i = 0; i < arr.size(); i++) {
      for (int j = 0; j < arr[i].size(); j++) {
        printf("%c", arr[i][j]);
      }
      printf("\n");
    }
    printf("\n");
  }

  /*
  for (int i = 0; i < arr.size(); i++) {
    for (int j = 0; j < arr[i].size(); j++) {
      printf("%c", arr[i][j]);
    }
    printf("\n");
  }
  */

  int sum = 0;
  for (auto i = 0u; i < arr.size(); i++) {
    for (auto j = 0u; j < arr[i].size(); j++) {
      if (arr[i][j] == '#') {
        sum++;
      }
    }
  }
  printf("sum: %d\n", sum);
}