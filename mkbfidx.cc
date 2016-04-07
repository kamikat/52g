#include <iostream>

#define private public
#include <bf/bitvector.h>
#undef private

#include <bloom_filter.h>

using namespace app;

void dump(bloom_filter& bf) {
  auto& storage = bf.storage();
  char* data = (char*) storage.bits_.data();
  size_t size = sizeof(bf::bitvector::block_type) * storage.blocks();
  std::cout.write(data, size).flush();
}

int main () {
  bloom_filter bf;

  bf.add({ "123", 3 });
  bf.add({ "foo", 3 });
  bf.add({ "bar", 3 });

  dump(bf);
  return 0;
}
