#include <iostream>
#include <fstream>
#include <sstream>
#include <docopt.h>
#include <bloom_filter.h>
#include <util.h>
#include <debug.h>

const char USAGE[] =
R"(
  Command-line tool to query bloom filter index.

  Usage:
    openidx [-x] <file>

  Options:
    file        bloom filter index file
    -x, --hex   enable hexadecimal query mode [default: false]
    -h, --help  print help message
)";

using namespace app;
using namespace std;

bloom_filter load(const string& file) {
  DEBUG("LOAD " << file);
  ifstream ifs { file, ios::binary };
  Header header;
  ifs.read((char*) &header, sizeof(header));
  cout << "HEADER k=" << header.k << ", m=" << header.m << ", seed=" << header.seed << endl;
  bloom_filter bf(header.k, header.m);
  auto& storage = bf.storage();
  char* data = (char*) storage.bits_.data();
  size_t size = sizeof(bf::bitvector::block_type) * storage.blocks();
  ifs.read(data, size);
  return move(bf);
}

int main(int argc, const char* argv[]) {
  auto args = docopt::docopt(USAGE, { argv + 1, argv + argc });
  bloom_filter bf = load(args["<file>"].asString());
  string line;
  if (args["--hex"].asBool()) {
    // hexadecimal input
    while (getline(cin, line)) {
      istringstream iss { line };
      vector<bf::digest> digests { istream_iterator<bf::digest> { iss >> hex }, istream_iterator<bf::digest> {} };
      DEBUG("LOOKUP digest {");
      for (auto d : digests) {
        DEBUG("LOOKUP     " << HEX(d));
      }
      DEBUG("LOOKUP }");
      cout << bf.lookupDigest(digests) << endl;
    }
  } else {
    // plain input
    while (getline(cin, line)) {
      DEBUG("LOOKUP plain \"" << line << "\"");
      fold_str(line, bf::default_hash_function::max_obj_size);
      cout << bf.lookup(line) << endl;
    }
  }
  return 0;
}
