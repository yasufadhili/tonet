// to be used to provide branching hints to the compiler

#pragma once

#include <iostream>
#include <cstring>

#define LIKELY(x) __builtin_expect(!!(x), 1)
#define UNLIKELY(x) __builtin_expect(!!(x), 0)


inline auto ASSERT(bool cond, const std::string& msg) noexcept{
  if (UNLIKELY(!cond))
  {
    std::cerr << msg << std::endl;
    exit(EXIT_FAILURE);
  }
}

inline auto FATAL(const std::string& msg) noexcept{
  std::cerr << msg <<std::endl;
  exit(EXIT_FAILURE);
}


