#ifndef BLOOM_FILTER_H
#define BLOOM_FILTER_H

#define private public
#include <bf/bitvector.h>
#undef private

#include <bf.h>

namespace app {

class bloom_filter: public bf::basic_bloom_filter {

public:

  // http://hur.st/bloomfilter?n=370069037&p=0.0001
  static const size_t BF_K = 13;
  static const size_t BF_M = 7094266647;

  bloom_filter();

  bloom_filter(bloom_filter&&);

  size_t lookupDigest(const std::vector<bf::digest>& digests);

};

}

#endif
