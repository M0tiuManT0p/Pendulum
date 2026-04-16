#ifndef LIB_H
#define LIB_H

#include <stdlib.h>
#include <string.h>
#include "external/raylib.h"
#include "math.h"
#include "structs.h"
#include "raygui.h"



    extern double dt;

    extern bool showSettings;
    extern bool isPaused;
    extern bool showAftermark;
    extern bool isDarkTheme;

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
 * Initializes the window.
 */
void InitScreen(void);

double Radians(double angle);

void KeyCheck(Pendulum *p, bool *isPaused, bool *showAftermark, bool *showSettings);

double Degrees(double angle);

double Square(double number);

void Cords(Pendulum *p);

void AccelerationFunction(Pendulum *p);

double RungeKuttaSwitch(Pendulum p, int data);

double RungeKutta (Pendulum p, double Time, int data);

double AngleWrap(double angle);

void UpdateState(Pendulum *p, double Time, bool showAftermark);

void DrawPendulum(Pendulum pendulum);

Pendulum InitPendulum1(void);

Pendulum InitPendulum2(void);

void Aftermark(Pendulum pendulum);

Pendulum InitPretzel(void);

bool DrawButton(int number);

bool SettingsWindow(Pendulum *pendulum, bool *isPaused, bool *showAftermark, bool *isDarkTheme);

void SliderAndLabel(Pendulum *pendulum, Rectangle panel, float *startY, bool *editMode, bool isFirst, int data, float minVal, float maxVal);

void InitStable(Pendulum *p);

bool DrawThemeButton(void);

void Draw(Pendulum *p);

void ResetPendulum(Pendulum *p);

bool DrawResetButton(void);

void ApplyPreset(Pendulum *p, int preset);

#endif 