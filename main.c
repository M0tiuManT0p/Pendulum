#include "lib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "style_dark.h"

int main(void) {
    Pendulum pendulum1 = InitPendulum1();

    Init();

    int speedMultiplier = 100;
    double dt = 0.001;

    int button = 10;
    bool showSettings = false;    

    while (!WindowShouldClose()) {
        if (showSettings == false){
            for (int i = 0; i < speedMultiplier; i++) {
            pendulum1.state = UpdateState(pendulum1.data, pendulum1.state, dt);
            }

            pendulum1.points = Cords(pendulum1.data, pendulum1.state, pendulum1.stable);

            pendulum1.history[pendulum1.count] = pendulum1.points.p2;
        }

        BeginDrawing();

        ClearBackground(BLACK);
        if (showSettings == false){
            for (int i = 0; i < speedMultiplier; i++) {
            pendulum1.state = UpdateState(pendulum1.data, pendulum1.state, dt);
            }
        }
        Aftermark(pendulum1);

        DrawPendulum(pendulum1, PURPLE);

        DrawText(TextFormat("%i", button), 10, 10, 20, LIGHTGRAY);

        if (DrawSettingsButton() == true) {
            showSettings = !showSettings; 
        }

        if (showSettings) {

            if (SettingsWindow() == true) {
                showSettings = false;
            }

        }

        EndDrawing();

        pendulum1.count++;

        pendulum1.count = pendulum1.count %1000;
    }

    CloseWindow();
    return 0;
}