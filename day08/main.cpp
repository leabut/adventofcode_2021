#include <algorithm>
#include <array>
#include <bits/stdc++.h>
#include <cstdio>
#include <fstream>
#include <limits>
#include <map>
#include <vector>

/*
std::map<int, int> mapAmountToNum{};
int main() {
  std::ifstream infile("input.txt");
  std::string line = "";
  std::string delimiter = " ";

  std::vector<std::string> vec{};

  mapAmountToNum.insert(std::make_pair<int, int>(2, 1));
  mapAmountToNum.insert(std::make_pair<int, int>(3, 7));
  mapAmountToNum.insert(std::make_pair<int, int>(4, 4));
  mapAmountToNum.insert(std::make_pair<int, int>(7, 8));

  while (std::getline(infile, line)) {
    auto pos = line.find(" | ");
    line.erase(0, pos + std::string(" | ").length());

    while ((pos = line.find(delimiter)) != std::string::npos) {
      auto token = line.substr(0, pos);
      line.erase(0, pos + delimiter.length());
      vec.push_back(token);
    }
    vec.push_back(line);
  }

  auto sum = 0u;
  for (auto it : vec) {
    if (mapAmountToNum.find(it.length()) != mapAmountToNum.end())
      sum++;
  }

  printf("ouptut: %d\n", sum);
}
*/

bool contains(const std::string &a, const std::string &b) {
  for (auto it : a) {
    bool contained = false;
    for (auto it2 : b) {
      if (it2 == it) {
        contained = true;
        break;
      }
    }
    if (contained == false) {
      return false;
    }
    contained = false;
  }
  return true;
}

int distance(std::string a, std::string b) {
  auto dist1 = 0u;
  for (auto it : a) {
    bool contained = false;
    for (auto it2 : b) {
      if (it2 == it) {
        contained = true;
        break;
      }
    }
    if (contained == false) {
      dist1++;
    }
    contained = false;
  }

  auto dist2 = 0u;
  for (auto it : b) {
    bool contained = false;
    for (auto it2 : a) {
      if (it2 == it) {
        contained = true;
        break;
      }
    }
    if (contained == false) {
      dist2++;
    }
    contained = false;
  }

  auto dist = 0u;
  return std::max(dist1, dist2);
}

const std::string numToStr[10] = {"abcefg",  "cf",    "acdeg",  "acdfg",
                                  "bcdf",    "abdfg", "abdefg", "acf",
                                  "abcdefg", "abcdfg"};

int main() {
  std::ifstream infile("input.txt");
  std::string line = "";
  std::string delimiter = " ";

  std::vector<std::vector<std::string>> vecLeft{{}};
  std::vector<std::vector<std::string>> vecRight{{}};

  auto i = 0u;
  while (std::getline(infile, line)) {
    auto pos = line.find(" | ");
    auto tokenLeft = line.substr(0, pos);
    line.erase(0, pos + std::string(" | ").length());

    vecLeft.push_back(std::vector<std::string>{});
    while ((pos = tokenLeft.find(delimiter)) != std::string::npos) {
      auto token2 = tokenLeft.substr(0, pos);
      tokenLeft.erase(0, pos + delimiter.length());
      vecLeft[i].push_back(token2);
    }
    vecLeft[i].push_back(tokenLeft);

    vecRight.push_back(std::vector<std::string>{});
    while ((pos = line.find(delimiter)) != std::string::npos) {
      auto token = line.substr(0, pos);
      line.erase(0, pos + delimiter.length());
      vecRight[i].push_back(token);
    }
    vecRight[i].push_back(line);
    i++;
  }

  /*
  for (auto i = 0u; i < vecRight.size(); i++) {
    for (auto it2 : vecRight[i]) {
      vecLeft[i].push_back(it2);
      printf("%s\n", it2.c_str());
    }
    printf("\n");
  }
  */

  std::map<std::string, int> myMap{};
  for (auto it = vecLeft.begin(); *it != vecLeft[1]; it++) {
    for (auto it2 = it->begin(); it2 != it->end(); it2++) {
      std::sort(it2->begin(), it2->end());
      // printf("%s\n", it2->c_str());
      if (it2->length() == 2u) {
        myMap.insert(std::make_pair<std::string, int>(it2->c_str(), 1));
        it2 = it->erase(it2);
        it2--;
      }
      if (it2->length() == 3u) {
        myMap.insert(std::make_pair<std::string, int>(it2->c_str(), 7));
        it2 = it->erase(it2);
        it2--;
      }
      if (it2->length() == 4u) {
        myMap.insert(std::make_pair<std::string, int>(it2->c_str(), 4));
        it2 = it->erase(it2);
        it2--;
      }
      if (it2->length() == 7u) {
        myMap.insert(std::make_pair<std::string, int>(it2->c_str(), 8));
        it2 = it->erase(it2);
        it2--;
      }
    }
    for (auto it2 = it->begin(); it2 != it->end(); it2++) {
      for (auto it3 = myMap.begin(); it3 != myMap.end(); it3++) {
        if (distance(it3->first, it2->c_str()) == 1u) {
          printf("%s in %s\n", it3->first.c_str(), it2->c_str());
          printf("distance: %d\n", distance(it3->first, it2->c_str()));
        }
      }
      // printf("%s\n", it2->c_str());
    }
    myMap.clear();
  }
}