#include <iostream>
#include <vector>

std::vector<char> polind(std::vector<char>& s) {
  int n = s.size();
  int maxlenth = 1;
  int start = 0;

  for (int i = 0; i < n; ++i) {
    for (int j = i; j < n; ++j) {
      int lenth = j - i + 1;
      int left = i;
      int right = j;
      bool palindtrue = true;

      while (left < right) {
        if (s[left] != s[right]) {
          palindtrue = false;
          break;
        }
        ++left;
        --right;
      }

      if (palindtrue and lenth > maxlenth) {
        maxlenth = lenth;
        start = i;
      }
    }
  }

  std::vector<char> res;
  for (int i = start; i < start + maxlenth; ++i) {
    res.push_back(s[i]);
  }

  return res;
}

int main() {
  std::vector<char> s1 = {'c', 'a', 'b', 'b', 'a', 'x'};
  std::vector<char> s2 = {'c', 'a', 'b', 'r', 'y', 'x'};
  std::vector<char> palindrome1 = polind(s1);
  std::vector<char> palindrome2 = polind(s2);


  for (auto c : palindrome1) {
    std::cout << c << ' ';
  }
  std::cout << '\n';
  for (auto c : palindrome2) {
    std::cout << c << ' ';
  }

  return 0;
}