#pragma once

#include "universe.h"

typedef struct _timer_t {
  f64 start_time;
  f64 lifetime;
} Timer;

typedef enum state_t {
  PAUSED,
  RUNNING,
} State;

typedef struct simulation_t {
  Universe *universe;
  Timer timer;
  f64 speed;
  u8 state;
  Vector2 mouse_pos;
} Simulation;

Simulation *simulationInit(void);
void simulationStart(Simulation *simulation);
void simulationUpdate(Simulation *simulation);
void simulationClose(Simulation *simulation);

inline static void startTimer(Timer *timer, f64 lifetime) {
  timer->start_time = GetTime();
  timer->lifetime = lifetime;
}
inline static bool timerDone(const Timer *timer) {
  return GetTime() - timer->start_time >= timer->lifetime;
}
inline static f64 timerGetElapsed(const Timer *timer) {
  return GetTime() - timer->start_time;
}
