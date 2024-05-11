#pragma once

#include <concepts>
namespace statdb {
// Constructor should construct the cache of size k.
template <typename CacheType>
concept Cache =
    std::constructible_from<CacheType, std::size_t> &&
    requires(CacheType cache, CacheType const &constCache, std::size_t e) {
      // Precondition: e belongs to [0, k)
      // Postcondiiton: add e to cache
      { cache.add(e) } -> std::same_as<void>;
      // Precondition: e belongs to [0, k) and e is in cache
      // Postcondiiton: remove e from cache
      { cache.remove(e) } -> std::same_as<void>;
      // Postcondiiton: Returns number of elements in cache currently
      { constCache.size() } -> std::same_as<std::size_t>;
      // Precondition: cache.size() > 0
      // Postcondiiton: Removes an element from cache according to eviction
      // policy
      { cache.evict() } -> std::same_as<std::size_t>;
      // Precondition: e belongs to [0, k)
      // Postcondition: Returns true if e is in the cache
      { cache.contains(e) } -> std::same_as<bool>;
      // Postcondition: Maximum number of elements possible in cache
      { constCache.capacity() } -> std::same_as<std::size_t>;
      // Postcondition:
      //   - Returns the element which would be removed if evict()
      //     is called, without removing it.
      { constCache.peek() } -> std::same_as<std::size_t>;
    };
} // namespace statdb
