#include "buffer_pool.hpp"
#include "cache/lru_cache.hpp"
#include "page/page_id.hpp"
#include <iostream>
#include <stdexec/stdexec/execution.hpp>

int main() {
  statdb::buffer_pool<statdb::lru_cache> pool(32);
  auto x = stdexec::sync_wait(pool.acquire(statdb::page_id{"sample_file", 2}));
  if (x.has_value()) {
    auto [page_ptr] = *x;
    std::cout << page_ptr << ' ' << (page_ptr == nullptr) << std::endl;
  }
}
