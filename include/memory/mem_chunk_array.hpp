#pragma once

#include <array>
#include <cstddef>
#include <vector>

namespace statdb {
template <std::size_t chunk_size>
  requires(chunk_size > 0)
class mem_chunk_array {
  using data_t = std::vector<std::array<std::byte, chunk_size>>;
  data_t data_;

public:
  using value_type = typename data_t::value_type;
  using size_type = typename data_t::size_type;
  using difference_type = typename data_t::difference_type;
  using reference = typename data_t::reference;
  using const_reference = typename data_t::const_reference;
  using pointer = typename data_t::pointer;
  using const_pointer = typename data_t::const_pointer;
  using iterator = typename data_t::iterator;
  using const_iterator = typename data_t::const_iterator;
  using reverse_iterator = typename data_t::reverse_iterator;
  using const_reverse_iterator = typename data_t::const_reverse_iterator;

  // Precondition:
  //   - size > 0
  mem_chunk_array(std::size_t size) : data_(size) {}

  // Precondition:
  //   - i < size
  auto operator[](std::size_t i) const noexcept -> const_reference {
    return data_[i];
  }

  // Precondition:
  //   - i < size
  auto operator[](std::size_t i) noexcept -> reference { return data_[i]; }

  auto begin() noexcept { return std::begin(data_); }
  auto begin() const noexcept { return std::begin(data_); }
  auto cbegin() const noexcept { return std::begin(data_); }

  auto end() noexcept { return std::end(data_); }
  auto end() const noexcept { return std::end(data_); }
  auto cend() const noexcept { return std::end(data_); }

  auto rbegin() noexcept { return std::rbegin(data_); }
  auto rbegin() const noexcept { return std::rbegin(data_); }
  auto crbegin() const noexcept { return std::crbegin(data_); }

  auto rend() noexcept { return std::rend(data_); }
  auto rend() const noexcept { return std::rend(data_); }
  auto crend() const noexcept { return std::crend(data_); }

  ~mem_chunk_array() noexcept { delete[] data_; }
};
} // namespace statdb
