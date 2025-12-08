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

#define println(...) ::mio::mprintln::builtin(__VA_ARGS__)

#endif // MIO_H
