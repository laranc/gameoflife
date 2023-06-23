#include "universe.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>

Universe initUniverse(void)
{
    Universe universe;
    universe.dimensions = initial_dimensions;
    universe.draw_grid = false;
    srand(time(NULL));

    universe.cells = malloc(sizeof(bool *) * universe.dimensions.x);
    universe.buffer = malloc(sizeof(bool *) * universe.dimensions.x);
    for (size_t x = 0; x < universe.dimensions.x; x++)
    {
        universe.cells[x] = malloc(sizeof(bool) * universe.dimensions.y);
        universe.buffer[x] = malloc(sizeof(bool) * universe.dimensions.y);
        for (size_t y = 0; y < universe.dimensions.y; y++)
        {
            universe.cells[x][y] = rand() % 2;
            universe.buffer[x][y] = universe.cells[x][y];
        }
    }

    return universe;
}

void updateUniverse(Universe *universe)
{
    for (size_t x = 0; x < universe->dimensions.x; x++)
    {
        for (size_t y = 0; y < universe->dimensions.y; y++)
        {
            universe->buffer[x][y] = universe->cells[x][y];
        }
    }
    generation(universe);
    for (size_t x = 0; x < universe->dimensions.x; x++)
    {
        for (size_t y = 0; y < universe->dimensions.y; y++)
        {
            universe->cells[x][y] = universe->buffer[x][y];
        }
    }
}

void drawUniverse(const Universe *universe, int state, Vector2 mouse_pos)
{
    for (size_t x = 0; x < universe->dimensions.x; x++)
    {
        for (size_t y = 0; y < universe->dimensions.y; y++)
        {
            Vector2 position = (Vector2){x + CELL_PADDING + (x * CELL_SIZE), y + CELL_PADDING + (y * CELL_SIZE)};
            Vector2 size = (Vector2){CELL_SIZE - CELL_PADDING, CELL_SIZE - CELL_PADDING};
            if (universe->cells[x][y])
            {
                DrawRectangleV(position, size, RAYWHITE);
            }
            else if (universe->draw_grid)
            {
                DrawRectangleLines(position.x, position.y, size.x, size.y, RAYWHITE);
            }
            if (state == 0 && (int)mouse_pos.x == x && (int)mouse_pos.y == y)
            {
                DrawRectangleRounded((Rectangle){
                                         position.x,
                                         position.y,
                                         size.x,
                                         size.y},
                                     0.25, 0, BLUE);
            }
        }
    }
}

void clearUniverse(Universe *universe)
{
    for (size_t x = 0; x < universe->dimensions.x; x++)
    {
        for (size_t y = 0; y < universe->dimensions.y; y++)
        {
            universe->cells[x][y] = 0;
        }
    }
}

void populateUniverse(Universe *universe)
{
    for (size_t x = 0; x < universe->dimensions.x; x++)
    {
        for (size_t y = 0; y < universe->dimensions.y; y++)
        {
            universe->cells[x][y] = rand() % 2;
        }
    }
}

void deleteUniverse(Universe *universe)
{
    for (size_t i = 0; i < universe->dimensions.x; i++)
    {
        free(universe->cells[i]);
    }
    free(universe->cells);
}

static void generation(Universe *universe)
{
    for (size_t x = 0; x < universe->dimensions.x; x++)
    {
        for (size_t y = 0; y < universe->dimensions.y; y++)
        {
            universe->buffer[x][y] = rule(neighbors(universe->cells, x, y, universe->dimensions), universe->cells[x][y]);
        }
    }
}

static int neighbors(bool **cells, int x, int y, Vector2 dimensions)
{
    int sum = 0;
    for (size_t i = x - 1; i <= x + 1; i++)
    {
        for (size_t j = y - 1; j <= y + 1; j++)
        {
            int col = (i + (int)dimensions.x) % (int)dimensions.x;
            int row = (j + (int)dimensions.y) % (int)dimensions.y;
            sum += (int)cells[col][row];
        }
    }
    sum -= (int)cells[x][y];

    return sum;
}

static bool rule(int neighbors, bool state)
{
    if (!state && neighbors == 3)
    {
        return 1;
    }
    else if (state && (neighbors < 2 || neighbors > 3))
    {
        return 0;
    }
    else
    {
        return state;
    }
}