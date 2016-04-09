#include <bloom_filter.h>
#include <debug.h>

namespace app {

  bloom_filter::bloom_filter(size_t k, size_t m, size_t seed)
  : bf::basic_bloom_filter(bf::make_hasher(k), m), k_(k), m_(m), seed_(seed)
  {
  }

  bloom_filter::bloom_filter(bloom_filter&& o)
  : basic_bloom_filter(std::move(o)), k_(o.k_), m_(o.m_), seed_(o.seed_)
  {
    DEBUG("MOVE bloom filter");
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
