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

enum IsBang { No = 0, Yes = 1, Random = 2 };

int IsBangFunc(std::string str) {
  std::vector<int> ans = PrefixFunc(str);
  int delta = ans[ans.size() - 1];

  int is_bang;

  if (str[delta] == '1') {
    is_bang = Yes;
  } else if (str[delta] == '0') {
    is_bang = No;
  } else {
    is_bang = Random;
  }

  if (is_bang != Random) {
    for (int i = delta + 1; str[i] != '#'; ++i) {
      if (str[i] != str[str.size() / 2 + i - delta]) {
        is_bang = (str[str.size() - 1] == 1) ? Yes : No;
        break;
      }
    }
  }
  return is_bang;
}

std::string Reverse(std::string str) {
  char a;
  for (size_t i = 0; i < str.size() / 2; ++i) {
    a = str[str.size() - 1 - i];
    str[str.size() - 1 - i] = str[i];
    str[i] = a;
  }
  return str;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  std::string str_before;
  std::string str_after;
  std::cin >> str_before;
  std::cin >> str_after;

  std::string str;
  str = str_before + '#' + str_after;
  int is_bang_r = IsBangFunc(str);

  str = Reverse(str_before) + '#' + Reverse(str_after);
  int is_bang_l = IsBangFunc(str);

  if (is_bang_r != is_bang_l) {
    std::cout << "Random";
  } else {
    switch (is_bang_r) {
      case 0:
        std::cout << "No";
        break;
      case 1:
        std::cout << "Yes";
        break;
      case 2:
        std::cout << "Random";
        break;
      default:
        break;
    }
  }

  return 0;
}
