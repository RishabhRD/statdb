#pragma once

#include "page/page.hpp"
#include "page/page_id.hpp"
#include <stdexec/exec/task.hpp>
#include <stdexec/stdexec/execution.hpp>
namespace statdb {
template <typename T>
concept PageStorage = requires(T &storage, page_id id, page &buffer) {
  // Postcondition:
  //   - If page exists in storage, store it in buffer and return true
  //     otherwise false
  // TODO: fix when stdexec fixes the sender_of concept
  { storage.fetch_page(id, buffer) } -> std::same_as<exec::task<bool>>;
};
}
