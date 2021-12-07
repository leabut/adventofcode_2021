#include <array>
#include <cstdio>
#include <fstream>
#include <limits>
#include <vector>

int costCalc(int num) {
  int sum = 0u;
  for (auto i = 1u; i <= num; i++) {
    sum += i;
  }
  return sum;
}

int main() {
  std::ifstream infile("input.txt");
  std::string line = "";
  std::string delimiter = ",";

  std::vector<int> vec;

  while (std::getline(infile, line)) {
    size_t pos = 0u;
    while ((pos = line.find(delimiter)) != std::string::npos) {
      auto token = line.substr(0, pos);
      line.erase(0, pos + delimiter.length());
      vec.push_back(std::stoi(token));
    }
    vec.push_back(std::stoi(line));
  }

  auto minCost = std::numeric_limits<int>::max();
  auto pos = 0u;
  for (int i = 0; i < 1000; i++) {
    auto cost = 0u;
    for (auto it : vec) {
      cost += costCalc(std::abs(it - i));
    }
    if (cost < minCost) {
      minCost = cost;
      pos = i;
    }
  }

  printf("ouptut: %d\n", minCost);
}
