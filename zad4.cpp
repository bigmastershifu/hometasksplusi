#include <iostream>
#include <cstdint>
#include <vector>

class IPv4 {
 private:
  std::vector<std::uint8_t> parts_ = {0, 0, 0, 0};

 public:
  IPv4() = default;

  IPv4(std::uint8_t a, std::uint8_t b, std::uint8_t c, std::uint8_t d) {
    parts_[0] = a;
    parts_[1] = b;
    parts_[2] = c;
    parts_[3] = d;
  }
  //  префиксный
  IPv4& operator++() {
    for (int i = 3; i >= 0; --i) {
      if (++parts_[i] != 0) {
        return *this;
      }
      parts_[i] = 0;
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
      if (parts_[i] != 0) {
        --parts_[i];
        return *this;
      }
      parts_[i] = 255;
    }
    return *this;
  }

  IPv4 operator--(int) {
    IPv4 temp = *this;
    --(*this);
    return temp;
  }

  friend bool operator==(const IPv4& a, const IPv4& b) {
    return a.parts_ == b.parts_;
  }

  friend bool operator<(const IPv4& a, const IPv4& b) {
    return a.parts_ < b.parts_;
  }

  friend bool operator>(const IPv4& a, const IPv4& b) {
    return b < a;
  }

  friend std::ostream& operator<<(std::ostream& os, const IPv4& ip) {
    //  тут преобразование типов
    os << +ip.parts_[0] << '.'
       << +ip.parts_[1] << '.'
       << +ip.parts_[2] << '.'
       << +ip.parts_[3] << '\n';
    return os;
  }

  friend std::istream& operator>>(std::istream& is, IPv4& ip) {
    int a = 0;
    int b = 0;
    int c = 0;
    int d = 0;
    char d1, d2, d3;
    is >> a >> d1 >> b >> d2 >> c >> d3 >> d;
    if (is and d1 == '.' and d2 == '.' and d3 == '.' and 
        a >= 0 and a <= 255 and b >= 0 and b <= 255 and 
        c >= 0 and c <= 255 and d >= 0 and d <= 255) {
      ip.parts_[0] = a;
      ip.parts_[1] = b;
      ip.parts_[2] = c;
      ip.parts_[3] = d;
    }
    //  при некорректном вводе остаются дефолт значение ip поэтому надо вводить нормальные
    return is;
  }
};

int main() {
    IPv4 ip1, ip2;

    std::cin >> ip1;
    std::cin >> ip2;

    if (ip1 < ip2) {
        std::cout << "first smaller\n";
    } else if (ip1 > ip2) {
        std::cout << "first bigger\n";
    } else {
        std::cout << "equal\n";
    }
    std::cout << (++ip1);
    std:: cout << (ip1++);
    std::cout << ip1;

    return 0;
}
