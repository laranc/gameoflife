#pragma once

#include <raylib.h>

#include "settings.h"
#include "types.h"

static const Vector2 initial_dimensions =
    (Vector2){SCREEN_WIDTH / (CELL_SIZE + CELL_PADDING / 2),
              SCREEN_HEIGHT / (CELL_SIZE + CELL_PADDING / 2)};
static const Vector2 maximum_dimensions =
    (Vector2){1000.0, 1000.0}; // place holder
typedef struct universe_t {
  bool **cells;
  bool **buffer;
  Vector2 dimensions;
  bool draw_grid;
} Universe;

Universe *universeInit(void);
void universeUpdate(Universe *universe);
void universeDraw(const Universe *universe, u8 state, Vector2 mouse_pos);
void universeClear(Universe *universe);
void universePopulate(Universe *universe);
void universeDelete(Universe *universe);
