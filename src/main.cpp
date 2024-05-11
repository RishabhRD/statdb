#include "buffer_pool.hpp"
#include "cache/lru_cache.hpp"
#include "page/page_id.hpp"
#include "storage/never_page_storage.hpp"
#include <iostream>
#include <stdexec/stdexec/execution.hpp>
#include <type_traits>

int main() {
  using storage_type = std::decay_t<decltype(statdb::never_page_storage)>;
  statdb::buffer_pool<statdb::lru_cache, storage_type> pool(
      32, statdb::never_page_storage);
  auto x = stdexec::sync_wait(pool.acquire(statdb::page_id{"sample_file", 2}));
  if (x.has_value()) {
    auto [page_ptr] = *x;
    std::cout << page_ptr << ' ' << (page_ptr == nullptr) << std::endl;
  }
}
