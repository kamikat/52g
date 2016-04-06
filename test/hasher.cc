#include <iostream>
#include <iomanip>
#include <bf.h>

using namespace bf;

void test(const hasher& hash, const object& obj) {
  for (auto digest : hash(obj)) {
    std::cout << std::setw(16) << std::setfill('0') << std::hex << digest << ' ';
  }
  std::cout << std::endl;
}

int main () {
  hasher hash = make_hasher(2, 1);
  test(hash, { "123", 3 });
  test(hash, { "foo", 3 });
  test(hash, { "bar", 3 });
  return 0;
}
