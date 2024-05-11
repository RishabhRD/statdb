#include "buffer_pool.hpp"
#include "cache/lru_cache.hpp"
#include "incremental_page_generator.hpp"
#include "storage/function_page_storage.hpp"
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

TEST_CASE("loads new page from storage if page doesn't exist in cache") {
  auto page_storage =
      statdb::function_page_storage{statdb::incremental_page_generator{}};
  using storage_type = std::decay_t<decltype(page_storage)>;

  statdb::buffer_pool<statdb::lru_cache, storage_type> pool(1, page_storage);

  auto [page_ptr1] =
      stdexec::sync_wait(pool.acquire(statdb::page_id{})).value();
  REQUIRE(page_ptr1 != nullptr);
  REQUIRE((*page_ptr1)[0] == std::byte{1});
}

TEST_CASE("Can return pinned page from cache if exists") {
  auto page_storage =
      statdb::function_page_storage{statdb::incremental_page_generator{}};
  using storage_type = std::decay_t<decltype(page_storage)>;

  statdb::buffer_pool<statdb::lru_cache, storage_type> pool(1, page_storage);

  auto [page_ptr1] =
      stdexec::sync_wait(pool.acquire(statdb::page_id{})).value();
  REQUIRE(page_ptr1 != nullptr);
  REQUIRE((*page_ptr1)[0] == std::byte{1});
  auto [page_ptr2] =
      stdexec::sync_wait(pool.acquire(statdb::page_id{})).value();
  REQUIRE(page_ptr2 != nullptr);
  REQUIRE((*page_ptr1)[0] == std::byte{1});
}

TEST_CASE("Can return unpinned page from cache if exists") {
  auto page_storage =
      statdb::function_page_storage{statdb::incremental_page_generator{}};
  using storage_type = std::decay_t<decltype(page_storage)>;

  statdb::buffer_pool<statdb::lru_cache, storage_type> pool(1, page_storage);

  auto [page_ptr1] =
      stdexec::sync_wait(pool.acquire(statdb::page_id{})).value();
  REQUIRE(page_ptr1 != nullptr);
  REQUIRE((*page_ptr1)[0] == std::byte{1});
  pool.release(statdb::page_id{});
  auto [page_ptr2] =
      stdexec::sync_wait(pool.acquire(statdb::page_id{})).value();
  REQUIRE(page_ptr2 != nullptr);
  REQUIRE((*page_ptr1)[0] == std::byte{1});
}

TEST_CASE("can't load new page in cache if all pages are pinned") {
  auto page_storage =
      statdb::function_page_storage{statdb::incremental_page_generator{}};
  using storage_type = std::decay_t<decltype(page_storage)>;

  statdb::buffer_pool<statdb::lru_cache, storage_type> pool(1, page_storage);

  stdexec::sync_wait(pool.acquire(statdb::page_id{})).value();
  auto [page_ptr2] =
      stdexec::sync_wait(pool.acquire(statdb::page_id{"other_page"})).value();
  REQUIRE(page_ptr2 == nullptr);
}

TEST_CASE("can acquire a new page in cache if no pages are pinned") {
  auto page_storage =
      statdb::function_page_storage{statdb::incremental_page_generator{}};
  using storage_type = std::decay_t<decltype(page_storage)>;

  statdb::buffer_pool<statdb::lru_cache, storage_type> pool(1, page_storage);

  stdexec::sync_wait(pool.acquire(statdb::page_id{})).value();
  pool.release(statdb::page_id{});
  auto [page_ptr2] =
      stdexec::sync_wait(pool.acquire(statdb::page_id{"other_page"})).value();
  REQUIRE(page_ptr2 != nullptr);
  REQUIRE((*page_ptr2)[0] == std::byte{2});
}
