#include "buffer_pool.hpp"
#include "cache/lru_cache.hpp"
#include "storage/never_page_storage.hpp"
#include <doctest/doctest.h>
#include <type_traits>

TEST_CASE("should return null page for non-existing page") {
  using storage_type = std::decay_t<decltype(statdb::never_page_storage)>;
  statdb::buffer_pool<statdb::lru_cache, storage_type> pool(
      2, statdb::never_page_storage);

  auto [page_ptr] = stdexec::sync_wait(pool.acquire(statdb::page_id{})).value();
  REQUIRE(page_ptr == nullptr);
}
