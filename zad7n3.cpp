#include <iostream>
#include <vector>
#include <cassert>

std::vector<char> FindPalindrome(std::vector<char>& s) {
  int str_size = s.size();
  int max_lenth = 1;
  int start = 0;

  for (int i = 0; i < str_size; ++i) {
    for (int j = i; j < str_size; ++j) {
      int lenth = j - i + 1;
      int left = i;
      int right = j;
      bool is_palindrome = true;

      while (left < right) {
        if (s[left] != s[right]) {
          is_palindrome = false;
          break;
        }
        ++left;
        --right;
      }

      if (is_palindrome and lenth > max_lenth) {
        max_lenth = lenth;
        start = i;
      }
    }
  }

  std::vector<char> result;
  for (int i = start; i < start + max_lenth; ++i) {
    result.push_back(s[i]);
  }

  return result;
}

void test1() {
  std::vector<char> str_1 = {'c', 'a', 'b', 'b', 'a', 'x'};
  std::vector<char> expected = {'a', 'b', 'b', 'a'};
  assert(FindPalindrome(str_1) == expected);
}

void test2() {
  std::vector<char> str_2 = {'c', 'a', 'b', 'r', 'y', 'x'};
  std::vector<char> expected = {'c'};
  assert(FindPalindrome(str_2) == expected);
}

int main() {
  test1();
  test2();

  return 0;
}
