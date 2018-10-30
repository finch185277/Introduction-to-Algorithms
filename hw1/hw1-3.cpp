#include "OJ.h"
#include "Point.h"

#include <bits/stdc++.h>
using namespace std;

bool update(int n, vector<Point> &points) {
  bool result = false;
  if (n <= 1)
    return result;
  Line L1 = {points[0], points[2] - points[0]};
  Line L2 = {points[1], points[3] - points[1]};
  if (intersection(L1, L2)) {
    result = true;
    swap(points[0], points[1]);
  }
  return result;
}

void naive(vector<Point> &points) {
  int n = (int)points.size() / 2;
  if (n == 1) {
    oj.set_match(points);
    return;
  }
  do {
    oj.set_match(points);
    display();
  } while (update(n, points));
}

void partition(vector<Point> &points, vector<Point> &sub1,
               vector<Point> &sub2) {
  int n = (int)points.size() / 2;
  int founded = 0;
  int rat_index, hole_index;
  int rats_count, holes_count;
  Point base, base1, base2;
  for (rat_index = 0; rat_index < n; rat_index++) {
    for (hole_index = 0; hole_index < n; hole_index++) {
      base = points[hole_index + n] - points[rat_index];
      rats_count = 0, holes_count = 0;
      for (int p = 0; p < n; p++) {
        if (p != rat_index && (points[p] - points[rat_index]) % base < 0)
          rats_count++;
        if (p != hole_index && (points[p + n] - points[rat_index]) % base < 0)
          holes_count++;
      }
      if (rats_count == holes_count) {
        base1 = points[rat_index];
        base2 = points[hole_index + n];
        founded = 1;
        break;
      }
    }
    if (founded)
      break;
  }
  sub1.clear();
  sub2.clear();
  for (int p = 0; p < n; p++) {
    if (p == rat_index)
      continue;
    if ((points[p] - points[rat_index]) % base < 0)
      sub1.push_back(points[p]);
    else
      sub2.push_back(points[p]);
  }
  for (int p = 0; p < n; p++) {
    if (p == hole_index)
      continue;
    if ((points[p + n] - points[rat_index]) % base < 0)
      sub1.push_back(points[p + n]);
    else
      sub2.push_back(points[p + n]);
  }
  points.clear();
  points.push_back(base1);
  points.push_back(base2);
}

void DC(vector<Point> &points) {
  if (points.size() <= 4) { // boundary case (naive)...
    naive(points);
    return;
  } else { // D&C ...
    vector<Point> sub1, sub2;
    partition(points, sub1, sub2);
    oj.set_match(sub1);
    oj.set_match(sub2);
    display();
    DC(points);
    DC(sub1);
    DC(sub2);
  }
}
