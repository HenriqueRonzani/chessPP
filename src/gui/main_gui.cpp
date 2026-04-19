//
// Created by ronzani on 4/19/26.
//

#include "raylib.h"
#include "chess/Engine.h"
#include "render/Screen.h"

int main () {
    const Screen screen = Screen(1000, 400);
    Engine engine;

    while (!WindowShouldClose()) {
        screen.draw_board(engine.get_board().grid);
    }

    CloseWindow();

    return 0;
}
