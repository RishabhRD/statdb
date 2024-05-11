#pragma once

#include "storage/function_page_storage.hpp"

namespace statdb {
constexpr auto never_page_storage =
    function_page_storage([](page_id const &, page &) { return false; });
}
