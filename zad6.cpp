#include <iostream>
#include <vector>

int main() {
  int rows = 10;
  int cols = 10;
  unsigned int random = 0;
  std::cin >> random;

  std::vector<std::vector<int>> desk(rows, std::vector<int>(cols, 0));
  std::vector<std::vector<int>> next_desk(rows, std::vector<int>(cols, 0));

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      random = random * 16623665 + 1013904666;
      if ((random % 100) < 50) {
        desk[i][j] = 1;
      } else {
        desk[i][j] = 0;
      }
    }
  }

  while (true) {
    for (int n = 0; n < 50; ++n) {
      std::cout << '\n';
    }

    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        if (desk[i][j] == 1) {
          std::cout << "# ";
        } else {
          std::cout << ". ";
        }
      }
      std::cout << '\n';
    }

    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        int neighbors = 0;

        for (int di = -1; di <= 1; ++di) {
          for (int dj = -1; dj <= 1; ++dj) {
            if (di == 0 and dj == 0) {
              continue;
            }

            int ni = i + di;
            int nj = j + dj;

            if (ni >= 0 and ni < rows and nj >= 0 and nj < cols) {
              if (desk[ni][nj] == 1) {
                neighbors = neighbors + 1;
              }
            }
          }
        }

        int is_alive = desk[i][j];
        next_desk[i][j] = 0;

        if (is_alive == 1) {
          if (neighbors == 2 or neighbors == 3) {
            next_desk[i][j] = 1;
          }
        } else {
          if (neighbors == 3) {
            next_desk[i][j] = 1;
          }
        }
      }
    }
    if (desk == next_desk) {
      break;
    } else {
      desk = next_desk;
    }
    for (long long k = 0; k < 266666666; ++k) {}
  }
  return 0;
}