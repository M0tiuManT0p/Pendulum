#include "lib.h"

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

void Circle(Point p,int r, Color color){

    DrawCircle(p.x, p.y, r, color);
}

double Length(Point p1, Point p2){
    return sqrt(((p2.x - p1.x) * (p2.x - p1.x)) + ((p2.y - p1.y) * (p2.y - p1.y)));
}

void Init(void){
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitWindow(START_WIDTH, START_HEIGHT, "RK4 Algorithm Visualization");
    SetTargetFPS(60);

    GuiLoadStyleDark();
}

void DrawPendulum(Pendulum pendulum, Color color){
    Circle(pendulum.stable, 10, color);
    Circle(pendulum.points.p1, 10, color);
    Circle(pendulum.points.p2, 10, color);

    Line(pendulum.stable, pendulum.points.p1, 3.0, color);
    Line(pendulum.points.p1, pendulum.points.p2, 3.0, color);
}

void Aftermark(Pendulum pendulum) {
    for (int i = 0; i < 1000; i++) {
        
        int diff = (i - pendulum.count + 1000) % 1000;
        
        int alpha = (int)((diff / 1000.0) * 255.0);
        
        Color color = (Color){ 255, 255, 255, alpha };
        
        Point p1 = pendulum.history[i];
        Point p2 = pendulum.history[(i + 1) % 1000];
        
        if (p1.x != 0 && p2.x != 0) {
            Line(p1, p2, 1.0, color);
        }
    }
}