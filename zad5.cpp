#include <iostream>
#include <string>
#include <vector>

std::vector<int> values = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
std::vector<std::string> symbols = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};

std::string ToRim(int num) { 
  std::string res;
  int i = 0;
    
  while (num > 0) {
    if (i >= values.size()) {
      break;
    }
    int count = num / values[i];
    for (int j = 0; j < count; ++j) {
      res = res + symbols[i];
    }
    num = num % values[i];
    ++i;
  }
    
  return res;
}

int main() {
  for (int i = 1; i <= 1000; ++i) {
    std::cout << i << ' ' << ToRim(i) << '\n';
  }
  return 0;
}