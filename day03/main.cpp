#include <array>
#include <cstdio>
#include <fstream>
#include <vector>

bool getCommonBit(std::vector<int> &vec, int bitPos) {
  int amount = 0;
  for (auto i = 0u; i < vec.size(); i++) {
    if ((vec[i] & (0x01u << bitPos)) > 0) {
      amount++;
    } else {
      amount--;
    }
  }
  return (amount >= 0);
}

bool removeMatching(std::vector<int> &vec, bool val, int pos) {
  for (auto it = vec.begin(); it != vec.end(); it++) {
    if (((*it) & (0x01u << pos)) == (val << pos)) {
      it = vec.erase(it);
      it--;
    }
  }
}

int main() {
  std::ifstream infile("input.txt");
  std::string line = "";

  std::array<int, 12u> occurences{};
  while (std::getline(infile, line)) {
    int val = std::stoi(line, nullptr, 2);

    for (auto i = 0u; i < occurences.size(); i++) {
      if ((val & (0x01u << i)) > 0) {
        occurences[i]++;
      } else {
        occurences[i]--;
      }
    }
  }

  int gamma = 0u;
  int epsilon = 0u;
  for (auto i = 0u; i < occurences.size(); i++) {
    if (occurences[i] > 0) {
      gamma |= 0x01u << i;
      epsilon |= 0x00u;
    }
    if (occurences[i] < 0) {
      gamma |= 0x00u;
      epsilon |= 0x01u << i;
    }
    if (occurences[i] == 0) {
      printf("Oh oh\n");
    }
  }

  printf("gamma: %d\n", gamma);
  printf("epsilon: %d\n", epsilon);
  printf("result: %d\n", gamma * epsilon);

  infile.clear();
  infile.seekg(0);

  std::vector<int> numbersO2{};
  std::vector<int> numbersCO2{};
  while (std::getline(infile, line)) {
    int val = std::stoi(line, nullptr, 2);
    numbersO2.push_back(val);
    numbersCO2.push_back(val);
  }

  int i = 11u;
  while (numbersO2.size() > 1u) {
    auto bitVal = getCommonBit(numbersO2, i);
    removeMatching(numbersO2, !bitVal, i);
    i--;
    if (i < 0) {
      break;
    }
  }

  i = 11u;
  while (numbersCO2.size() > 1u) {
    auto bitVal = getCommonBit(numbersCO2, i);
    removeMatching(numbersCO2, bitVal, i);
    i--;
    if (i < 0) {
      break;
    }
  }

  printf("numbersO2.size(): %d\n", numbersO2.size());
  printf("numbersCO2.size(): %d\n", numbersCO2.size());

  printf("O2: %d\n", numbersO2[0]);
  printf("CO2: %d\n", numbersCO2[0]);
  printf("O2 * CO2: %d\n", numbersO2[0] * numbersCO2[0]);
}
