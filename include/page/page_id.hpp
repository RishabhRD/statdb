#pragma once

namespace statdb {
struct page_id_t {
  friend bool operator==(page_id_t const &, page_id_t const &) = default;
};
} // namespace statdb
