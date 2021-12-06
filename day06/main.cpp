#include <array>
#include <cstdio>
#include <fstream>
#include <vector>

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

#if 0
  for (auto k = 0u; k < 80; k++) {
    auto count = 0u;
    for (auto i = 0u; i < vec.size(); i++) {
      if (vec[i] == 0) {
        vec[i] = 6;
        count++;
        continue;
      }
      vec[i]--;
    }
    for (auto i = 0u; i < count; i++) {
      vec.push_back(8);
    }
    /*
    printf("day %d: ", k + 1);
    for (auto i = 0u; i < vec.size(); i++) {
      printf("%d,", vec[i]);
    }
    printf("\n");
    */
  }
  printf("output: %ld\n", vec.size());
#endif

  std::array<long long, 9u> fish{};
  for (auto i = 0u; i < vec.size(); i++) {
    fish[vec[i]]++;
  }

  for (auto k = 0u; k < 256u; k++) {
    long long tmp = fish[0];
    fish[0] = fish[1];
    fish[1] = fish[2];
    fish[2] = fish[3];
    fish[3] = fish[4];
    fish[4] = fish[5];
    fish[5] = fish[6];
    fish[6] = fish[7] + tmp;
    fish[7] = fish[8];
    fish[8] = tmp;
  }

  long long sum = 0u;
  for (auto i = 1u; i < fish.size(); i++) {
    sum += fish[i];
  }

  printf("output2: %lld\n", sum);
}
