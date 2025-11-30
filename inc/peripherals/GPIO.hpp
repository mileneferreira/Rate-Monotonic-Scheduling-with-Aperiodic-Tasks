#pragma once

#include <cstdint>
#include <mutex>

#include "driver/gpio.h"
#include "hal/gpio_types.h"
#include "task/Aperiodic.hpp"

namespace Peripherals {
  namespace {
    static inline auto installed = std::once_flag{};
  }

  struct GPIO {
    enum class Level : bool {
      LOW = false,
      HIGH = true,
    };

    template <uint8_t pin>
    struct Output {
      private:
        static inline auto initialized = std::once_flag{};
      
        static auto initialize() -> void {
          gpio_config_t io_conf = {
            .pin_bit_mask = (1ULL << pin),
            .mode = GPIO_MODE_OUTPUT,
            .pull_up_en = GPIO_PULLUP_DISABLE,
            .pull_down_en = GPIO_PULLDOWN_DISABLE,
            .intr_type = GPIO_INTR_DISABLE,
          };
          
          gpio_config(&io_conf);
        }
          
      public:
      Output() { std::call_once(initialized, initialize); }

      auto set(Level lvl) -> void {
        gpio_set_level(static_cast<gpio_num_t>(pin), lvl == Level::HIGH ? 1 : 0);
      }
    };

    enum class Edge : uint8_t {
      RISING = GPIO_INTR_POSEDGE,
      FALLING = GPIO_INTR_NEGEDGE,
      BOTH = GPIO_INTR_ANYEDGE,
    };

    enum class Pull : uint8_t {
      NONE,
      UP,
      DOWN,
    };

    template <uint8_t pin, Edge edge, Pull pull = Pull::NONE>
    struct Input {
      static auto initialize() -> void {
        gpio_config_t io_conf = {
          .pin_bit_mask = (1ULL << pin),
          .mode = GPIO_MODE_INPUT,
          .pull_up_en = pull == Pull::UP ? GPIO_PULLUP_ENABLE : GPIO_PULLUP_DISABLE,
          .pull_down_en = pull == Pull::DOWN ? GPIO_PULLDOWN_ENABLE : GPIO_PULLDOWN_DISABLE,
          .intr_type = static_cast<gpio_int_type_t>(edge),
        };

        gpio_config(&io_conf);
      }

      static auto read() -> Level {
        return gpio_get_level(static_cast<gpio_num_t>(pin)) > 0 ? GPIO::Level::HIGH : GPIO::Level::LOW;
      }

      static auto register_interrupt(Task::isr_handler_t isr_handler_ptr, void* arg) -> void {
        initialize();
        std::call_once(installed, gpio_install_isr_service, 0);
        gpio_isr_handler_add((gpio_num_t)pin, isr_handler_ptr, arg);
      }

      static auto unregister_interrupt() -> void {
        gpio_isr_handler_remove((gpio_num_t)pin);
      }
    };
  };
}  // namespace Peripherals
