#include <algorithm>
#include <array>
#include <bits/stdc++.h>
#include <cstdio>
#include <fstream>
#include <limits>
#include <map>
#include <vector>

std::vector<std::vector<int>> vec;
std::vector<std::vector<bool>> flags;
std::vector<std::vector<bool>> visited;

int depthSearch(int x, int y) {
  static int stackSize = 0u;
  stackSize++;
  visited[x][y] = true;

  int matches = 0;
  if (x + 1 < vec.size() && visited[x + 1][y] == false) {
    if (vec[x][y] > (vec[x + 1][y] + 1)) {
      matches++;
      matches += depthSearch(x + 1, y);
    }
  }

  if (x - 1 >= 0 && visited[x - 1][y] == false) {
    if (vec[x][y] > (vec[x - 1][y] + 1)) {
      matches++;
      matches += depthSearch(x - 1, y);
    }
  }

  if (y + 1 < vec[x].size() && visited[x][y + 1] == false) {
    if (vec[x][y] > (vec[x][y + 1] + 1)) {
      matches++;
      matches += depthSearch(x, y + 1);
    }
  }

  if (y - 1 >= 0 && visited[x][y - 1] == false) {
    if (vec[x][y] == (vec[x][y - 1] + 1)) {
      matches++;
      matches += depthSearch(x, y - 1);
    }
  }
  return matches;
}

int main() {
  std::ifstream infile("input.txt");
  std::string line = "";

  auto i = 0u;
  while (std::getline(infile, line)) {
    vec.push_back(std::vector<int>());
    flags.push_back(std::vector<bool>());
    visited.push_back(std::vector<bool>());
    for (auto j = 0u; j < line.length(); j++) {
      vec[i].push_back(line[j] - '0');
      flags[i].push_back(false);
      visited[i].push_back(false);
    }
    i++;
  }

  for (auto i = 0u; i < vec.size(); i++) {
    for (auto j = 0u; j < vec[i].size(); j++) {
      printf("%d", vec[i][j]);
    }
    printf("\n");
  }

  auto sum = 0u;
  for (int i = 0; i < vec.size(); i++) {
    for (int j = 0; j < vec[i].size(); j++) {
      auto smaller = true;
      if ((i + 1) < vec.size()) {
        if (vec[i + 1][j] < vec[i][j]) {
          smaller = false;
        }
      }
      if ((i - 1) >= 0) {
        if (vec[i - 1][j] < vec[i][j]) {
          smaller = false;
        }
      }
      if ((j + 1) < vec[i].size()) {
        if (vec[i][j + 1] < vec[i][j]) {
          smaller = false;
        }
      }
      if ((j - 1) >= 0) {
        if (vec[i][j - 1] < vec[i][j]) {
          smaller = false;
        }
      }

      if (smaller) {
        flags[i][j] = true;
        sum += vec[i][j] + 1;
      }
    }
  }

  std::vector<int> result;
  for (int i = 0; i < vec.size(); i++) {
    for (int j = 0; j < vec[i].size(); j++) {
      if (flags[i][j] == true) {
        auto ret = depthSearch(i, j);
        result.push_back(ret);
        printf("%d\n", ret);
      }
    }
  }

  printf("sum: %d\n", sum);
}