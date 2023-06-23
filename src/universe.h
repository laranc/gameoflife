#pragma once

#include <raylib.h>

#include "settings.h"

static const Vector2 initial_dimensions = (Vector2){SCREEN_WIDTH / (CELL_SIZE + CELL_PADDING / 2), SCREEN_HEIGHT / (CELL_SIZE + CELL_PADDING / 2)};

typedef struct Universe
{
    bool **cells;
    bool **buffer;
    Vector2 dimensions;
    bool draw_grid;
} Universe;

Universe initUniverse(void);
void updateUniverse(Universe *universe);
void drawUniverse(const Universe *universe, int state, Vector2 mouse_pos);
void clearUniverse(Universe *universe);
void populateUniverse(Universe *universe);
void deleteUniverse(Universe *universe);
static void generation(Universe *universe);
static int neighbors(bool **cells, int x, int y, Vector2 dimensions);
static bool rule(int neighbors, bool state);