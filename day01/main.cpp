#include <cstdio>
#include <fstream>

int mainpartone() {
  std::ifstream infile("input.txt");

  std::string line;
  std::getline(infile, line);
  auto old = std::stoi(line);
  auto output = 0u;
  while (std::getline(infile, line)) {
    auto next = std::stoi(line);
    if(old < next) {
        output++;
    }
    old = next;
  }

  printf("output: %d\n", output);
}

int main() {
  std::ifstream infile("input.txt");

  std::string line;
  std::getline(infile, line);
  auto old = std::stoi(line);
  auto output = 0u;
  while (std::getline(infile, line)) {
    auto next = std::stoi(line);
    if(old < next) {
        output++;
    }
    old = next;
  }

  printf("output: %d\n", output);
}
