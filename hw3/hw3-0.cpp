#include <algorithm>
#include <array>
#include <cstring>
#include <iostream>
#include <stack>
#include <utility>
#include <vector>
#define MAX 100005

std::pair<long long, long long> get_edge() {
  long long _a, _b;
  std::cin >> _a >> _b;
  std::pair<long long, long long> _tmp(_a - 1, _b - 1); // 0-base
  return _tmp;
}

std::vector<std::vector<bool>>
make_connect_graph(long long _node_num,
                   std::vector<std::pair<long long, long long>> &_edges) {
  std::vector<std::vector<bool>> _graph_table(
      _node_num, std::vector<bool>(_node_num, false));
  for (auto _itr = _edges.begin(); _itr != _edges.end(); _itr++) {
    _graph_table.at(_itr->first).at(_itr->second) = true;
    _graph_table.at(_itr->second).at(_itr->first) = true;
  }
  for (int i = 0; i < _node_num; i++)
    _graph_table.at(i).at(i) = true;
  return _graph_table;
}

bool depth_first_search(long long _node_num, std::string &_node_str,
                        std::string &_target_str,
                        std::vector<std::vector<bool>> &_graph) {
  std::vector<int> _check_stack;
  for (int i = 0; i < _node_num; i++)
    _check_stack.push_back(i);

  for (int i = 0; i < _target_str.size(); i++) {
    std::vector<int> _cache_stack;
    while (!_check_stack.empty()) {
      for (int j = 0; j < _node_num; j++) {
        if (_target_str[i] == _node_str[j] && _graph[_check_stack.back()][j]) {
          _cache_stack.push_back(j);
        }
      }
      _check_stack.pop_back();
    }
    std::sort(_cache_stack.begin(), _cache_stack.end());
    _cache_stack.erase(std::unique(_cache_stack.begin(), _cache_stack.end()),
                       _cache_stack.end());
    _check_stack = _cache_stack;
    if (_check_stack.empty())
      return false;
  }
  return true;
}

int main() {
  // initial
  long long node_num, edge_num;
  bool exist_flag = false;
  std::string node_str, target_str;
  std::vector<std::pair<long long, long long>> edges;
  std::cin >> node_num >> edge_num >> node_str;
  long long _edge_num(edge_num);
  while (_edge_num--) {
    edges.push_back(get_edge());
  }
  std::vector<std::vector<bool>> graph_table =
      make_connect_graph(node_num, edges);
  std::cin >> target_str;

  // solve
  exist_flag = depth_first_search(node_num, node_str, target_str, graph_table);

  // output
  if (exist_flag)
    std::cout << "Yes" << std::endl;
  else
    std::cout << "No" << std::endl;
  return 0;
}
