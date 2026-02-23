#include "lib.h"

int main(void) {
    Pendulum pendulum1 = InitPendulum1();

    Init();

    int speedMultiplier = 100;
    double dt = 0.001;

    int button = 10;
    bool showSettings = false;

    pendulum1.stable.x = GetScreenWidth() / 2;
    pendulum1.stable.y = GetScreenHeight() / 3;    

    while (!WindowShouldClose()) {
        if (IsWindowResized() || IsKeyPressed(KEY_F11)) {
                pendulum1.stable.x = GetScreenWidth() / 2;
                pendulum1.stable.y = GetScreenHeight() / 3;
        }
        if (showSettings == false){
            for (int i = 0; i < speedMultiplier; i++) {
            pendulum1.state = UpdateState(pendulum1.data, pendulum1.state, dt);
            }

            pendulum1.points = Cords(pendulum1.data, pendulum1.state, pendulum1.stable);

            pendulum1.history[pendulum1.count].x = pendulum1.points.p2.x - pendulum1.stable.x;
            pendulum1.history[pendulum1.count].y = pendulum1.points.p2.y - pendulum1.stable.y;

            pendulum1.count++;

            pendulum1.count = pendulum1.count %maxHistory;
        }

        if (IsKeyPressed(KEY_F11)) {
            ToggleFullscreen();
        }

        BeginDrawing();

        ClearBackground(BLACK);

        Aftermark(pendulum1);

        DrawPendulum(pendulum1, PURPLE);

        DrawText(TextFormat("%i", button), 10, 10, 20, LIGHTGRAY);

        if (showSettings == false) {
            if (DrawSettingsButton() == true) {
                showSettings = !showSettings; 
            }
        }

        if (showSettings) {

            if (SettingsWindow(&pendulum1) == true) {
                showSettings = false;
            }

        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}