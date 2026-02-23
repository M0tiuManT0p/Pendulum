#ifndef STRUCT_H
#define STRUCT_H

#define START_WIDTH 1280
#define START_HEIGHT 720

#define SCREEN_WIDTH GetScreenWidth()
#define SCREEN_HEIGHT GetScreenHeight()

#define maxHistory 255

typedef struct {
    double x;
    double y;
} Point;

typedef struct {
    Point p1;
    Point p2;
} Points;

typedef struct {
    double Angle1;
    double Angle2;

    double Velocity1;
    double Velocity2;

} State;

typedef struct {
    double Length1;
    double Length2;

    double Mass1;
    double Mass2;

    double g;

} StartingData;

typedef struct {
    double Acceleration1;
    double Acceleration2;

} Acceleration;

typedef struct {
    Points points;
    StartingData data;
    State state;
    Point stable;
    Point history[1000];
    int count;
} Pendulum;

#endif 