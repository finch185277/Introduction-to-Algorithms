#include <cstring>
#include <iostream>
#include <vector>

#define MAX 10005
int dp[MAX][MAX];
std::vector<std::string> global_vc;

int lps(std::string &s, int i, int j) {
  if (i == j)
    return 1;
  if (i > j)
    return 0;
  if (dp[i][j] != -1)
    return dp[i][j];
  if (s[i] == s[j]) {
    dp[i][j] = lps(s, i + 1, j - 1) + 2;
  } else if (lps(s, i + 1, j) > lps(s, i, j - 1)) {
    dp[i][j] = lps(s, i + 1, j);
  } else if (lps(s, i + 1, j) < lps(s, i, j - 1)) {
    dp[i][j] = lps(s, i, j - 1);
  } else {
    dp[i][j] = lps(s, i, j - 1);
  }
  return dp[i][j];
}

void subsequences(const std::string &prefix, const std::string &suffix,
                  int max_ss_len) {
  if (prefix.length() >= 1 && prefix.length() <= max_ss_len) {
    global_vc.push_back(prefix);
  }
  for (size_t i = 0; i < suffix.length(); ++i)
    subsequences(prefix + suffix[i], suffix.substr(i + 1), max_ss_len);
}

int max_palin_in_subsequence(std::string &base, std::string &patch,
                             int max_patch_len, bool flag) {
  int max_palin;
  max_palin = lps(base, 0, base.size() - 1);
  std::cout << "=============base: " << base << '\n';
  std::cout << "=============patch: " << patch << '\n';
  std::cout << "=============mpl: " << max_patch_len << '\n';
  subsequences("", patch, max_patch_len);
  for (auto ss = global_vc.begin(); ss != global_vc.end(); ++ss) {
    std::string _tmp(base);
    if (flag)
      _tmp.append(*ss);
    else
      _tmp.insert(0, *ss);
    std::cout << _tmp << '\n';
    max_palin = std::max(max_palin, lps(_tmp, 0, _tmp.size() - 1));
    std::cout << "---palin: " << max_palin << " --tmp: " << _tmp;
    std::cout << " ---lps: " << lps(_tmp, 0, _tmp.size() - 1) << '\n';
  }
  global_vc.clear();
  std::cout << '\n';
  return max_palin;
}

int main() {
  int len_s;
  int ans[MAX];
  std::string s;
  std::cin >> s;
  len_s = s.size();
  std::memset(dp, -1, sizeof dp);
  std::memset(ans, 1, sizeof ans);
  for (int i = 0; i < len_s; i++) {
    if (i == len_s / 2 && len_s % 2 == 1) {
      ans[i] = lps(s, 0, len_s - 1);
    } else if (i < len_s / 2) {
      std::string tmp;
      std::string tmp2;
      tmp.append(s.substr(0, i + 1)); // append(pos, len)
      tmp2.append(s.substr(i + 1, len_s - i - 1));
      ans[i] = max_palin_in_subsequence(tmp, tmp2, i, true);
    } else if (i >= len_s / 2) {
      std::string tmp;
      std::string tmp2;
      tmp.append(s.substr(i, len_s - i));
      tmp2.append(s.substr(0, i));
      ans[i] = max_palin_in_subsequence(tmp, tmp2, len_s - i - 1, false);
    }
  }
  for (int i = 0; i < len_s; i++)
    std::cout << ans[i] << ' ';
  std::cout << '\n';
}
