#include <assert.h>
#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#include <stdlib.h>

#include "settings.h"
#include "simulation.h"

Simulation *simulationInit(void) {
  Simulation *simulation = malloc(sizeof(Simulation));
  simulation->timer = (Timer){0, 0};
  simulation->speed = 0.5;
  simulation->universe = universeInit();
  simulation->state = PAUSED;

  return simulation;
}

void simulationStart(Simulation *simulation) {
  printf("Starting...\n");
  assert(!GetWindowHandle());
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
  SetTargetFPS(GAME_FPS);
  startTimer(&simulation->timer, simulation->speed);
}

static void update(Simulation *simulation) {
  if (timerDone(&simulation->timer)) {
    universeUpdate(simulation->universe);
    startTimer(&simulation->timer, simulation->speed);
  }
}

static void edit(Simulation *simulation) {
  usize pos_x = simulation->mouse_pos.x;
  usize pos_y = simulation->mouse_pos.y;
  if (pos_x >= 0 && pos_x < simulation->universe->dimensions.x && pos_y >= 0 &&
      pos_y < simulation->universe->dimensions.y) {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
      simulation->universe->cells[pos_x][pos_y] =
          !simulation->universe->cells[pos_x][pos_y];
    }
  }
}

void simulationUpdate(Simulation *simulation) {
  while (!WindowShouldClose()) {
    simulation->mouse_pos = Vector2Divide(
        GetMousePosition(),
        (Vector2){CELL_SIZE + CELL_PADDING / 2, CELL_SIZE + CELL_PADDING / 2});
    BeginDrawing();
    ClearBackground(BLACK);
    universeDraw(simulation->universe, simulation->state,
                 simulation->mouse_pos);
    if (IsKeyPressed(KEY_SPACE)) {
      simulation->state = (simulation->state + 1) % 2;
    }
    if (IsKeyPressed(KEY_C)) {
      universeClear(simulation->universe);
    }
    if (IsKeyPressed(KEY_R)) {
      universePopulate(simulation->universe);
    }
    if (IsKeyPressed(KEY_D)) {
      simulation->universe->draw_grid = !simulation->universe->draw_grid;
    }
    if (IsKeyPressed(KEY_UP)) {
      simulation->speed -= 0.01;
    }
    if (IsKeyPressed(KEY_DOWN)) {
      simulation->speed += 0.01;
    }
    DrawRectangle(0, 0, 150, 150, (Color){255.0, 255.0, 255.0, 200.0});
    switch (simulation->state) {
    case PAUSED:
      edit(simulation);
      DrawText("PAUSED", 1, 20, 30, MAROON);
      break;
    case RUNNING:
      update(simulation);
      DrawText("RUNNING", 1, 20, 30, MAROON);
      break;
    default:
      break;
    }
    DrawText("CONTROLS", 1, 50, 20, DARKBLUE);
    DrawText("PLAY/PAUSE - [SPACE]", 1, 70, 10, DARKBLUE);
    DrawText("TOGGLE CELL - [LMOUSE]", 1, 80, 10, DARKBLUE);
    DrawText("CLEAR - [C]", 1, 90, 10, DARKBLUE);
    DrawText("RANOMISE - [R]", 1, 100, 10, DARKBLUE);
    DrawText("TOGGLE GRID - [D]", 1, 110, 10, DARKBLUE);
    DrawText("INCREASE SPEED - [UP]", 1, 120, 10, DARKBLUE);
    DrawText("DECREASE SPEED - [DOWN]", 1, 130, 10, DARKBLUE);
    DrawFPS(1, 0);
    EndDrawing();
  }
}

void simulationClose(Simulation *simulation) {
  printf("Closing...\n");
  universeDelete(simulation->universe);
  assert(GetWindowHandle());
  CloseWindow();
}
