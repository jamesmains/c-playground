#include <raylib.h>
#include <math.h>
#include <stdio.h>
#define INIT_WINDOW_X 1000
#define INIT_WINDOW_Y 1000
#define SCALE 2

// This project requires you have raylib installed / compiled locally, still figuring out raylib...
int main()
{

    // 1. Enable High DPI support
    SetConfigFlags(FLAG_WINDOW_HIGHDPI);
    InitWindow(INIT_WINDOW_X, INIT_WINDOW_Y, "Valentine's Day");
    int width = GetScreenWidth();
    int height = GetScreenHeight();
    // 2. Hide that tiny system cursor
    HideCursor();
    int centerx = width / 4;
    int centery = height / 4;
    Vector2 noPos = {centerx + 100, centery};
    bool accepted = false;

    while (!WindowShouldClose())
    {
        // Use GetMousePosition - it's scaled to the virtual window by default in modern Raylib
        Vector2 mouse = GetMousePosition();

        if (!accepted)
        {
            // Check collision with "No" button
            Rectangle noRect = {noPos.x - 50, noPos.y - 25, 100, 50};

            if (CheckCollisionPointRec(mouse, noRect))
            {
                noPos.x = GetRandomValue(100, GetScreenWidth() - 100);
                noPos.y = GetRandomValue(100, GetScreenHeight() - 100);
            }

            // Check collision with "Yes" button
            if (CheckCollisionPointRec(mouse, (Rectangle){250, 275, 100, 50}))
            {
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    accepted = true;
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText(TextFormat("Mouse X: %f", GetMousePosition().x), 10, 10, 20, BLACK);
        DrawText(TextFormat("Mouse Y: %f", GetMousePosition().y), 10, 30, 20, BLACK);
        DrawText(TextFormat("Window Height: %d", GetScreenHeight()), 10, 50, 20, BLACK);
        DrawText(TextFormat("Window Width: %d", GetScreenWidth()), 10, 70, 20, BLACK);
        DrawText(TextFormat("Render Height: %d", GetRenderHeight()), 10, 90, 20, BLACK);
        DrawText(TextFormat("Render Width: %d", GetRenderWidth()), 10, 110, 20, BLACK);
        if (!accepted)
        {
            DrawText("Will you be my Valentine?", 50, 150, 30, MAROON);
            DrawRectangle(250, 275, 100, 50, PINK);
            DrawText("YES", 280, 290, 20, MAROON);

            DrawRectangle(noPos.x - 50, noPos.y - 25, 100, 50, LIGHTGRAY);
            DrawText("NO", noPos.x - 15, noPos.y - 10, 20, DARKGRAY);
        }
        else
        {
            DrawText("YAY! <3", 350, 200, 40, RED);
        }

        // 3. Draw a CUSTOM CURSOR (A small red circle or heart)
        // This will look the correct size regardless of DPI
        DrawCircleV(mouse, 5, MAROON);
        DrawCircle(mouse.x - 3, mouse.y - 2, 4, RED);
        DrawCircle(mouse.x + 3, mouse.y - 2, 4, RED);

        EndDrawing();
    }
    CloseWindow();
    return 0;
}