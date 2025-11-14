#include <cassert>
#include <iostream>
#include <vector>
#include <string>

auto LongestComStr(std::vector<char>& a, std::vector<char>& b) {
  int n = a.size();
  int m = b.size();
  std::vector<std::vector<int>> matrix(n + 1, std::vector<int>(m + 1, 0));

  int maxLen = 0;
  int end = 0;
    
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      if (a[i - 1] == b[j - 1]) {
        matrix[i][j] = matrix[i - 1][j - 1] + 1;
        if (matrix[i][j] > maxLen) {
          maxLen = matrix[i][j];
          end = i - 1;
        }
       } else {
          matrix[i][j] = 0;
      }
    }
  }
  std::vector<char> ans;

  if (maxLen == 0) {
    return ans;
  } else {
    for (int i = end - maxLen + 1; i <= end; ++i) {
      ans.push_back(a[i]);
    }
    return ans;
  }
}



int main() {
  std::vector<char> a1 = {'a', 'b', 'c', 'd'};
  std::vector<char> b1 = {'a', 'b', 'c', 'd', 'e', 'f'};
  std::vector<char> c1 = {'a', 'b', 'c', 'd'};
  std::vector<char> ans1 = LongestComStr(a1, b1);
  assert(ans1 == c1);

  std::vector<char> a2 = {'x', 'a', 'b', 'c', 'd'};
  std::vector<char> b2 = {'a', 'b', 'c', 'd', 'e', 'f'};
  std::vector<char> c2 = {'a', 'b', 'c', 'd'};
  std::vector<char> ans2 = LongestComStr(a2, b2);
  assert(ans2 == c2);

  std::vector<char> a3 = {'a', 'm', 'c', 'd'};
  std::vector<char> b3 = {'a', 'b', 'c', 'd', 'e', 'f'};
  std::vector<char> c3 = {'c', 'd'};
  std::vector<char> ans3 = LongestComStr(a3, b3);
  assert(ans3 == c3);

  std::vector<char> a4 = {'a', 'x', 'b', 'y', 'c'};
  std::vector<char> b4 = {'a', 'b', 'c', 'd', 'e', 'f'};
  std::vector<char> c4 = {'a'};
  std::vector<char> ans4 = LongestComStr(a4, b4);
  assert(ans4 == c4);


  /*
  int n = 0;
  int m = 0;
  std::cin >> n;
  std::vector<char> a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }
  std::cin >> m;
  std::vector<char> b(m);
  for (int i = 0; i < m; ++i) {
    std::cin >> b[i];
  }
  for (auto i : LongestComStr(a, b)) {
    std::cout << i << ' ';
  }
  */
  return 0;
}