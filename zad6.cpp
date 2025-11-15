#include <cassert>
#include <iostream>
#include <vector>

std::vector<char> LongestComStr(std::vector<char>& str_1, std::vector<char>& str_2) {
  int str_1_size = str_1.size();
  int str_2_size = str_2.size();
  std::vector<std::vector<int>> matrix(str_1_size + 1, std::vector<int>(str_2_size + 1, 0));

  int max_len = 0;
  int end = 0;
    
  for (int i = 1; i <= str_1_size; ++i) {
    for (int j = 1; j <= str_2_size; ++j) {
      if (str_1[i - 1] == str_2[j - 1]) {
        matrix[i][j] = matrix[i - 1][j - 1] + 1;
        if (matrix[i][j] > max_len) {
          max_len = matrix[i][j];
          end = i - 1;
        }
       } else {
          matrix[i][j] = 0;
      }
    }
  }
  std::vector<char> result;

  if (max_len == 0) {
    return result;
  } else {
    for (int i = end - max_len + 1; i <= end; ++i) {
      result.push_back(str_1[i]);
    }
    return result;
  }
}

void TestMatchAtStart() {
  std::vector<char> str_1 = {'a', 'b', 'c', 'd'};
  std::vector<char> str_2 = {'a', 'b', 'c', 'd', 'e', 'f'};
  std::vector<char> expected = {'a', 'b', 'c', 'd'};
  std::vector<char> result = LongestComStr(str_1, str_2);
  assert(result == expected);
}

void TestMatchWithRubbish() {
  std::vector<char> str_1 = {'x', 'a', 'b', 'c', 'd'};
  std::vector<char> str_2 = {'a', 'b', 'c', 'd', 'e', 'f'};
  std::vector<char> expected = {'a', 'b', 'c', 'd'};
  std::vector<char> result = LongestComStr(str_1, str_2);
  assert(result == expected);
}

void TestMatchWithRubbish2() {
  std::vector<char> str_1 = {'a', 'm', 'c', 'd'};
  std::vector<char> str_2 = {'a', 'b', 'c', 'd', 'e', 'f'};
  std::vector<char> expected = {'c', 'd'};
  std::vector<char> result = LongestComStr(str_1, str_2);
  assert(result == expected);
}

void TestSingleChar() {
  std::vector<char> str_1 = {'a', 'x', 'b', 'y', 'c'};
  std::vector<char> str_2 = {'a', 'b', 'c', 'd', 'e', 'f'};
  std::vector<char> expected = {'a'};
  std::vector<char> result = LongestComStr(str_1, str_2);
  assert(result == expected);
}
void TestNoCom() {
  std::vector<char> str_1 = {'a', 'c', 'b'};
  std::vector<char> str_2 = {'d', 'e', 'f'};
  std::vector<char> expected = {};
  std::vector<char> result = LongestComStr(str_1, str_2);
  assert(result == expected);
}

int main() {
  TestMatchAtStart();
  TestMatchWithRubbish();
  TestMatchWithRubbish2();
  TestSingleChar();
  TestNoCom();
  return 0;
}
