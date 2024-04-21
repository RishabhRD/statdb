#pragma once

#include <array>
#include <cstddef>

namespace statdb {
constexpr static std::size_t page_size = 1024 * 4; // 4 KB

using page_t = std::array<std::byte, page_size>;
} // namespace statdb
