#include <iostream>

#define private public
#include <bf/bitvector.h>
#undef private

#include <bloom_filter.h>

#ifndef NDEBUG
#include <iomanip>
#define DEBUG(expr) cerr << "DEBUG " << expr << endl
#define HEX(x) setw(2) << setfill('0') << hex << (int)(x) << setw(0) << dec
#else
#define DEBUG(expr)
#endif

using namespace app;
using namespace std;

void dump(bloom_filter& bf) {
  auto& storage = bf.storage();
  char* data = (char*) storage.bits_.data();
  size_t size = sizeof(bf::bitvector::block_type) * storage.blocks();
  cout.write(data, size).flush();
}

const size_t MAX_OBJECT_SIZE = 36;

void fold_line(string& line) {
  // fold long string...
  for (int i = MAX_OBJECT_SIZE; i < line.length(); i += MAX_OBJECT_SIZE) {
    for (int j = 0; j < MAX_OBJECT_SIZE && i + j < line.length(); j++) {
      DEBUG("FOLD line[" << j << "]=" << HEX(line[j]) << ", line[" << i + j << "]=" << HEX(line[i + j]));
      line[j] ^= line[i + j];
      DEBUG("FOLD line[" << j << "] XOR line[" << i + j << "]=" << HEX(line[j]));
    }
  }
  if (line.length() > MAX_OBJECT_SIZE) line.resize(MAX_OBJECT_SIZE);
}

int main () {
  bloom_filter bf;
  string line;
  while (getline(cin, line)) {
    fold_line(line);
    bf.add(line);
    DEBUG("ADD '" << line << "'");
  }
  dump(bf);
  return 0;
}
