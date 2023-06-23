#pragma once

#include <raylib.h>

#include "universe.h"

typedef struct Timer
{
    double start_time;
    double lifetime;
} Timer;

typedef enum State
{
    PAUSED,
    RUNNING,
} State;

typedef struct Simulation
{
    Timer timer;
    double speed;
    Universe universe;
    int state;
    Vector2 mouse_pos;
} Simulation;

Simulation initSimulation(void);
void startSimulation(Simulation *simulation);
void drawSimulation(Simulation *simulation);
void closeSimulation(Simulation *simulation);
static void tick(Simulation *simulation);
static void update(Simulation *simulation);
static void edit(Simulation *simulation);

inline static void startTimer(Timer *timer, double lifetime)
{
    timer->start_time = GetTime();
    timer->lifetime = lifetime;
}
inline static bool timerDone(const Timer *timer)
{
    return GetTime() - timer->start_time >= timer->lifetime;
}
inline static double timerGetElapsed(const Timer *timer)
{
    return GetTime() - timer->start_time;
}