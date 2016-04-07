#include <bloom_filter.h>

namespace app {

  bloom_filter::bloom_filter(size_t k, size_t m)
  : bf::basic_bloom_filter(bf::make_hasher(k), m), k_(k), m_(m)
  {
  }

  bloom_filter::bloom_filter(bloom_filter&& o)
  : basic_bloom_filter(std::move(o)), k_(o.k_), m_(o.m_)
  {
  }

  size_t bloom_filter::lookupDigest(const std::vector<bf::digest>& digests)
  {
    auto bits = storage();
    for (auto d : digests) {
      if (!bits[d % bits.size()]) return 0;
    }
    return 1;
  }

}
