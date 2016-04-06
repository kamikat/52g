#include <iostream>
#include <iomanip>
#include <bf.h>
#include <random>

using namespace bf;

static const size_t BF_K = 13;
static const size_t BF_M = 7094266647;

void debug(uint64_t digest) {
  std::cout << std::setw(16) << std::setfill('0') << std::hex << digest << ' ';
}

void test(const hasher& hash, const object& obj) {
  for (auto d : hash(obj)) {
    debug(d);
  }
  std::cout << std::endl;
}

int main () {
  // http://hur.st/bloomfilter?n=370069037&p=0.0001
  basic_bloom_filter bf(make_hasher(BF_K), BF_M);
  hasher hash = make_hasher(2, 1);
  test(hash, { "123", 3 });
  test(hash, { "foo", 3 });
  test(hash, { "bar", 3 });
  return 0;
}
