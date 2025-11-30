#pragma once

#include <span>

#include "utils/Frequency.h"

namespace Music {
  using Song = std::span<Utils::Frequency>;

  namespace Notes {
    using namespace Utils::literals;

    static constexpr auto R = 0_Hz;
    static constexpr auto B0 = 31_Hz;
    static constexpr auto C1 = 33_Hz;
    static constexpr auto CS1 = 35_Hz;
    static constexpr auto D1 = 37_Hz;
    static constexpr auto DS1 = 39_Hz;
    static constexpr auto E1 = 41_Hz;
    static constexpr auto F1 = 44_Hz;
    static constexpr auto FS1 = 46_Hz;
    static constexpr auto G1 = 49_Hz;
    static constexpr auto GS1 = 52_Hz;
    static constexpr auto A1 = 55_Hz;
    static constexpr auto AS1 = 58_Hz;
    static constexpr auto B1 = 62_Hz;
    static constexpr auto C2 = 65_Hz;
    static constexpr auto CS2 = 69_Hz;
    static constexpr auto D2 = 73_Hz;
    static constexpr auto DS2 = 78_Hz;
    static constexpr auto E2 = 82_Hz;
    static constexpr auto F2 = 87_Hz;
    static constexpr auto FS2 = 93_Hz;
    static constexpr auto G2 = 98_Hz;
    static constexpr auto GS2 = 104_Hz;
    static constexpr auto A2 = 110_Hz;
    static constexpr auto AS2 = 117_Hz;
    static constexpr auto B2 = 123_Hz;
    static constexpr auto C3 = 131_Hz;
    static constexpr auto CS3 = 139_Hz;
    static constexpr auto D3 = 147_Hz;
    static constexpr auto DS3 = 156_Hz;
    static constexpr auto E3 = 165_Hz;
    static constexpr auto F3 = 175_Hz;
    static constexpr auto FS3 = 185_Hz;
    static constexpr auto G3 = 196_Hz;
    static constexpr auto GS3 = 208_Hz;
    static constexpr auto A3 = 220_Hz;
    static constexpr auto AS3 = 233_Hz;
    static constexpr auto B3 = 247_Hz;
    static constexpr auto C4 = 262_Hz;
    static constexpr auto CS4 = 277_Hz;
    static constexpr auto D4 = 294_Hz;
    static constexpr auto DS4 = 311_Hz;
    static constexpr auto E4 = 330_Hz;
    static constexpr auto F4 = 349_Hz;
    static constexpr auto FS4 = 370_Hz;
    static constexpr auto G4 = 392_Hz;
    static constexpr auto GS4 = 415_Hz;
    static constexpr auto A4 = 440_Hz;
    static constexpr auto AS4 = 466_Hz;
    static constexpr auto B4 = 494_Hz;
    static constexpr auto C5 = 523_Hz;
    static constexpr auto CS5 = 554_Hz;
    static constexpr auto D5 = 587_Hz;
    static constexpr auto DS5 = 622_Hz;
    static constexpr auto E5 = 659_Hz;
    static constexpr auto F5 = 698_Hz;
    static constexpr auto FS5 = 740_Hz;
    static constexpr auto G5 = 784_Hz;
    static constexpr auto GS5 = 831_Hz;
    static constexpr auto A5 = 880_Hz;
    static constexpr auto AS5 = 932_Hz;
    static constexpr auto B5 = 988_Hz;
    static constexpr auto C6 = 1047_Hz;
    static constexpr auto CS6 = 1109_Hz;
    static constexpr auto D6 = 1175_Hz;
    static constexpr auto DS6 = 1245_Hz;
    static constexpr auto E6 = 1319_Hz;
    static constexpr auto F6 = 1397_Hz;
    static constexpr auto FS6 = 1480_Hz;
    static constexpr auto G6 = 1568_Hz;
    static constexpr auto GS6 = 1661_Hz;
    static constexpr auto A6 = 1760_Hz;
    static constexpr auto AS6 = 1865_Hz;
    static constexpr auto B6 = 1976_Hz;
    static constexpr auto C7 = 2093_Hz;
    static constexpr auto CS7 = 2217_Hz;
    static constexpr auto D7 = 2349_Hz;
    static constexpr auto DS7 = 2489_Hz;
    static constexpr auto E7 = 2637_Hz;
    static constexpr auto F7 = 2794_Hz;
    static constexpr auto FS7 = 2960_Hz;
    static constexpr auto G7 = 3136_Hz;
    static constexpr auto GS7 = 3322_Hz;
    static constexpr auto A7 = 3520_Hz;
    static constexpr auto AS7 = 3729_Hz;
    static constexpr auto B7 = 3951_Hz;
    static constexpr auto C8 = 4186_Hz;
    static constexpr auto CS8 = 4435_Hz;
    static constexpr auto D8 = 4699_Hz;
    static constexpr auto DS8 = 4978_Hz;
  }  // namespace Notes

