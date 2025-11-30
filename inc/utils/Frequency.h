#pragma once

#include <chrono>
#include <cmath>
#include <cstdint>

namespace Utils {
  struct Frequency {
    uint32_t freq;

    constexpr Frequency(uint32_t f) : freq(f) {}
    constexpr operator uint32_t() const { return freq; }
    constexpr operator std::chrono::milliseconds() const { 
      const long long period = std::round(1000.f/static_cast<double>(freq));
      return std::chrono::milliseconds(period); 
    }
  };

  namespace literals {
    constexpr auto operator""_Hz(unsigned long long val) -> Frequency { return Frequency{ static_cast<uint32_t>(val) }; }
    constexpr auto operator""_kHz(unsigned long long val) -> Frequency { return Frequency{ static_cast<uint32_t>(val * 1e3) }; }
    constexpr auto operator""_MHz(unsigned long long val) -> Frequency { return Frequency{ static_cast<uint32_t>(val * 1e6) }; }
  }  // namespace literals
}  // namespace Utils
