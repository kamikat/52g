#include <iostream>
#include <bloom_filter.h>
#include <util.h>
#include <debug.h>

using namespace app;
using namespace std;

void load(bloom_filter& bf) {
  // TODO load bloom filter index from file
}

int main () {
  bloom_filter bf;
  load(bf);
  string line;
  while (getline(cin, line)) {
    fold_str(line, bf::default_hash_function::max_obj_size);
    cout << bf.lookup(line) << endl;
  }
  return 0;
}
