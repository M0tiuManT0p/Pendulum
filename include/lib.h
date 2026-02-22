#ifndef LIB_H
#define LIB_H

#include "raylib.h"
#include "math.h"
#include "structs.h"
#include "raygui.h"

/**
 * Draws a line between 2 points.
 * 
 * @param p1 First point.
 * @param p2 Second point.
 * @param r The thickness of the line.
 */
void Line(Point p1, Point p2, double r, Color color);

/**
 * Draws a circle by cords.
 * 
 * @param p Point.
 * @param r Radius.
 */
void Circle(Point p, int r, Color color);

/**
 * Calulates the distance between 2 points.
 * 
 * @param p1 First point.
 * @param p2 Second point.
 */
double Length(Point p1, Point p2);

/**
 * Initializes the monitor.
 */
void Init(void);

double Radians(double angle);

double Square(double number);

Points Cords(StartingData Data, State State, Point stable);

Acceleration AccelerationFunction(StartingData Data, State State);

State UpdateState(StartingData Data, State State, double Time);

void DrawPendulum(Pendulum pendulum, Color color);

Pendulum InitPendulum1(void);

Pendulum InitPendulum2(void);

void Aftermark(Pendulum pendulum);

Pendulum InitPretzel(void);

bool DrawSettingsButton(void);

bool SettingsWindow(void);

#endif 