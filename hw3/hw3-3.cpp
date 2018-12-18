#include <algorithm>
#include <array>
#include <cstring>
#include <iostream>
#include <set>
#include <stack>
#include <utility>
#include <vector>

std::vector<std::vector<std::pair<int, long long>>> get_edge(const int _n,
                                                             const int _m) {
  std::vector<std::vector<std::pair<int, long long>>> _rt(_n);
  for (int i = 0; i < _m; i++) {
    int u; // u = source
    std::cin >> u;
    std::pair<int, long long> p; // p = <dest, weight>
    std::cin >> p.first >> p.second;
    p.first--; // 0-base
    _rt.at(u - 1).push_back(p);
  }
  return _rt;
}

void relax(const int _u, const int _v, const long long _w,
           std::vector<int> &_predecessor, std::vector<long long> &_distance) {
  if (_distance.at(_u) + _w > _distance.at(_v)) {
    _distance.at(_v) = _distance.at(_u) + _w;
    _predecessor.at(_v) = _u;
  }
}

bool bellman_ford(
    const int _n, const int _m, std::vector<int> &_predecessor,
    std::vector<long long> &_distance,
    const std::vector<std::vector<std::pair<int, long long>>> &_graph) {
  for (int i = 0; i < _n - 1; i++) {
    for (int j = 0; j < _n; j++) {
      for (std::pair<int, long long> _p : _graph.at(j)) {
        relax(j, _p.first, _p.second, _predecessor, _distance);
      }
    }
  }

  // check positive cycle
  for (int i = 0; i < _n; i++) {
    for (std::pair<int, long long> _p : _graph.at(i)) {
      if (_distance.at(i) + _p.second > _distance.at(_p.first))
        return false;
    }
  }
  return true;
}

long long find_max_path(const std::vector<long long> &_distance) {
  long long _rt = 0;
  for (long long _d : _distance) {
    _rt = std::max(_rt, _d);
  }
  return _rt;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  std::vector<int> predecessor(n, -1);
  std::vector<long long> distance(n, 0);
  std::vector<std::vector<std::pair<int, long long>>> graph(get_edge(n, m));

  if (!bellman_ford(n, m, predecessor, distance, graph))
    std::cout << "INF" << std::endl;
  else
    std::cout << find_max_path(distance) << std::endl;

  return 0;
}
