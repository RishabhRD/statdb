#pragma once

namespace statdb {
struct page_id {
  friend bool operator==(page_id const &, page_id const &) = default;
};
} // namespace statdb