  static constexpr auto MARIO_BROS_THEME = std::array{
    // Phase 1
    Notes::E7, Notes::E7, Notes::E7,
    Notes::E7, Notes::E7, Notes::E7,
    Notes::R, Notes::R, Notes::R,
    Notes::E7, Notes::E7, Notes::E7,

    Notes::R, Notes::R, Notes::R,
    Notes::C7, Notes::C7, Notes::C7,
    Notes::E7, Notes::E7, Notes::E7,
    Notes::R, Notes::R, Notes::R,

    Notes::G7, Notes::G7, Notes::G7,
    Notes::R, Notes::R, Notes::R,
    Notes::R, Notes::R, Notes::R,
    Notes::R, Notes::R, Notes::R,

    Notes::G6, Notes::G6, Notes::G6,
    Notes::R, Notes::R, Notes::R,
    Notes::R, Notes::R, Notes::R,
    Notes::R, Notes::R, Notes::R,

    // Phase 2
    Notes::G6, Notes::G6, Notes::G6, Notes::G6,
    Notes::E7, Notes::E7, Notes::E7, Notes::E7,
    Notes::G7, Notes::G7, Notes::G7, Notes::G7,

    Notes::A7, Notes::A7, Notes::A7,
    Notes::R, Notes::R, Notes::R,
    Notes::F7, Notes::F7, Notes::F7,
    Notes::G7, Notes::G7, Notes::G7,

    Notes::R, Notes::R, Notes::R,
    Notes::E7, Notes::E7, Notes::E7,
    Notes::R, Notes::R, Notes::R,
    Notes::C7, Notes::C7, Notes::C7,

    Notes::D7, Notes::D7, Notes::D7,
    Notes::B6, Notes::B6, Notes::B6,
    Notes::R, Notes::R, Notes::R,
    Notes::R, Notes::R, Notes::R,

    // Phase 3
    Notes::C7, Notes::C7, Notes::C7,
    Notes::R, Notes::R, Notes::R,
    Notes::R, Notes::R, Notes::R,
    Notes::G6, Notes::G6, Notes::G6,

    Notes::R, Notes::R, Notes::R,
    Notes::R, Notes::R, Notes::R,
    Notes::E6, Notes::E6, Notes::E6,
    Notes::R, Notes::R, Notes::R,

    Notes::R, Notes::R, Notes::R,
    Notes::A6, Notes::A6, Notes::A6,
    Notes::R, Notes::R, Notes::R,
    Notes::B6, Notes::B6, Notes::B6,

    Notes::R, Notes::R, Notes::R,
    Notes::AS6, Notes::AS6, Notes::AS6,
    Notes::A6, Notes::A6, Notes::A6,
    Notes::R, Notes::R, Notes::R,

    // Phase 4
    Notes::G6, Notes::G6, Notes::G6, Notes::G6,
    Notes::E7, Notes::E7, Notes::E7, Notes::E7,
    Notes::G7, Notes::G7, Notes::G7, Notes::G7,

    Notes::A7, Notes::A7, Notes::A7,
    Notes::R, Notes::R, Notes::R,
    Notes::F7, Notes::F7, Notes::F7,
    Notes::G7, Notes::G7, Notes::G7,

    Notes::R, Notes::R, Notes::R,
    Notes::E7, Notes::E7, Notes::E7,
    Notes::R, Notes::R, Notes::R,
    Notes::C7, Notes::C7, Notes::C7,

    Notes::D7, Notes::D7, Notes::D7,
    Notes::B6, Notes::B6, Notes::B6,
    Notes::R, Notes::R, Notes::R,
    Notes::R, Notes::R, Notes::R
  };

