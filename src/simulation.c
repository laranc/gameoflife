#include "simulation.h"

#include <stdio.h>
#include <assert.h>
#include <string.h>

#include <raymath.h>

#include "settings.h"

Simulation initSimulation(void)
{
    Simulation simulation;
    simulation.timer = (Timer){0, 0};
    simulation.speed = 0.5;
    simulation.universe = initUniverse();
    simulation.state = PAUSED;

    return simulation;
}

void startSimulation(Simulation *simulation)
{
    printf("Starting...\n");
    assert(!GetWindowHandle());
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(GAME_FPS);
    startTimer(&simulation->timer, simulation->speed);
}

void drawSimulation(Simulation *simulation)
{
    while (!WindowShouldClose())
    {
        tick(simulation);
    }
}

void closeSimulation(Simulation *simulation)
{
    printf("Closing...\n");
    deleteUniverse(&simulation->universe);
    assert(GetWindowHandle());
    CloseWindow();
}

static void tick(Simulation *simulation)
{
    simulation->mouse_pos = Vector2Divide(GetMousePosition(), (Vector2){CELL_SIZE + CELL_PADDING / 2, CELL_SIZE + CELL_PADDING / 2});
    BeginDrawing();
    ClearBackground(BLACK);
    drawUniverse(&simulation->universe, simulation->state, simulation->mouse_pos);
    if (IsKeyPressed(KEY_SPACE))
    {
        simulation->state = (simulation->state + 1) % 2;
    }
    if (IsKeyPressed(KEY_C))
    {
        clearUniverse(&simulation->universe);
    }
    if (IsKeyPressed(KEY_R))
    {
        populateUniverse(&simulation->universe);
    }
    if (IsKeyPressed(KEY_D))
    {
        simulation->universe.draw_grid = !simulation->universe.draw_grid;
    }
    if (IsKeyPressed(KEY_UP))
    {
        simulation->speed -= 0.01;
    }
    if (IsKeyPressed(KEY_DOWN))
    {
        simulation->speed += 0.01;
    }
    switch (simulation->state)
    {
    case PAUSED:
        edit(simulation);
        DrawText("PAUSED", 0, 20, 30, MAROON);
        break;
    case RUNNING:
        update(simulation);
        DrawText("RUNNING", 0, 20, 30, MAROON);
        break;
    default:
        break;
    }
    DrawFPS(0, 0);
    EndDrawing();
}

static void update(Simulation *simulation)
{
    if (timerDone(&simulation->timer))
    {
        updateUniverse(&simulation->universe);
        startTimer(&simulation->timer, simulation->speed);
    }
}

static void edit(Simulation *simulation)
{
    size_t pos_x = simulation->mouse_pos.x;
    size_t pos_y = simulation->mouse_pos.y;
    if (pos_x >= 0 && pos_x < simulation->universe.dimensions.x && pos_y >= 0 && pos_y < simulation->universe.dimensions.y)
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            simulation->universe.cells[pos_x][pos_y] = !simulation->universe.cells[pos_x][pos_y];
        }
    }
}