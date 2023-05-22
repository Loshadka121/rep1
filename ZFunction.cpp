#include <iostream>
#include <vector>
#include <string>

size_t Min(size_t a, size_t b) {
  return (a < b) ? a : b;
}

std::vector<int> ZFunc(std::string& str) {
  std::vector<int> z(str.size(), 0);
  size_t left = 0, right = 0;
  z[0] = str.size();
  for (size_t i = 1; i < str.size(); ++i) {
    if (i < right) {
      z[i] = Min(z[i - left], right - i);
    }
    while (i + z[i] < str.size() and str[z[i]] == str[i + z[i]]) {
      ++z[i];
    }
    if (right < i + z[i]) {
      right = i + z[i];
      left = i;
    }
  }
  return z;
}

int main() {
  std::string str;
  std::cin >> str;

  std::vector<int> ans = ZFunc(str);
  for (size_t i = 0; i < ans.size(); ++i) {
    std::cout << ans[i] << ' ';
  }

  return 0;
}
