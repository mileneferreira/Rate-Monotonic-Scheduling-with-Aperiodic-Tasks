# 🍄 👲🏻 🏰 👸🏼 🍄 🐢 💗 🏎️💨 ⭐ 🧱 👑 🪙
# **Rate Monotonic Scheduling with Periodic and Aperiodic Tasks on ESP32**
### _Mario Kart World Music Player using PWM + Buttons_

This project implements a full real‑time scheduling example on the ESP32, combining *periodic* and *aperiodic* tasks. It uses PWM audio generation, interrupt‑driven button input, and multiple blinking LEDs to simulate real-time behavior.

The logic includes:

- 🔄 **Periodic tasks** → simulated by LED blinking  
- ⏱️ **Aperiodic tasks** → triggered by user interaction (buttons changing the music)  
- 🎶 PWM buzzer playing Mario melodies  
- 🎚️ GPIO + PWM  

---

# 📌 **Real-Time Scheduling concepts illustrated in this project**

## 🔄 **LEDs = Simulation of Periodic Tasks**
The three LEDs operate on fixed intervals (1 Hz, 2 Hz, 4 Hz).  
Each LED task runs on a strictly periodic schedule, representing deterministic, time‑triggered tasks in real‑time systems.

| LED | Pin | Frequency | Role |
|-----|------|------------|--------|
| Green | 15 | 1 Hz | Low‑priority periodic task |
| Red | 2 | 2 Hz | Medium‑priority periodic task |
| Yellow | 4 | 4 Hz | High‑frequency periodic task |

These tasks show how periodic activities behave under Rate Monotonic Scheduling (RMS):  
**higher frequencies = higher rate = higher priority**.

---

## ⚡ **Music Selection = Aperiodic Tasks**
Button presses do **not** follow any fixed schedule.  
They occur at unpredictable, user‑defined times → making them *aperiodic events*.

- Button 1 → Switch to Regular Song  
- Button 2 → Switch to Underworld Song  

Each button is handled by an **Aperiodic Task**, triggered by a hardware interrupt.  
This demonstrates real-time *event-driven* behavior.

> ✔ Aperiodic tasks change the state of the system  
> ✔ Periodic tasks continue running independently  
> ✔ Both coexist under the scheduling model

---

## 🎼 **Music Playback (Periodic Execution, Aperiodic Selection)**

Even though the **selection of the song** is an *aperiodic event*, the **playback of notes** is done by a **periodic task**:

- Runs every **50 ms**
- Reads the next note of the selected song
- Sends frequency to the PWM buzzer

| Component | Type |
|-----------|--------|
| Song selection | **Aperiodic task** (button) |
| Audio playback | **Periodic task** (fixed interval) |

This dual behavior exemplify real‑time systems where aperiodic events modify periodic processes.

---

# 📂 **Project File Organization**

## **1. `main/main.cpp`**
📌 **Purpose:** Entry point of the system. Configures GPIOs, PWM, periodic/aperiodic tasks, and keeps the main loop alive.

### **Main Components**

#### 🔊 **Buzzer (PWM on GPIO 23)**

```cpp
using Buzzer = Peripherals::PWM<23, TIMER_0, CHANNEL_0>;
```

- Generates musical frequencies  
- Used by the periodic music task
- Pin used: **GPIO 23**
- PWM output used to generate musical frequencies

#### 🎮 **Button Actions**
| Button | Pin | Action |
|--------|------|---------|
| Button 1 | GPIO 18 | Selects **Regular Song** |
| Button 2 | GPIO 19 | Selects **Underworld Song** |

Controlled through the `MusicChoice` enum.

#### 🔁 **Main Loop**
Keeps the program running:
```cpp
while (true) std::this_thread::sleep_for(1s);
```

---

#### 🎼 **Periodic Tasks**
- Reads the currently selected song  
- Sends the current frequency to the buzzer  
- Advances to the next musical note  

# 🔆 **LED Periodic Tasks**

All LED blink tasks use:

```cpp
template <uint8_t pin_number>
auto toggle_gpio() -> void;
```

Created as:

```cpp
auto green_led = Task::Periodic(1_Hz, toggle_gpio<15>);
auto red_led   = Task::Periodic(2_Hz, toggle_gpio<2>);
auto yellow_led = Task::Periodic(4_Hz, toggle_gpio<4>);
```

These simulate the periodic task scheduling behavior under RM.

---

## 🎵 **2. Music Library (`inc/music/Song.h`)**

Contains:
- Notes from **B0 → B7**
- Two classical Mario Kart World songs:
  - Regular   
  - Underworld

#### 🎚️ Example note:
```cpp
static constexpr auto A4 = 440_Hz;
```

Songs are represented as `span<Frequency>`.

---

#### ⏱️ Important Conversion:
**Frequency → duration (ms)**  
Used to determine note timing in the periodic task.

---

## 🛠️ **3.GPIO and PWM**

### `3.1. GPIO.hpp`**
📌 Abstraction for digital inputs and outputs.

**Main features:**
- `GPIO::Output<pin>` → write HIGH/LOW  
- `GPIO::Input<pin, edge, pull>` → configure:  
  - pin  
  - edge (RISING/FALLING)  
  - pull resistor (UP/DOWN)

**Interrupts**
```cpp
register_interrupt(isr_handler, arg);
```

Used for buttons + LEDs.

### `3.2. PWM.hpp`**
📌 Generates frequencies using ESP32's LEDC module.

| Parameter | Value |
|-----------|--------|
| Pin | **23** |
| Timer | `TIMER_0` |
| Channel | `CHANNEL_0` |
| Base frequency | 4000 Hz |
| Resolution | 8‑bit |

**Main functions:**
- `start()`  
- `stop()`  
- `set_frequency(freq)`  
- `set_duty(duty)`  

## 🔌 **4. Pin Usage**

| Component | Pin | Type |
|-----------|------|-----------|
| Buzzer | **23** | PWM Output |
| Button 1 | **18** | Input (RISING, Pull‑down) |
| Button 2 | **19** | Input (FALLING, Pull‑up) |
| Green LED | **15** | Output |
| Red LED | **2** | Output |
| Yellow LED | **4** | Output |

---

🍄 👲🏻 🏰 👸🏼 🍄 🐢 💗 🏎️💨 ⭐ 🧱 👑 🪙
## **5. Overall System Flow**

1. PWM initialized on pin 23  
2. Music library loads Regular + Underworld themes  
3. Periodic task:  
   - reads selected song  
   - plays note via PWM  
   - advances to next note  
4. Aperiodic tasks:  
   - Button 1 → selects Regular Song  
   - Button 2 → selects Underworld Song  
5. Infinite loop keeps the system alive  

---
