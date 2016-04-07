#include <iostream>
#include <bloom_filter.h>
#include <debug.h>
#include <util.h>

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
    fold_str(line, bf::default_hash_function::max_obj_size);
    bf.add(line);
    DEBUG("ADD '" << line << "'");
  }
  dump(bf);
  return 0;
}
