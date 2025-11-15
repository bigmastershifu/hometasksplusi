#include <iostream>
#include <cstdint>
#include <vector>

class IPv4 {
 private:
  std::vector<std::uint8_t> parts = {0, 0, 0, 0};

 public:
  IPv4() = default;

  IPv4(std::uint8_t a, std::uint8_t b, std::uint8_t c, std::uint8_t d) {
    parts[0] = a;
    parts[1] = b;
    parts[2] = c;
    parts[3] = d;
  }
  //  префиксный
  IPv4& operator++() {
    for (int i = 3; i >= 0; --i) {
      if (++parts[i] != 0) {
        return *this;
      }
      parts[i] = 0;
    }
    return *this;
  }
  //  постфиксный
  IPv4 operator++(int) {
    IPv4 temp = *this;
    ++(*this);
    return temp;
  }

  IPv4& operator--() {
    for (int i = 3; i >= 0; --i) {
      if (parts[i] != 0) {
        --parts[i];
        return *this;
      }
      parts[i] = 255;
    }
    return *this;
  }

  IPv4 operator--(int) {
    IPv4 temp = *this;
    --(*this);
    return temp;
  }

  friend bool operator==(const IPv4& a, const IPv4& b) {
    return a.parts == b.parts;
  }

  friend bool operator<(const IPv4& a, const IPv4& b) {
    return a.parts < b.parts;
  }

  friend bool operator>(const IPv4& a, const IPv4& b) {
    return b < a;
  }

  void output() const {
    //  тут преобразование типов
    std::cout << +parts[0] << '.'
              << +parts[1] << '.'
              << +parts[2] << '.'
              << +parts[3] << '\n';
  }

  bool input() {
    int a = 0;
    int b = 0;
    int c = 0;
    int d = 0;
    char d1, d2, d3;
    std::cin >> a >> d1 >> b >> d2 >> c >> d3 >> d;
    if (std::cin and d1 == '.' and d2 == '.' and d3 == '.' and a >= 0 and a <= 255 and b >= 0 and b <= 255 and c >= 0 and c <= 255 and d >= 0 and d <= 255) {
      parts[0] = a;
      parts[1] = b;
      parts[2] = c;
      parts[3] = d;
      return true;
    } else {
      return false;
    }
  }
};

int main() {
    IPv4 ip1, ip2;

    if (!ip1.input()) {
        return 1;
    }

    if (!ip2.input()) {
        return 1;
    }

    if (ip1 < ip2) {
        std::cout << "first smaller\n";
    } else if (ip1 > ip2) {
        std::cout << "first bigger\n";
    } else {
        std::cout << "equal\n";
    }
    (++ip1).output();
    (ip1++).output();
    ip1.output();

    
    return 0;
}
