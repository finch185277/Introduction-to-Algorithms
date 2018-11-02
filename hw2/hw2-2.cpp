#include <algorithm>
#include <cstring>
#include <iostream>

#define MAX 10005

int lcs(std::string &_s1, std::string &_s2, int _m, int _n) {
  if (_m == 0 || _n == 0)
    return 0;
  if (_s1[_m - 1] == _s2[_n - 1])
    return lcs(_s1, _s2, _m - 1, _n - 1) + 1;
  else
    return std::max(lcs(_s1, _s2, _m, _n - 1), lcs(_s1, _s2, _m - 1, _n));
}

int main() {
  int ans[MAX];
  std::string str1;
  std::cin >> str1;
  std::string str2(str1);
  std::reverse(str2.begin(), str2.end());
  std::memset(ans, 1, sizeof ans);
  int len_s = str1.size();
  for (int i = 0; i < len_s; i++) {
    std::string tmp1(str1.substr(0, i));
    std::string tmp2(str2.substr(0, len_s - i - 1));
    ans[i] = 1 + 2 * lcs(tmp1, tmp2, tmp1.size(), tmp2.size());
  }
  for (int i = 0; i < len_s; i++)
    std::cout << ans[i] << ' ';
  std::cout << '\n';
}
