#include <iostream>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <bit>

long long floor_log_2(long long x) {
  //  глобально тут мы ищем старший бит
  if (x <= 0) {
    return -1;
  }
  long long  n = -1;
  while (x != 0) {
    x = x >> 1; //  делим на 2
    ++n;
  }
  return n;
}

long long floor_double_log2(double d) {
  uint64_t bits = std::bit_cast<uint64_t>(d);
  int exp = (bits >> 52) & 0b11111111111; //  сдвинули на 52 позиции получили экспоненту и знак а потом выкинули знак
  return exp - 1023;  //  так надо
}

int main() {
  assert(floor_log_2(3) == std::floor(std::log2(3)));
  assert(floor_log_2(15) == std::floor(std::log2(15)));
  assert(floor_log_2(100) == std::floor(std::log2(100)));
  assert(floor_double_log2(3) == std::floor(std::log2(3)));
  assert(floor_double_log2(1.66) == std::floor(std::log2(1.66)));
  assert(floor_double_log2(0.3) == std::floor(std::log2(0.3)));

  return 0;
}
