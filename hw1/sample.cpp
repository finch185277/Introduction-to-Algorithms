#include "OJ.h"

#include <bits/stdc++.h>
using namespace std;

void naive(vector<Point> &points) {
  int n = (int)points.size() / 2;
  do {
    oj.set_match(points);
    display();
  } while (update(n, points));
}

void DC(vector<Point> &points) {
  // boundary case (naive)...

  vector<Point> sub1, sub2;
  partition(points, sub1, sub2);
  oj.set_match(sub1);
  oj.set_match(sub2);
  display();

  // D&C ...
}
