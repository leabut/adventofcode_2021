#include <algorithm>
#include <array>
#include <bits/stdc++.h>
#include <cstdio>
#include <fstream>
#include <limits>
#include <map>
#include <vector>

std::vector<std::vector<char>> vec;
std::vector<std::vector<char>> open;
std::vector<char> illegal;
std::vector<std::vector<char>> closing;
std::vector<bool> remains;
std::vector<long> scores;

std::string closeRemains(int row) {
  std::string ret = "";
  for (int i = open[row].size() - 1; i >= 0; i--) {
    switch (open[row][i]) {
    case '<':
      ret += ">";
      break;
    case '{':
      ret += "}";
      break;
    case '(':
      ret += ")";
      break;
    case '[':
      ret += "]";
      break;
    default:
      continue;
    }
    open[row].erase(open[row].begin() + i);
  }
  return ret;
}

bool reverseSearch(int row, char c) {
  switch (c) {
  case '}':
  case '>':
  case ')':
  case ']':
    break;
  default:
    return true;
  }

  if (open[row].size() == 0u) {
    return false;
  }

  for (int i = open[row].size() - 1; i >= 0; i--) {
    switch (open[row][i]) {
    case '<':
      if (c != '>')
        return false;
      break;
    case '{':
      if (c != '}')
        return false;
      break;
    case '(':
      if (c != ')')
        return false;
      break;
    case '[':
      if (c != ']')
        return false;
      break;
    default:
      continue;
    }
    open[row].erase(open[row].begin() + i);
    return true;
  }

  return false;
}

int main() {
  std::ifstream infile("input.txt");
  std::string line = "";

  auto i = 0u;
  while (std::getline(infile, line)) {
    vec.push_back(std::vector<char>());
    for (auto j = 0u; j < line.length(); j++) {
      vec[i].push_back(line[j]);
    }
    i++;
  }

  for (auto i = 0u; i < vec.size(); i++) {
    open.push_back(std::vector<char>());
    for (auto j = 0u; j < vec[i].size(); j++) {
      // printf("%c", vec[i][j]);
      if (reverseSearch(i, vec[i][j])) {
        switch (vec[i][j]) {
        case '}':
        case '>':
        case ']':
        case ')':
          continue;
        }
        open[i].push_back(vec[i][j]);
      } else {
        printf("Illegal: %c\n", vec[i][j]);
        illegal.push_back(vec[i][j]);
        remains.push_back(false);
        break;
      }
    }
    if (remains.size() <= i) {
      remains.push_back(true);
    }
  }

  auto sum = 0u;
  for (auto it : illegal) {
    switch (it) {
    case ')':
      sum += 3;
      break;
    case ']':
      sum += 57;
      break;
    case '}':
      sum += 1197;
      break;
    case '>':
      sum += 25137;
      break;
    }
  }

  // correct 358737
  printf("%d\n", sum);

  for (auto i = 0u; i < remains.size(); i++) {
    if (remains[i] == true) {
      auto ret = closeRemains(i);

      long score = 0u;
      for (auto j = 0u; j < ret.length(); j++) {
        score *= 5;
        switch (ret[j]) {
        case ')':
          score += 1;
          break;
        case ']':
          score += 2;
          break;
        case '}':
          score += 3;
          break;
        case '>':
          score += 4;
          break;
        }
      }
      scores.push_back(score);
    }
  }

  std::sort(scores.begin(), scores.end());

  long output2 = scores[scores.size()/2];
  printf("output2: %ld\n", output2);
}