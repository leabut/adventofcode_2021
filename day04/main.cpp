#include <array>
#include <cstdio>
#include <fstream>
#include <vector>

constexpr auto numberOfPlayers = 100u;
using ArrayBool =
    std::array<std::array<std::array<bool, 5u>, 5u>, numberOfPlayers>;
using ArrayInt =
    std::array<std::array<std::array<int, 5u>, 5u>, numberOfPlayers>;

int checkBingo(ArrayBool &flag) {
  for (auto k = 0u; k < flag.size(); k++) {
    // count rows
    for (auto j = 0u; j < flag[0].size(); j++) {
      auto rowCount = 0u;
      for (auto i = 0u; i < flag[0][0].size(); i++) {
        if (flag[k][j][i] == true) {
          rowCount++;
        }
      }
      if (rowCount == 5u) {
        return k;
      }
    }
    // count columns
    for (auto i = 0u; i < flag[0][0].size(); i++) {
      auto columnCount = 0u;
      for (auto j = 0u; j < flag[0].size(); j++) {
        if (flag[k][j][i] == true) {
          columnCount++;
        }
      }
      if (columnCount == 5u) {
        return k;
      }
    }
  }
  return -1;
}

int checkLastBingo(ArrayBool &flag) {
  auto numberOfSolved = 0u;
  auto increased = false;
  for (auto k = 0u; k < flag.size(); k++) {
    increased = false;
    // count rows
    for (auto j = 0u; j < flag[0].size(); j++) {
      auto rowCount = 0u;
      for (auto i = 0u; i < flag[0][0].size(); i++) {
        if (flag[k][j][i] == true) {
          rowCount++;
        }
      }
      if (rowCount == 5u) {
        numberOfSolved++;
        increased = true;
        break;
      }
    }
    if (increased) {
      continue;
    }
    // count columns
    for (auto i = 0u; i < flag[0][0].size(); i++) {
      auto columnCount = 0u;
      for (auto j = 0u; j < flag[0].size(); j++) {
        if (flag[k][j][i] == true) {
          columnCount++;
        }
      }
      if (columnCount == 5u) {
        numberOfSolved++;
        break;
      }
    }
  }

  if (numberOfSolved == (numberOfPlayers - 1u)) {
    auto won = false;
    for (auto k = 0u; k < flag.size(); k++) {
      won = false;
      // count rows
      for (auto j = 0u; j < flag[0].size(); j++) {
        auto rowCount = 0u;
        for (auto i = 0u; i < flag[0][0].size(); i++) {
          if (flag[k][j][i] == true) {
            rowCount++;
          }
        }
        if (rowCount == 5u) {
          won = true;
        }
      }
      // count columns
      for (auto i = 0u; i < flag[0][0].size(); i++) {
        auto columnCount = 0u;
        for (auto j = 0u; j < flag[0].size(); j++) {
          if (flag[k][j][i] == true) {
            columnCount++;
          }
        }
        if (columnCount == 5u) {
          won = true;
        }
      }

      if (won == false) {
        return k;
      }
    }
  }

  return -1;
}

void flagBingo(ArrayInt &field, ArrayBool &flag, int val) {
  for (auto k = 0u; k < flag.size(); k++) {
    for (auto j = 0u; j < flag[0].size(); j++) {
      for (auto i = 0u; i < flag[0][0].size(); i++) {
        if (field[k][j][i] == val) {
          flag[k][j][i] = true;
        }
      }
    }
  }
}

int getUnflaggedSum(ArrayInt &field, ArrayBool &flag, int player) {
  auto sum = 0u;
  auto k = player;
  for (auto j = 0u; j < flag[0].size(); j++) {
    for (auto i = 0u; i < flag[0][0].size(); i++) {
      if (flag[k][j][i] == false) {
        sum += field[k][j][i];
      }
    }
  }
  return sum;
}

void printFlagged(ArrayBool &flag) {
  for (auto k = 0u; k < flag.size(); k++) {
    for (auto j = 0u; j < flag[0].size(); j++) {
      for (auto i = 0u; i < flag[0][0].size(); i++) {
        if (flag[k][j][i] == true) {
          printf("X ");
        } else {
          printf("O ");
        }
      }
      printf("\n");
    }
    printf("\n");
  }
}

int main() {
  std::ifstream infile("input.txt");
  std::string line = "";
  std::string delimiter = " ";
  std::string drawDelimiter = ",";

  std::getline(infile, line);
  std::vector<int> draw{};
  {
    size_t pos = 0u;
    while ((pos = line.find(drawDelimiter)) != std::string::npos) {
      auto token = line.substr(0, pos);
      line.erase(0, pos + drawDelimiter.length());
      draw.push_back(std::stoi(token));
    }
    if (line.length() > 0) {
      draw.push_back(std::stoi(line));
    }
  }

  std::getline(infile, line);
  ArrayInt field{{{}}};
  ArrayBool flag{{{}}};
  {
    auto i = 0u;
    auto j = 0u;
    auto k = 0u;
    while (std::getline(infile, line)) {
      if (line.length() == 0u) {
        k++;
        j = 0u;
        continue;
      }

      size_t pos = 0u;
      while ((pos = line.find(delimiter)) != std::string::npos) {
        auto token = line.substr(0, pos);
        line.erase(0, pos + delimiter.length());
        if (token == "") {
          continue;
        }
        field[k][j][i] = std::stoi(token);
        i++;
      }
      if (line.length() > 0) {
        field[k][j][i] = std::stoi(line);
        i = 0u;
      }
      j++;
    }
  }

  auto player = -1;
  auto number = -1;
  for (auto it : draw) {
    flagBingo(field, flag, it);
    player = checkBingo(flag);
    number = it;

    if (player != -1) {
      break;
    }
  }

  printf("player: %d\n", player);
  printf("number: %d\n", number);
  auto sum = getUnflaggedSum(field, flag, player);
  printf("sum: %d\n", sum);
  printf("output1: %d\n", sum * number);

  player = -1;
  number = -1;
  for (auto i = 0u; i < draw.size(); i++) {
    flagBingo(field, flag, draw[i]);
    player = checkLastBingo(flag);
    number = draw[i];

    if (player != -1) {
      for (auto j = 1u; j < draw.size() - i; j++) {
        flagBingo(field, flag, draw[i + j]);
        auto simPlayer = checkLastBingo(flag);
        number = draw[i + j];
        if (simPlayer == -1) {
          break;
        }
      }
      break;
    }
  }

  printf("player: %d\n", player);
  printf("number: %d\n", number);
  sum = getUnflaggedSum(field, flag, player);
  printf("sum: %d\n", sum);
  printf("output2: %d\n", sum * number);

  //printFlagged(flag);

  /*
  for (auto k = 0u; k < field.size(); k++) {
    for (auto j = 0u; j < field[0].size(); j++) {
      for (auto i = 0u; i < field[0][0].size(); i++) {
        printf("%d ", field[k][j][i]);
      }
      printf("\n");
    }
    printf("\n");
  }
  */
}
