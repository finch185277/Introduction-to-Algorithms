#include <algorithm>
#include <array>
#include <cstring>
#include <iostream>
#include <set>
#include <stack>
#include <utility>
#include <vector>

struct edge {
  int u, v;
  long long w;
};

bool cmp_edge(const edge &_l, const edge &_r) { return (_l.w < _r.w); }

std::vector<edge> get_edge(const int _m) {
  std::vector<edge> _rt;
  for (int i = 0; i < _m; i++) {
    edge _e;
    std::cin >> _e.u >> _e.v >> _e.w;
    _e.u--; // 0-base
    _e.v--;
    _rt.push_back(_e);
  }
  return _rt;
}

int find_parent(const int _t, std::vector<int> &_p) {
  if (_p.at(_t) == _t)
    return _t;
  return _p.at(_t) = find_parent(_p.at(_t), _p);
}

void union_node(const int _u, const int _v, std::vector<int> &_p) {
  _p.at(find_parent(_u, _p)) = find_parent(_v, _p);
}

void mst(std::vector<int> &_p, std::vector<long long> &_mel,
         const std::vector<edge> &_g) {
  for (edge _e : _g) {
    if (find_parent(_e.u, _p) != find_parent(_e.v, _p)) {
      union_node(_e.u, _e.v, _p);
      _mel.push_back(_e.w);
    }
  }
}

int main() {
  int n, m, k; // node, edge, k-th
  std::cin >> n >> m >> k;
  std::vector<edge> graph(get_edge(m));
  std::vector<int> parent(n);
  std::vector<long long> min_edge_list;
  for (int i = 0; i < n; i++) { // init
    parent.at(i) = i;
  }
  std::sort(graph.begin(), graph.end(), cmp_edge);
  mst(parent, min_edge_list, graph);
  std::cout << min_edge_list.at(k - 1) << std::endl;
  return 0;
}
