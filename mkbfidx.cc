#include <iostream>

#define private public
#include <bf/bitvector.h>
#undef private

#include <bloom_filter.h>

using namespace app;
using namespace std;

void dump(bloom_filter& bf) {
  auto& storage = bf.storage();
  char* data = (char*) storage.bits_.data();
  size_t size = sizeof(bf::bitvector::block_type) * storage.blocks();
  cout.write(data, size).flush();
}

int main () {
  bloom_filter bf;
  string line;
  while (getline(cin, line)) {
    bf.add(line);
  }
  dump(bf);
  return 0;
}
