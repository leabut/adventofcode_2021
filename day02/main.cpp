#include <cstdio>
#include <fstream>

int main() {
  std::ifstream infile("input.txt");
  std::string line = "";

  auto depth = 0;
  auto horizontal = 0;
  auto aim = 0;
  while (std::getline(infile, line)) {
    int val = 0;
    if (line.find("forward") != std::string::npos) {
      val = atoi(&line[8]);
      horizontal += val;
      depth += aim * val;
    } else if (line.find("down") != std::string::npos) {
      val = atoi(&line[5]);
      aim += val;
    } else if (line.find("up") != std::string::npos) {
      val = atoi(&line[3]);
      aim -= val;
    }
  }

  printf("depth: %d\n", depth);
  printf("horizontal: %d\n", horizontal);
  printf("output: %d\n", depth * horizontal);
}
