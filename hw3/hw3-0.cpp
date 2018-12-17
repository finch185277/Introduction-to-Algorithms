#include <algorithm>
#include <array>
#include <cstring>
#include <iostream>
#include <set>
#include <stack>
#include <utility>
#include <vector>
#define MAX 100005 // thanks to tracy

int main() {
  int n, m;
  std::cin >> n >> m;
  std::string source, target;
  std::vector<int> src;
  std::vector<bool> tar(26, false);
  std::vector<std::vector<int>> graph(n);

  std::cin >> source;
  for (int i = 0; i < n; i++)
    src.push_back((int)source[i] - 'a');

  for (int i = 0; i < m; i++) {
    int u, v;
    std::cin >> u >> v;
    graph.at(u - 1).push_back(v - 1); // undirected graph
    graph.at(v - 1).push_back(u - 1);
  }

  std::cin >> target;
  for (int i = 0; i < target.size(); i++)
    tar.at((int)target[i] - 'a') = true;

  // DFS
  bool flag = true;
  std::vector<bool> vis(n, false);
  for (int i = 0; i < n; i++) {
    if (vis.at(i)) // already visited
      continue;
    vis.at(i) = true;
    std::vector<bool> cur(26, false);
    std::stack<int> stk;
    cur.at(src.at(i)) = true;
    stk.push(i);
    while (stk.size()) {
      int x = stk.top();
      stk.pop();
      for (int j = 0; j < graph.at(x).size(); j++) { // for possible next node
        if (!vis.at(graph.at(x).at(j))) { // if next possible not visited
          vis.at(graph.at(x).at(j)) = true;
          cur.at(src.at(graph.at(x).at(j))) = true; // save node
          stk.push(graph.at(x).at(j));
        }
      }
    }

    flag = true;
    for (int i = 0; i < 26; i++) {
      if (tar.at(i) && !cur.at(i))
        flag = false;
    }
    if (flag) {
      std::cout << "Yes" << std::endl;
      break;
    }
  }

  if (!flag)
    std::cout << "No" << std::endl;
}
