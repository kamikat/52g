#include <iostream>
#include <bloom_filter.h>

using namespace app;

int main () {
  bloom_filter bf;
  bf.add({ "123", 3 });
  bf.add({ "foo", 3 });
  bf.add({ "bar", 3 });
  std::cout << bf.lookup({ "bar", 3 }) << std::endl;
  std::cout << bf.lookup({ "baz", 3 }) << std::endl;
  return 0;
}
