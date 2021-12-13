#include <algorithm>
#include <array>
#include <bits/stdc++.h>
#include <cstdio>
#include <fstream>
#include <limits>
#include <map>
#include <vector>

std::vector<std::vector<int>> vec;
std::vector<std::vector<bool>> flashed;
int numFlashes = 0u;

bool simultaneously() {
  for (int i = 0u; i < vec.size(); i++) {
    for (int j = 0u; j < vec[i].size(); j++) {
      if (vec[i][j] != vec[0][0]) {
        return false;
      }
    }
  }
  return true;
}

void flashPos(int x, int y) {
  if (flashed[x][y]) {
    return;
  }
  flashed[x][y] = true;

  if (x + 1 < vec.size()) {
    vec[x + 1][y]++;
    if (vec[x + 1][y] > 9) {
      flashPos(x + 1, y);
    }
  }
  if (x - 1 >= 0) {
    vec[x - 1][y]++;
    if (vec[x - 1][y] > 9) {
      flashPos(x - 1, y);
    }
  }
  if (y + 1 < vec[x].size()) {
    vec[x][y + 1]++;
    if (vec[x][y + 1] > 9) {
      flashPos(x, y + 1);
    }
  }
  if (y - 1 >= 0) {
    vec[x][y - 1]++;
    if (vec[x][y - 1] > 9) {
      flashPos(x, y - 1);
    }
  }
  if ((x + 1 < vec.size()) && (y + 1 < vec[x].size())) {
    vec[x + 1][y + 1]++;
    if (vec[x + 1][y + 1] > 9) {
      flashPos(x + 1, y + 1);
    }
  }
  if ((x - 1 >= 0) && (y + 1 < vec[x].size())) {
    vec[x - 1][y + 1]++;
    if (vec[x - 1][y + 1] > 9) {
      flashPos(x - 1, y + 1);
    }
  }
  if ((x + 1 < vec.size()) && (y - 1 >= 0)) {
    vec[x + 1][y - 1]++;
    if (vec[x + 1][y - 1] > 9) {
      flashPos(x + 1, y - 1);
    }
  }
  if ((x - 1 >= 0) && (y - 1 >= 0)) {
    vec[x - 1][y - 1]++;
    if (vec[x - 1][y - 1] > 9) {
      flashPos(x - 1, y - 1);
    }
  }
}

void processStep() {
  for (int i = 0u; i < vec.size(); i++) {
    for (int j = 0u; j < vec[i].size(); j++) {
      vec[i][j]++;
      flashed[i][j] = false;
    }
  }

  for (int i = 0u; i < vec.size(); i++) {
    for (int j = 0u; j < vec[i].size(); j++) {
      if (vec[i][j] > 9) {
        flashPos(i, j);
      }
    }
  }

  for (int i = 0u; i < vec.size(); i++) {
    for (int j = 0u; j < vec[i].size(); j++) {
      if (vec[i][j] > 9) {
        vec[i][j] = 0;
        numFlashes++;
      }
    }
  }
}

int main() {
  std::ifstream infile("input.txt");
  std::string line = "";

  auto i = 0u;
  while (std::getline(infile, line)) {
    vec.push_back(std::vector<int>());
    flashed.push_back(std::vector<bool>());
    for (auto j = 0u; j < line.length(); j++) {
      vec[i].push_back(line[j] - '0');
      flashed[i].push_back(false);
    }
    i++;
  }

  for (i = 0; i < 500; i++) {
    processStep();

    if (simultaneously()) {
      break;
    }

    /*
    printf("Step: %d\n", i + 1);
    for (auto i = 0u; i < vec.size(); i++) {
      for (auto j = 0u; j < vec[i].size(); j++) {
        printf("%d", vec[i][j]);
      }
      printf("\n");
    }
    */
  }
  // printf("numFlashes: %d\n", numFlashes);
  printf("simultaneously: %d", i + 1);
}