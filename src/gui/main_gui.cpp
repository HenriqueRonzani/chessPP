//
// Created by ronzani on 4/19/26.
//

#include "../../cmake-build-debug/_deps/raylib-src/src/raylib.h"

int main () {
    constexpr int screenWidth = 400;
    constexpr int screenHeight = 400;

    InitWindow(screenWidth, screenHeight, "Cchess GUI");

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
