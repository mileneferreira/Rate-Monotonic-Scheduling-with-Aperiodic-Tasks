#include <iterator>

#include "esp_task_wdt.h"
#include "music/Song.h"
#include "peripherals/GPIO.hpp"
#include "peripherals/PWM.hpp"
#include "task/Aperiodic.hpp"
#include "task/Config.h"
#include "task/Periodic.hpp"
#include "task/Query.h"
#include "utils/Frequency.h"
#include "utils/Percentage.h"
#include "utils/print.hpp"

using Buzzer = Peripherals::PWM<23, Peripherals::PWMTimer::TIMER_0, Peripherals::PWMChannel::CHANNEL_0>;

enum class MusicChoice {
  REGULAR,
  UNDERWORLD,
};

static MusicChoice music_chosen;

auto get_note() -> Utils::Frequency {
  static size_t note_index = 0;

  switch (music_chosen) {
    case MusicChoice::REGULAR:
      note_index = (note_index + 1) % Music::MARIO_BROS_THEME.size();
      return Music::MARIO_BROS_THEME[note_index];

    case MusicChoice::UNDERWORLD:
      note_index = (note_index + 1) % Music::MARIO_BROS_UNDERWORLD_THEME.size();
      return Music::MARIO_BROS_UNDERWORLD_THEME[note_index];

    default: std::unreachable();
  }
}

auto play() -> void {
  static Buzzer output;

  using namespace Utils::literals;
  output.set(get_note(), 25_percent);
}

template <uint8_t pin_number>
auto toggle_gpio() -> void {
  static auto state = Peripherals::GPIO::Level::LOW;
  Peripherals::GPIO::Output<pin_number> pin;

  if(state == Peripherals::GPIO::Level::LOW)
    state = Peripherals::GPIO::Level::HIGH; 
  else 
    state = Peripherals::GPIO::Level::LOW;

  pin.set(state);
}

using namespace std::chrono_literals;
extern "C" void app_main(void) {
  esp_task_wdt_deinit();

  Task::Config()
    .with_name("Music Player")
    .pinned_to_core(0)
    .with_stack_size(4 * 1024);
  auto music_player = Task::Periodic(50ms, play);

  using namespace Utils::literals;
  Task::Config()
    .with_name("Green LED")
    .pinned_to_core(1)
    .with_stack_size(1024);
  auto green_led = Task::Periodic(1_Hz, toggle_gpio<15>);
  
  Task::Config()
    .with_name("Red LED")
    .pinned_to_core(1)
    .with_stack_size(1024);
  auto red_led = Task::Periodic(2_Hz, toggle_gpio<2>);
  
  Task::C()
    .with_name("Yellow LED")
    .pinned_to_core(1)
    .with_stack_size(1024);
  auto yellow_led = Task::Periodic(4_Hz, toggle_gpio<4>);

  using Button1 = Peripherals::GPIO::Input<18, Peripherals::GPIO::Edge::RISING, Peripherals::GPIO::Pull::DOWN>;
  Task::Config()
    .with_name("Button 1")
    .pinned_to_core(0)
    .with_stack_size(3 * 1024);
  auto button1_handler = Task::Aperiodic<Button1>([]() { music_chosen = MusicChoice::REGULAR; });

  using Button2 = Peripherals::GPIO::Input<19, Peripherals::GPIO::Edge::FALLING, Peripherals::GPIO::Pull::UP>;
  Task::Config()
    .with_name("Button 2")
    .pinned_to_core(0)
    .with_stack_size(3 * 1024);
  auto button2_handler = Task::Aperiodic<Button2>([]() { music_chosen = MusicChoice::UNDERWORLD; });

  while (true)
    std::this_thread::sleep_for(1s);
}
