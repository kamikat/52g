#include <iostream>
#include <docopt.h>
#include <bloom_filter.h>
#include <debug.h>
#include <util.h>

const char USAGE[] =
R"(
  Make bloom filter index.

  Usage:
    mkbfidx <k> <m> [--seed <x>]
    mkbfidx <k> <m> [--seed <x>] > stdin.idx
    mkbfidx <k> <m> [--seed <x>] < data.txt > data.idx
    mkbfidx <k> <m> [--seed <x>] < data.txt | gzip > data.idx.gz

  Options:
    k               number of hash functions
    m               number of bits
    -s, --seed <x>  hash function seed [default: 1]
    -h, --help      print help message
)";

using namespace app;
using namespace std;

void dump(bloom_filter& bf, ostream& out) {
  Header header = { bf.k_, bf.m_, bf.seed_ };
  out.write((char*) &header, sizeof(header));
  auto& storage = bf.storage();
  char* data = (char*) storage.bits_.data();
  size_t size = sizeof(bf::bitvector::block_type) * storage.blocks();
  out.write(data, size).flush();
}

int main(int argc, const char* argv[]) {
  auto args = docopt::docopt(USAGE, { argv + 1, argv + argc });
  bloom_filter bf { size_t(args["<k>"].asLong()), size_t(args["<m>"].asLong()), size_t(args["--seed"].asLong()) };
  string line;
  while (getline(cin, line)) {
    fold_str(line, bf::default_hash_function::max_obj_size);
    bf.add(line);
    DEBUG("ADD '" << line << "'");
  }
  dump(bf, cout);
  return 0;
}
