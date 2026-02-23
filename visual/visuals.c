#include "lib.h"
#include <stdlib.h>
#include <string.h>

#define RAYGUI_CUSTOM_ICONS
#include "external/style_dark.h"

// --- RAYLIB BUILT-IN COLORS ---
// LIGHTGRAY, GRAY, DARKGRAY
// YELLOW, GOLD, ORANGE
// PINK, RED, MAROON
// GREEN, LIME, DARKGREEN
// SKYBLUE, BLUE, DARKBLUE
// PURPLE, VIOLET, DARKPURPLE
// BEIGE, BROWN, DARKBROWN
// WHITE, BLACK, BLANK, MAGENTA, RAYWHITE

void Line(Point p1, Point p2, double r, Color color){
    Vector2 start = { (float)p1.x, (float)p1.y };
    Vector2 end = { (float)p2.x, (float)p2.y };

    DrawLineEx(start, end, r, color);
}

void Circle(Point p, int r, Color color){

    DrawCircle(p.x, p.y, r, color);
}

double Length(Point p1, Point p2){
    return sqrt(((p2.x - p1.x) * (p2.x - p1.x)) + ((p2.y - p1.y) * (p2.y - p1.y)));
}

void Init(void){
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT); 

    InitWindow(START_WIDTH, START_HEIGHT, "Pendulum");
    SetTargetFPS(60);

    GuiLoadStyleDark();
}

void DrawPendulum(Pendulum pendulum){
    Circle(pendulum.points.p1, pendulum.data.Mass1 / 5, pendulum.color);
    Circle(pendulum.points.p2, pendulum.data.Mass2 / 5, pendulum.color);

    Line(pendulum.stable, pendulum.points.p1, pendulum.data.Mass1 / 20, pendulum.color);
    Line(pendulum.points.p1, pendulum.points.p2, (pendulum.data.Mass1 + pendulum.data.Mass2) / 40, pendulum.color);
}

void Aftermark(Pendulum pendulum) { 
    Color DarkColor = pendulum.color;
    DarkColor.r = (unsigned char)(DarkColor.r * 0.4f);
    DarkColor.g = (unsigned char)(DarkColor.g * 0.4f);
    DarkColor.b = (unsigned char)(DarkColor.b * 0.4f);

    for (int i = 0; i < maxHistory - 1; i++) {
        Point p1 = { 
            pendulum.history[i].x + pendulum.stable.x, 
            pendulum.history[i].y + pendulum.stable.y 
        };
        Point p2 = { 
            pendulum.history[i + 1].x + pendulum.stable.x, 
            pendulum.history[i + 1].y + pendulum.stable.y 
        };

        int diff = (i - pendulum.count + maxHistory) % maxHistory;
        float intensity = (float)diff / maxHistory;

        Color color = Fade(DarkColor, intensity);

        if (i + 1 != pendulum.count) {
            Line(p1, p2, 1.5, color);
        }
    }
}