#include <iostream>
#include <vector>
#include <string>

std::vector<int> PrefixFunc(std::string& str) {
  std::vector<int> pref(str.size(), 0);
  for (size_t i = 1; i < str.size(); ++i) {
    int k = pref[i - 1];
    while (k > 0 and str[k] != str[i]) {
      k = pref[k - 1];
    }
    if (str[k] == str[i]) {
      pref[i] = k + 1;
    }
  }
  return pref;
}

int main() {
  std::string str;
  std::cin >> str;

  std::vector<int> ans = PrefixFunc(str);
  for (size_t i = 0; i < ans.size(); ++i) {
    std::cout << ans[i] << ' ';
  }

  return 0;
}
