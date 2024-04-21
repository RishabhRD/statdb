#pragma once

#include <cstddef>
#include <span>
namespace statdb {
constexpr static std::size_t page_size = 1024 * 4; // 4 KB

using page_t = std::span<std::byte, page_size>;
} // namespace statdb
