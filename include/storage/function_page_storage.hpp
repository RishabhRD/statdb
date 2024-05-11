#pragma once

#include "page/page.hpp"
#include "page/page_id.hpp"
#include <stdexec/exec/task.hpp>
#include <stdexec/stdexec/execution.hpp>

namespace statdb {
template <typename ComputePage> class function_page_storage {
  ComputePage compute_page_;

public:
  constexpr function_page_storage(ComputePage compute_page)
      : compute_page_(std::move(compute_page)) {}

  auto fetch_page(page_id const &id, page &page) const -> exec::task<bool> {
    // TODO: fix when stdexec fixes sender_of concept
    co_return compute_page_(id, page);
  }
};

template <typename ComputePage>
function_page_storage(ComputePage) -> function_page_storage<ComputePage>;
} // namespace statdb
