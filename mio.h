#pragma once
#include <cstddef>
#include <cstdio>
#include <ostream>
#include <string_view>
#include <utility>

#ifndef MIO_H
#define MIO_H

namespace mio::mprintln {
template <typename... T> int writer(std::string_view bw, T &&...args) {
  const char *c = bw.data();

  if constexpr (sizeof...(T) != 0) {
    const int w = std::printf(c, std::forward<T>(args)...);
    if (w < 0) {
      return -1;
    }
    std::putchar('\n');
    return w + 1;
  }

  return std::fputs(c, stdout) + std::putchar('\n');
}

template <typename... T> int builtin(std::string_view fmt, T &&...args) {
  return writer(fmt, std::forward<T>(args)...) + 1;
}

template <typename... T> int builtin(const char *fmt, T &&...args) {
  return writer(fmt, std::forward<T>(args)...) + 1;
}
template <typename T> int builtin(const T &fmt) {
  return writer(std::data(fmt)) + 1;
}

} // namespace mio::mprintln

template <typename F> class Defer {
  F f;
  bool active = true;

public:
  template <typename T> Defer(T &&f_) : f(std::forward<T>(f_)), active(true) {}

  Defer(const Defer &) = delete;

  Defer(Defer &&o) : f(std::move(o.f)), active(o.active) { o.active = false; }

  ~Defer() {
    if (active)
      f();
  }

  Defer &operator=(const Defer &) = delete;
};

inline constexpr struct {
  template <typename F> Defer<F> operator<<(F &&f) const {
    return Defer<std::decay_t<F>>(std::forward<F>(f));
  }
} deferrer;

#define println(...) ::mio::mprintln::builtin(__VA_ARGS__)
#define TOKENPASTE(x, y) x##y
#define TOKENPASTE2(x, y) TOKENPASTE(x, y)
#define defer auto TOKENPASTE2(_defer_, __LINE__) = deferrer << [&]() noexcept

#endif // MIO_H
