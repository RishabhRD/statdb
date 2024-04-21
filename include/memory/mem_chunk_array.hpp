#pragma once

#include <algorithm>
#include <cstddef>
#include <span>

namespace statdb {
template <std::size_t chunk_size>
  requires(chunk_size > 0)
class mem_chunk_array {
  std::byte *data_;
  std::size_t size_;

public:
  // Precondition:
  //   - size > 0
  mem_chunk_array(std::size_t size)
      : data_(new std::byte[size * chunk_size]), size_(size) {}

  mem_chunk_array(mem_chunk_array const &other)
      : data_(new std::byte[other.size_ * chunk_size]), size_(other.size_) {
    std::copy(other.data_, other.data_ + (size_ * chunk_size), data_);
  }

  mem_chunk_array(mem_chunk_array &&other) noexcept
      : data_(other.data_), size_(other.size_) {
    other.data_ = nullptr;
  }

  auto operator=(mem_chunk_array other) -> mem_chunk_array & {
    swap(*this, other);
    return *this;
  }

  friend void swap(mem_chunk_array &first, mem_chunk_array &second) noexcept {
    using std::swap;
    swap(first.data_, second.data_);
  }

  // Precondition:
  //   - i < size
  auto operator[](std::size_t i) const noexcept {
    return std::span<std::byte const, chunk_size>{data_ + (i * chunk_size),
                                                  chunk_size};
  }

  // Precondition:
  //   - i < size
  auto operator[](std::size_t i) noexcept {
    return std::span<std::byte, chunk_size>{data_ + (i * chunk_size),
                                            chunk_size};
  }

  ~mem_chunk_array() noexcept { delete[] data_; }
};
} // namespace statdb
