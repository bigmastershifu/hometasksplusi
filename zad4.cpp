#include <iostream>
#include <cstdint>
#include <vector>

class IPv4 {
 private:
  std::vector<std::uint8_t> octets = {0, 0, 0, 0};

 public:
  IPv4() = default;

  IPv4(std::uint8_t a, std::uint8_t b, std::uint8_t c, std::uint8_t d) {
    octets[0] = a;
    octets[1] = b;
    octets[2] = c;
    octets[3] = d;
  }

  IPv4& operator++() {
    for (int i = 3; i >= 0; --i) {
      if (++octets[i]) {
        return *this;
      }
      octets[i] = 0;
    }
    return *this;
  }

  IPv4 operator++(int) {
    IPv4 temp = *this;
    ++(*this);
    return temp;
  }

  IPv4& operator--() {
    for (int i = 3; i >= 0; --i) {
      if (octets[i]--) {
        return *this;
      }
      octets[i] = 255;
    }
    return *this;
  }

  IPv4 operator--(int) {
    IPv4 temp = *this;
    --(*this);
    return temp;
  }

  friend bool operator==(const IPv4& lhs, const IPv4& rhs) {
    return std::equal(lhs.octets.begin(), lhs.octets.end(), rhs.octets.begin());
  }

  friend bool operator<(const IPv4& lhs, const IPv4& rhs) {
    return std::lexicographical_compare(lhs.octets.begin(), lhs.octets.end(), rhs.octets.begin(), rhs.octets.end());
  }

  friend bool operator>(const IPv4& lhs, const IPv4& rhs) {
    return rhs < lhs;
  }

  void output() const {
    std::cout << +octets[0] << '.'
              << +octets[1] << '.'
              << +octets[2] << '.'
              << +octets[3];
  }

  bool input() {
    int a, b, c, d;
    char d1, d2, d3;
    std::cin >> a >> d1 >> b >> d2 >> c >> d3 >> d;
    if (std::cin and d1 == '.' and d2 == '.' and d3 == '.' and a >= 0 && a <= 255 and b >= 0 and b <= 255 and c >= 0 and c <= 255 and d >= 0 and d <= 255) {
      octets[0] = a;
      octets[1] = b;
      octets[2] = c;
      octets[3] = d;
      return true;
    } else {
      return false;
    }
  }
};

int main() {
  IPv4 ip;
  if (ip.input()) {
    ip.output();

    IPv4 next = ip++;
    std::cout << "post-increment ";
    next.output();
    std::cout << '\n';

    std::cout << "IP after increment ";
    ip.output();
    std::cout << '\n';

    --ip;
    std::cout << "pre-decrement";
    ip.output();
    std::cout << '\n';

    IPv4 another(192, 168, 0, 1);
    if (ip == another) {
      std::cout << "IP equal " << '\n';
    }
  }
  return 0;
}