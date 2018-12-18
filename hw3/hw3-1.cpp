#include <algorithm>
#include <array>
#include <cstring>
#include <iostream>
#include <set>
#include <stack>
#include <utility>
#include <vector>
#define MAX 100005 // thanks to tracy

void graph_dfs(const int _i, std::vector<bool> &_vis,
               const std::vector<std::vector<int>> &_graph,
               std::vector<int> &_order) {
  _vis.at(_i) = true;
  for (int i = 0; i < _graph.at(_i).size(); i++)
    if (!_vis.at(_graph.at(_i).at(i)))
      graph_dfs(_graph.at(_i).at(i), _vis, _graph, _order);
  _order.push_back(_i);
}

std::vector<bool> tgraph_dfs(const int _i, const std::vector<int> &_src,
                             std::vector<bool> &_vis,
                             const std::vector<std::vector<int>> &_t_graph) {
  std::vector<bool> cur(26, false);
  _vis.at(_i) = true;
  std::stack<int> stk;
  stk.push(_i);
  cur.at(_src.at(_i)) = true;
  while (stk.size()) {
    int x = stk.top();
    stk.pop();
    for (int j = 0; j < _t_graph.at(x).size(); j++) {
      if (!_vis.at(_t_graph.at(x).at(j))) {
        _vis.at(_t_graph.at(x).at(j)) = true;
        cur.at(_src.at(_t_graph.at(x).at(j))) = true;
        stk.push(_t_graph.at(x).at(j));
      }
    }
  }
  return cur;
}

bool check_single_node(const std::vector<bool> _cur,
                       const std::vector<bool> &_tar) {
  bool flag = true;
  for (int i = 0; i < 26; i++)
    if ((_tar.at(i)) && !(_cur.at(i)))
      flag = false;
  if (flag)
    return true;
  else
    return false;
}

void print_order(const std::vector<int> &_order) {
  std::cout << "order: ";
  for (int i : _order)
    std::cout << i << ' ';
  std::cout << std::endl;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  std::string source, target;
  std::vector<int> src, order;
  std::vector<bool> tar(26, false);
  std::vector<std::vector<int>> graph(n);
  std::vector<std::vector<int>> trans_graph(n);

  std::cin >> source;
  for (int i = 0; i < n; i++)
    src.push_back((int)source[i] - 'a');

  for (int i = 0; i < m; i++) {
    int u, v;
    std::cin >> u >> v;
    graph.at(u - 1).push_back(v - 1); // directed graph
    trans_graph.at(v - 1).push_back(u - 1);
  }

  std::cin >> target;
  for (int i = 0; i < target.size(); i++)
    tar.at((int)target[i] - 'a') = true;

  // DFS
  std::vector<bool> vis(n, false);
  for (int i = 0; i < n; i++) {
    if (!vis.at(i))
      graph_dfs(i, vis, graph, order);
  }
  // print_order(order);
  std::fill(vis.begin(), vis.end(), false);
  for (int i = n - 1; i >= 0; i--) { // using back-to-front to find SCC
    if (!vis.at(order.at(i))) {
      // std::cout << "\ni = " << i << ", node: " << order.at(i) << std::endl;
      std::vector<bool> cur(tgraph_dfs(order.at(i), src, vis, trans_graph));
      if (check_single_node(cur, tar)) { // restrict circle could pass
        std::cout << "Yes" << std::endl;
        return 0;
      }
    }
  }
  std::cout << "No" << std::endl;
}
