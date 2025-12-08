#pragma once
#include <cstdio>
#include <ostream>
#include <string_view>
#include <utility>

#ifndef MIO_H
#define MIO_H

#define println(...) ::mio::mprintln::builtin(__VA_ARGS__)

namespace mio::mprintln {
template <typename... T> int writer(const char *c, T &&...args) {
  if constexpr (sizeof...(T) != 0) {
    const int w = std::printf(c, std::forward<T>(args)...);
    std::putchar('\n');
    return w + 1;
  }

  return std::fputs(c, stdout) + std::putchar('\n');
}

template <typename... T> int builtin(const char *fmt, T &&...args) {
  return writer(fmt, std::forward<T>(args)...) + 1;
}
template <typename T> inline int builtin(const T &fmt) {
  writer(std::data(fmt)) + 1;
  return static_cast<int>(std::size(fmt)) + 1;
}

} // namespace mio::mprintln
#endif // MIO_H
