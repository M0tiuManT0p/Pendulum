#include "lib.h"

int main(void) {
    Pendulum pendulum1 = InitPendulum1();

    Init();

    double dt = 0.001;

    bool showSettings = false;
    bool isPaused = false;
    bool showAftermark = false;

    pendulum1.stable.x = GetScreenWidth() / 2;
    pendulum1.stable.y = GetScreenHeight() / 3; 

    while (!WindowShouldClose()) {
        if (IsWindowResized() || IsKeyPressed(KEY_F11)) {
                pendulum1.stable.x = GetScreenWidth() / 2;
                pendulum1.stable.y = GetScreenHeight() / 3;
        }
        if (isPaused == false){
            for (int i = 0; i < pendulum1.speed; i++) {
            pendulum1.state = UpdateState(pendulum1.data, pendulum1.state, dt, pendulum1.AirResistance);
            }

            pendulum1.points = Cords(pendulum1.data, pendulum1.state, pendulum1.stable);


            if (showAftermark == true) {

            pendulum1.history[pendulum1.count].x = pendulum1.points.p2.x - pendulum1.stable.x;
            pendulum1.history[pendulum1.count].y = pendulum1.points.p2.y - pendulum1.stable.y;

            pendulum1.count++;

            pendulum1.count = pendulum1.count %maxHistory;

            }
        }

        if (IsKeyPressed(KEY_F11)) {
            ToggleFullscreen();
        }

        if (IsKeyPressed(KEY_ESCAPE)) {
            CloseWindow();
        }

        if (IsKeyPressed(KEY_P)) {
            isPaused = !isPaused;
        }

        if (IsKeyPressed(KEY_S)) {
            showSettings = !showSettings;
        }


        BeginDrawing();

        ClearBackground(BLACK);

        if (showAftermark == true) {
            Aftermark(pendulum1);
        }

        DrawPendulum(pendulum1);

        if (showSettings == false) {
            if (DrawSettingsButton() == true) {
                showSettings = !showSettings; 
            }
        }

        if (showSettings) {

            if (SettingsWindow(&pendulum1, &isPaused, &showAftermark) == true) {
                showSettings = false;
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}