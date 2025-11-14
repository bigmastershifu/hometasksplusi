#include <iostream>
#include <string>
#include <iomanip>

unsigned int bintogray(unsigned int bin) {
  return bin ^ (bin >> 1);
}

unsigned int graytobin(unsigned int gray) {
  unsigned int bin = gray;
  while (gray > 0) {
    gray = gray >> 1;
    bin = bin ^ gray;
  }
  return bin;
}

std::string intostring(unsigned int num, int width) {
  std::string bin;
  for (int i = width - 1; i >= 0; --i) {
    if (num & (1 << i)) {
      bin = bin + '1';
    } else {
      bin = bin + '0';
    }
  }
  return bin;
}

int main() {
  unsigned int n = 0;
  std::cin >> n;
  std::string bini = intostring(n, 5);
  unsigned int gray = bintogray(n);
  std::string bingray = intostring(gray, 5);
  unsigned int decode = graytobin(gray);
  std::string bindecode = intostring(decode, 5);
  std::cout << std::setw(2) << n << ' ' << bini
            << ' ' << bingray
            << ' ' << bindecode << '\n';

  return 0;
}