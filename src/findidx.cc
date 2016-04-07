#include <iostream>
#include <docopt.h>
#include <bloom_filter.h>
#include <util.h>
#include <debug.h>

const char USAGE[] =
R"(Make bloom-filter index from input dataset.

  Usage: mkbfidx [-i <input>] [-o <output>]

  Options:
    -i <file>, --input=<file>   set input file, stdin is used by default
    -o <file>, --output=<file>  set output file, stdout is used by defailt
    -h, --help                  print help message

)";

using namespace app;
using namespace std;

void load(bloom_filter& bf) {
  // TODO load bloom filter index from file
}

int main (int argc, const char* argv[]) {
  auto args = docopt::docopt(USAGE, { argv + 1, argv + argc });
  cout << args["--input"] << "=>" << args["--output"] << endl;
  // bloom_filter bf;
  // load(bf);
  string line;
  while (getline(cin, line)) {
    fold_str(line, bf::default_hash_function::max_obj_size);
    cout << line << endl;
  }
  return 0;
}
