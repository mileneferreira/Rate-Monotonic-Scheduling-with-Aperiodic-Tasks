Rate Monotonic Scheduling (Automatic RM + Aperiodic Tasks)

This project implements a system that plays two Super Mario Bros songs using a PWM-driven buzzer on the ESP32. It includes button input, interrupts, periodic and aperiodic tasks, custom GPIO and PWM abstractions, and a custom-configurable thread management system.

This project implements a C++ system using:

Audio generation via PWM (buzzer)

Button reading via GPIO with interruption

Periodic tasks to play music

Aperiodic tasks triggered by interruptions

Proprietary infrastructure for thread configuration and task state queries

Musical notes library with frequencies in Hz

The system allows different melodies to be played when buttons are pressed, using PWM to generate the frequencies corresponding to the musical notes.

📁 File Organization
1. /main/main.cpp
File Function Entry point of the application. Configures GPIOs, PWM, tasks, and executes the main loop.

Main Elements

Buzzer Type: using Buzzer = Peripherals::PWM<23, TIMER_0, CHANNEL_0>; Uses pin 23 for the buzzer's PWM output.

Periodic Tasks for Playing Music: A periodic task reads the current song and sends the frequency to the buzzer.

Button Action:

Button 1 – GPIO 18 → Selects "Regular" music

Button 2 – GPIO 19 → Selects "Underworld" music MusicChoice enum controls which song will be played.

Main Loop only keeps the program active: while (true) std::this_thread::sleep_for(1s);

2. Music Library (/inc/music/Song.h)
Function Defines:

Song type (span of frequencies)

Complete set of musical notes from B0 to B7

Ready-made songs: Regular Theme and Underworld Theme

Metrics Used

Notes are represented in Hz.

Example: static constexpr auto A4 = 440_Hz;

Important Conversion

Frequency -> std::chrono::milliseconds → Determines the note's period to control duration.

3. Peripherals
3.1 GPIO.hpp
Function Abstraction for digital inputs and outputs.

Main Features

GPIO::Output<pin> – simple write HIGH/LOW

GPIO::Input<pin, edge, pull> – configuration of:

pin

edge (RISING / FALLING)

resistor (UP / DOWN)

Interrupts

register_interrupt(isr_handler, arg)

unregister_interrupt()

Usage in the Project

Button 1 → GPIO 18

Button 2 → GPIO 19

Both configured with falling edge (FALLING) and Pull-up.

3.2 PWM.hpp
Function Generates frequencies using LEDC (ESP32's hardware PWM).

Template PWM<pin, timer, channel> Parameters used in the project:

Resource	Value
pin	23
timer	TIMER_0
channel	CHANNEL_0
base frequency	4000 Hz
resolution	8 bits (0–255 duty)
Main Functions

start(): Initializes PWM channel.

stop(): Turns off PWM (duty = 0).

set_frequency(Frequency freq): Changes timer frequency.

set_duty(Percentage duty): Defines duty cycle (0.0 to 1.0).

4. Task System
The project implements its own framework for task manipulation using std::thread + ESP-IDF pthread extensions.

4.1 task/Config.h & Config.cpp
Function Defines parameters when creating threads using std::thread, but applying ESP-IDF configurations:

thread name

priority

target core

stack size

configuration inheritance

Example Usage

C++
Task::Config()
  .with_name("Music Task")
  .with_priority(3)
  .pinned_to_core(0)
  .with_stack_size(8*1024);
4.2 task/Query.h & Query.cpp
Function Queries information of the current thread or the pthread configuration.

this_thread API

name()

core()

priority()

free_stack()

pthread API

name()

core()

priority()

stack_size()

4.3 task/Aperiodic.hpp
Function Allows the creation of a task that runs only when an interrupt occurs.

How it Works

Uses a semaphore (trigger_sem)

The ISR releases the semaphore

The associated thread executes the callback

Usage in the Project Each button creates an aperiodic task:

C++
auto button1_handler = Task::Aperiodic<Button1>([](){ music_chosen = REGULAR; });
4.4 task/Periodic.hpp
Function Creates a periodic task that runs every provided interval.

Example Task::Periodic(200ms, [](){ tocar_nota(); });

In the Project:

A periodic task reads the current song

Sends the frequency to the buzzer via PWM

Advances to the next note

5. Utils
5.1 Frequency.h
Function Represents a frequency in Hz.

Conversions

to uint32_t

to std::chrono::milliseconds (period = 1000/freq)

5.2 Percentage.h
Function Represents decimal duty-cycle values.

Supports literal: 50_percent // becomes 0.50

5.3 print.hpp
Function Prints colored text to the terminal using std::print().

🔌 Pins Used in the Project
Function	Pin	Mode
Buzzer PWM	GPIO 23	PWM Output
Button 1	GPIO 18	Input, pull-up, FALLING
Button 2	GPIO 19	Input, pull-up, FALLING
🎵 General Code Operation
Initializes PWM on pin 23 to control the buzzer.

Loads songs defined in Song.h.

Creates a periodic task that:

reads the selected song

updates the PWM to play each note

Creates two aperiodic tasks linked to interrupts:

Button 1 → switches to the Regular song

Button 2 → switches to the Underworld song

The system remains running in the infinite loop.



