#include "lib.h"

double dt = 0.001;
bool showSettings = false;
bool isPaused = false;
bool showAftermark = false;
bool isDarkTheme = false;

int main(void) {
    Pendulum p = InitPendulum1();

    InitScreen();

    InitStable(&p);

    while (!WindowShouldClose()) {
        if (IsWindowResized() || IsKeyPressed(KEY_F11)) {
                InitStable(&p);
        }

        if (isPaused == false){
            UpdateState(&p, dt, showAftermark);
        }

        KeyCheck(&p, &isPaused, &showAftermark, &showSettings);

        Draw(&p);

    }

    CloseWindow();
    return 0;
}