  static constexpr auto MARIO_BROS_UNDERWORLD_THEME = std::array{
    Notes::C4, Notes::C4, Notes::C4,
    Notes::C5, Notes::C5, Notes::C5,
    Notes::A3, Notes::A3, Notes::A3,
    Notes::A4, Notes::A4, Notes::A4,

    Notes::AS3, Notes::AS3, Notes::AS3,
    Notes::AS4, Notes::AS4, Notes::AS4,
    Notes::R, Notes::R, Notes::R, Notes::R, Notes::R, Notes::R,

    Notes::R, Notes::R, Notes::R, Notes::R, Notes::R, Notes::R, Notes::R, Notes::R, Notes::R, Notes::R, Notes::R, Notes::R,

    Notes::C4, Notes::C4, Notes::C4,
    Notes::C5, Notes::C5, Notes::C5,
    Notes::A3, Notes::A3, Notes::A3,
    Notes::A4, Notes::A4, Notes::A4,

    Notes::AS3, Notes::AS3, Notes::AS3,
    Notes::AS4, Notes::AS4, Notes::AS4,
    Notes::R, Notes::R, Notes::R, Notes::R, Notes::R, Notes::R,

    Notes::R, Notes::R, Notes::R, Notes::R, Notes::R, Notes::R, Notes::R, Notes::R, Notes::R, Notes::R, Notes::R, Notes::R,

    Notes::F3, Notes::F3, Notes::F3,
    Notes::F4, Notes::F4, Notes::F4,
    Notes::D3, Notes::D3, Notes::D3,
    Notes::D4, Notes::D4, Notes::D4,

    Notes::DS3, Notes::DS3, Notes::DS3,
    Notes::DS4, Notes::DS4, Notes::DS4,
    Notes::R, Notes::R, Notes::R, Notes::R, Notes::R, Notes::R,

    Notes::R, Notes::R, Notes::R, Notes::R, Notes::R, Notes::R, Notes::R, Notes::R, Notes::R, Notes::R, Notes::R, Notes::R,

    Notes::F3,
    Notes::F3, Notes::F3,
    Notes::F4, Notes::F4, Notes::F4,
    Notes::D3, Notes::D3, Notes::D3,
    Notes::D4, Notes::D4, Notes::D4,

    Notes::DS3, Notes::DS3, Notes::DS3,
    Notes::DS4, Notes::DS4, Notes::DS4,
    Notes::R, Notes::R, Notes::R, Notes::R, Notes::R, Notes::R,

    Notes::R, Notes::R, Notes::R, Notes::R, Notes::R, Notes::R,
    Notes::DS4, Notes::DS4,
    Notes::CS4, Notes::CS4,
    Notes::D4, Notes::D4,

    Notes::CS4, Notes::CS4, Notes::CS4, Notes::CS4, Notes::CS4, Notes::CS4,
    Notes::DS4, Notes::DS4, Notes::DS4, Notes::DS4, Notes::DS4, Notes::DS4,

    Notes::DS4, Notes::DS4, Notes::DS4, Notes::DS4, Notes::DS4, Notes::DS4,
    Notes::GS3, Notes::GS3, Notes::GS3, Notes::GS3, Notes::GS3, Notes::GS3,

    Notes::G3, Notes::G3, Notes::G3, Notes::G3, Notes::G3, Notes::G3,
    Notes::CS4, Notes::CS4, Notes::CS4, Notes::CS4, Notes::CS4, Notes::CS4,

    Notes::C4, Notes::C4,
    Notes::FS4, Notes::FS4,
    Notes::F4, Notes::F4,
    Notes::E3, Notes::E3,
    Notes::AS4, Notes::AS4,
    Notes::A4, Notes::A4,

    Notes::GS4, Notes::GS4, Notes::GS4, Notes::GS4,
    Notes::DS4, Notes::DS4, Notes::DS4, Notes::DS4,
    Notes::B3, Notes::B3, Notes::B3, Notes::B3,

    Notes::AS3, Notes::AS3, Notes::AS3, Notes::AS3,
    Notes::A3, Notes::A3, Notes::A3, Notes::A3,
    Notes::GS3, Notes::GS3, Notes::GS3, Notes::GS3,

    Notes::R, Notes::R, Notes::R, Notes::R, Notes::R, Notes::R, Notes::R, Notes::R, Notes::R, Notes::R, Notes::R, Notes::R,
    Notes::R, Notes::R, Notes::R, Notes::R, Notes::R, Notes::R, Notes::R, Notes::R, Notes::R, Notes::R, Notes::R, Notes::R,
    Notes::R, Notes::R, Notes::R, Notes::R, Notes::R, Notes::R, Notes::R, Notes::R, Notes::R, Notes::R, Notes::R, Notes::R
  };
}  // namespace Music
