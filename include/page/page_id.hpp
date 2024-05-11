#pragma once

#include <string>
namespace statdb {
struct page_id {
  std::string file_path;
  std::size_t offset;

  friend bool operator==(page_id const &, page_id const &) = default;
};
} // namespace statdb
