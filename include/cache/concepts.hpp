#pragma once

#include <concepts>
namespace statdb {
// Constructor should construct the cache of size k.
template <typename CacheType>
concept cache =
    std::constructible_from<CacheType, std::size_t> &&
    requires(CacheType cache, CacheType const &constCache, std::size_t e) {
      // Precondition: e belongs to [0, k)
      { cache.add(e) } -> std::same_as<void>;
      // Precondition: e belongs to [0, k)
      { cache.remove(e) } -> std::same_as<void>;
      { constCache.size() } -> std::same_as<std::size_t>;
      // Precondition: cache.size() > 0
      { cache.evict() } -> std::same_as<std::size_t>;
      { cache.contains(e) } -> std::same_as<bool>;
    };
} // namespace statdb
