#pragma once

#include <cstdint>

namespace Utils {
  struct Percentage {
    double value;

    constexpr Percentage(double percentage) : value(percentage) {}
    constexpr operator double() const { return value; }
  };

  namespace literals {
    constexpr auto operator""_percent(unsigned long long val) -> Percentage { return Percentage{ static_cast<double>(val) / 100.f }; }
  }  // namespace literals
}  // namespace Utils
