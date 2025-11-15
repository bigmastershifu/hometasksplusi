#include <iostream>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <bit>

long long Log2(long long x) {
  //  глобально тут мы ищем старший бит
  if (x <= 0) {
    return -1;
  }
  long long biggest_bit = -1;
  while (x != 0) {
    x = x >> 1; //  делим на 2
    ++biggest_bit;
  }
  return biggest_bit;
}

long long Log2(double d) {
  uint64_t bits = std::bit_cast<uint64_t>(d);
  int exp = (bits >> 52) & 0b11111111111; //  сдвинули на 52 позиции получили экспоненту и знак а потом выкинули знак
  return exp - 1023;  //  так надо
}

void tests() {
  assert(Log2(3ll) == std::floor(std::log2(3)));
  assert(Log2(15ll) == std::floor(std::log2(15)));
  assert(Log2(100ll) == std::floor(std::log2(100)));
  assert(Log2(3.0) == std::floor(std::log2(3)));
  assert(Log2(1.66) == std::floor(std::log2(1.66)));
  assert(Log2(0.3) == std::floor(std::log2(0.3)));
}

int main() {
  tests();
  
  return 0;
}
