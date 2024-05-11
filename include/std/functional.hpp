#pragma once

#include <concepts>
#include <utility>

namespace statdb {
template <class Fun, class... Args>
concept Predicate = std::invocable<Fun, Args...> &&
                    std::same_as<std::invoke_result_t<Fun, Args...>, bool>;

template <typename T> constexpr auto equals(T val) {
  return [val_ = std::move(val)](T const &other) { return other == val_; };
}

template <typename T> constexpr auto not_equals(T val) {
  return [val_ = std::move(val)](T const &other) { return !(other == val_); };
}

#define lift(func)                                                             \
  [](auto &&...__args__) noexcept(                                             \
      noexcept(func(std::forward<decltype(__args__)>(__args__)...)))           \
      -> decltype(func(std::forward<decltype(__args__)>(__args__)...)) {       \
    return func(std::forward<decltype(__args__)>(__args__)...);                \
  }

#define lift_mem(func)                                                         \
  [this](auto &&...__args__) noexcept(                                         \
      noexcept(func(std::forward<decltype(__args__)>(__args__)...)))           \
      -> decltype(func(std::forward<decltype(__args__)>(__args__)...)) {       \
    return func(std::forward<decltype(__args__)>(__args__)...);                \
  }

} // namespace statdb
