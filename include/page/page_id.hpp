#pragma once

#include <string>
namespace statdb {
struct page_id {
  std::string file_path;
  std::size_t offset;

  page_id(std::string file_path_ = {}, std::size_t offset_ = {})
      : file_path(std::move(file_path_)), offset(offset_) {}

  friend bool operator==(page_id const &, page_id const &) = default;
};
} // namespace statdb
