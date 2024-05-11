#pragma once

#include <iterator>
#include <list>
#include <vector>

namespace statdb {
class lru_cache {
  using list_type = std::list<std::size_t>;
  using value_type = std::size_t;

  list_type cached_elements;
  std::vector<typename list_type::iterator> element_pointers;

public:
  // Class Invariants:
  //   - There would unique elements in cached_elements
  //   - element_pointers[i] would contain iterator to i in elements
  //   - if i is not in cached_elements, element_pointers[i] =
  //     end(cached_elements)

  lru_cache(std::size_t cache_size)
      : element_pointers(cache_size, std::end(cached_elements)) {}

  // Precondition:
  //   - e would range from [0, cache_size)
  // Postcondition:
  //   - Add element e to the cache
  auto add(value_type e) -> void {
    if (element_pointers[e] != std::end(cached_elements)) {
      cached_elements.erase(element_pointers[e]);
    }
    cached_elements.push_back(std::move(e));
    element_pointers[e] = std::prev(cached_elements.end());
  }

  // Precondition:
  //   - e would range from [0, cache_size)
  //   - e exists in cached_elements
  // Postcondition:
  //   - Remove element e from cache
  auto remove(value_type e) -> void {
    cached_elements.erase(element_pointers[e]);
    element_pointers[e] = std::end(cached_elements);
  }

  // Postcondition:
  //   - Return number of elements in cache right now
  constexpr auto size() const noexcept -> std::size_t {
    return cached_elements.size();
  }

  // Precondition:
  //   - size() > 0
  // Postcondition:
  //   - Remove the least recently used element and remove it from cache
  auto evict() -> value_type {
    auto e = std::move(cached_elements.front());
    cached_elements.pop_front();
    element_pointers[e] = std::end(cached_elements);
    return e;
  }

  // Precondition:
  //   - size() > 0
  // Postcondition:
  //   - Return the least recently used element without removing it
  auto peek() const noexcept -> value_type { return cached_elements.front(); }

  // Precondition:
  //   - e would range from [0, cache_size)
  // Postcondition:
  //   - true if element exists in cache otherwise false
  auto contains(value_type const &e) const noexcept -> bool {
    return element_pointers[e] != std::end(cached_elements);
  }

  auto capacity() const noexcept { return element_pointers.size(); }
};
} // namespace statdb
