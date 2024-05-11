#pragma once

#include "page/page.hpp"
#include "page/page_id.hpp"
namespace statdb {
struct incremental_page_generator {
  unsigned char cur_val{};

  auto operator()(page_id const &, page &page) -> bool {
    page[0] = std::byte(cur_val++);
    return true;
  }
};
} // namespace statdb
