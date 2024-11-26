#include <stdlib.h>
#include <string.h>

#include "universe.h"

Universe *universeInit(void) {
  Universe *universe = malloc(sizeof(Universe));
  universe->dimensions = initial_dimensions;
  universe->draw_grid = false;

  universe->cells = malloc(sizeof(bool *) * universe->dimensions.x);
  universe->buffer = malloc(sizeof(bool *) * universe->dimensions.x);
  for (usize x = 0; x < universe->dimensions.x; x++) {
    universe->cells[x] = malloc(sizeof(bool) * universe->dimensions.y);
    universe->buffer[x] = malloc(sizeof(bool) * universe->dimensions.y);
    for (usize y = 0; y < universe->dimensions.y; y++) {
      universe->cells[x][y] = rand() % 2;
      universe->buffer[x][y] = universe->cells[x][y];
    }
  }

  return universe;
}

static bool rule(u8 neighbors, bool state) {
  if (!state && neighbors == 3) {
    return 1;
  } else if (state && (neighbors < 2 || neighbors > 3)) {
    return 0;
  } else {
    return state;
  }
}

static u8 neighbors(bool **cells, u32 x, u32 y, Vector2 dimensions) {
  u8 sum = 0;
  for (usize i = x - 1; i <= x + 1; i++) {
    for (usize j = y - 1; j <= y + 1; j++) {
      usize col = (i + (usize)dimensions.x) % (usize)dimensions.x;
      usize row = (j + (usize)dimensions.y) % (usize)dimensions.y;
      sum += cells[col][row];
    }
  }
  sum -= cells[x][y];

  return sum;
}

void universeUpdate(Universe *universe) {
  for (usize i = 0; i < universe->dimensions.x; i++) {
    memcpy(universe->buffer[i], universe->cells[i],
           sizeof(bool) * universe->dimensions.y);
  }
  for (usize x = 0; x < universe->dimensions.x; x++) {
    for (usize y = 0; y < universe->dimensions.y; y++) {
      universe->buffer[x][y] =
          rule(neighbors(universe->cells, x, y, universe->dimensions),
               universe->cells[x][y]);
    }
  }
  for (usize i = 0; i < universe->dimensions.x; i++) {
    memcpy(universe->cells[i], universe->buffer[i],
           sizeof(bool) * universe->dimensions.y);
  }
}

void universeDraw(const Universe *universe, u8 state, Vector2 mouse_pos) {
  Vector2 size = (Vector2){CELL_SIZE - CELL_PADDING, CELL_SIZE - CELL_PADDING};

  for (usize x = 0; x < universe->dimensions.x; x++) {
    for (usize y = 0; y < universe->dimensions.y; y++) {
      Vector2 position = (Vector2){x + CELL_PADDING + (x * CELL_SIZE),
                                   y + CELL_PADDING + (y * CELL_SIZE)};

      if (universe->cells[x][y]) {
        DrawRectangleV(position, size, RAYWHITE);
      } else if (universe->draw_grid) {
        DrawRectangleLines(position.x, position.y, size.x, size.y, RAYWHITE);
      }
      if (state == 0 && (u32)mouse_pos.x == x && (u32)mouse_pos.y == y) {
        DrawRectangleRounded(
            (Rectangle){position.x, position.y, size.x, size.y}, 0.25, 0, BLUE);
      }
    }
  }
}

void universeClear(Universe *universe) {
  for (usize x = 0; x < universe->dimensions.x; x++) {
    for (usize y = 0; y < universe->dimensions.y; y++) {
      universe->cells[x][y] = 0;
    }
  }
}

void universePopulate(Universe *universe) {
  for (usize x = 0; x < universe->dimensions.x; x++) {
    for (usize y = 0; y < universe->dimensions.y; y++) {
      universe->cells[x][y] = rand() % 2;
    }
  }
}

void universeDelete(Universe *universe) {
  for (usize i = 0; i < universe->dimensions.x; i++) {
    free(universe->cells[i]);
  }
  free(universe->cells);
}
