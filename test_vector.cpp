#include <iostream>
#include <assert.h>

#include "vector.h"

int main() {
  // test push_back and random access
  xiar::vector<int> v1;
  for (int i = 0; i < 20; ++i) {
    v1.push_back(i);

    assert(v1.size() == i+1);
    assert(v1.capacity() >= v1.size());
  }

  for (int i = 0; i < v1.size(); ++i) assert(v1[i] == i);

  // test copy constructor
  xiar::vector<int> v2(v1);
  assert(v2.size() == v1.size());
  for (int i = 0; i < v2.size(); ++i) assert(v1[i] == v2[i]);

  // make sure it is a copy and not a reference
  for (int i = 0; i < v2.size(); ++i) {
    v2[i] += 10;
    assert(v1[i] != v2[i]);
  }

  // test pop_back
  for (int i = v2.size(); i > 0; --i) {
    v2.pop_back();
    assert(v2.size() == i-1);
  }

  // test iteration
  int i = 0;
  for (xiar::vector<int>::iterator it = v1.begin(); it != v1.end(); ++it) {
    assert(*it == i++);
    *it += v1.size();
  }

  for (int n : v1) {
    assert(n == i++);
  }

  return 0;
}