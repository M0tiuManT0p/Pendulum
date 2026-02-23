#include "lib.h"

Rectangle PointsToRect(Points p) {
    Rectangle rect;
    rect.x = p.p1.x;
    rect.y = p.p1.y;
    rect.width = p.p2.x - p.p1.x;
    rect.height = p.p2.y - p.p1.y;
    
    return rect;
}

bool DrawSettingsButton(void) {
    int sw = GetScreenWidth();

    float btnSize = 40.0f;
    float margin = 20.0f;

    int iconScale = (sw > 1200) ? 2 : 1; 
    GuiSetIconScale(iconScale);

    Rectangle btnRect = { 
        (float)sw - btnSize - margin,
        margin,
        btnSize,
        btnSize
    };

    bool pressed = GuiLabelButton(btnRect, GuiIconText(142, ""));

    GuiSetIconScale(1);
    
    return pressed;
}
bool SettingsWindow(Pendulum *pendulum, bool *isPaused, bool *showAftermark) {
    float windowWidth = GetScreenWidth() / 3.0f;
    Rectangle windowRect = { GetScreenWidth() - windowWidth, 0, windowWidth, (float)GetScreenHeight() };

    int oldColor = GuiGetStyle(DEFAULT, BACKGROUND_COLOR);

    float currentY = 80;

    static bool editL1 = false, editL2 = false;
    static bool editM1 = false, editM2 = false;
    static bool editG = false, editAir = false;
    static bool editSpeed = false;
    static bool editA1 = false, editA2 = false;
    static bool editV1 = false, editV2 = false;

    float margin = windowRect.width * 0.05f;

    GuiSetStyle(DEFAULT, BACKGROUND_COLOR, ColorToInt(GetColor(0x2c2c2ccc)));

    bool pressed = GuiWindowBox(windowRect, "#198# SETTINGS");

    if (GuiCheckBox((Rectangle){ windowRect.x + margin, currentY, 20, 20 }, "Pause Simulation", isPaused)) {
    }
    
    if (GuiCheckBox((Rectangle){ windowRect.x + (windowRect.width / 2), currentY, 20, 20 }, "Trace", showAftermark)) {
    }

    currentY += 40;

    SliderAndLabel(pendulum, windowRect, &currentY, &editL1, true, 0, 10.0f, 300.0f);
    SliderAndLabel(pendulum, windowRect, &currentY, &editL2, false, 0, 10.0f, 300.0f);

    SliderAndLabel(pendulum, windowRect, &currentY, &editM1, true, 1, 1.0f, 300.0f);
    SliderAndLabel(pendulum, windowRect, &currentY, &editM2, false, 1, 1.0f, 300.0f);

    SliderAndLabel(pendulum, windowRect, &currentY, &editG, false, 2, 0.0f, 20.0f);
    SliderAndLabel(pendulum, windowRect, &currentY, &editAir, false, 3, 0.0f, 1.0f);
    SliderAndLabel(pendulum, windowRect, &currentY, &editSpeed, false, 6, 1.0f, 1000.0f);

    SliderAndLabel(pendulum, windowRect, &currentY, &editA1, true, 4, -180.0f, 180.0f);
    SliderAndLabel(pendulum, windowRect, &currentY, &editA2, false, 4, -180.0f, 180.0f);

    SliderAndLabel(pendulum, windowRect, &currentY, &editV1, true, 5, -100.0f, 100.0f);
    SliderAndLabel(pendulum, windowRect, &currentY, &editV2, false, 5, -100.0f, 100.0f);

    GuiSetStyle(DEFAULT, BACKGROUND_COLOR, oldColor);
    

    return pressed;
}

void SliderAndLabel(Pendulum *pendulum, Rectangle panel, float *startY, bool *editMode, bool isFirst, int data, float minVal, float maxVal) {
    double *targetData = NULL;
    const char *label = "";

    switch (data) {
        case 0: targetData = isFirst ? &pendulum->data.Length1 : &pendulum->data.Length2; label = isFirst ? "Length 1" : "Length 2"; break;
        case 1: targetData = isFirst ? &pendulum->data.Mass1 : &pendulum->data.Mass2; label = isFirst ? "Mass 1" : "Mass 2"; break;
        case 2: targetData = &pendulum->data.g; label = "Gravity"; break;
        case 3: targetData = &pendulum->AirResistance; label = "Air Resist"; break;
        case 4: targetData = isFirst ? &pendulum->state.Angle1 : &pendulum->state.Angle2; label = isFirst ? "Angle 1" : "Angle 2"; break;
        case 5: targetData = isFirst ? &pendulum->state.Velocity1 : &pendulum->state.Velocity2; label = isFirst ? "Velocity 1" : "Velocity 2"; break;
        case 6: targetData = &pendulum->speed; label = "Speed"; break;
        default: targetData = isFirst ? &pendulum->data.Length1 : &pendulum->data.Length2; label = isFirst ? "Length 1" : "Length 2"; break;
    }

    float margin = panel.width * 0.05f;
    float padding = 10.0f;
    float labelWidth = panel.width * 0.30f; 
    
    float remainingWidth = panel.width - labelWidth - (margin * 2) - (padding * 2);
    float sliderWidth = remainingWidth * 0.70f;
    float valueBoxWidth = remainingWidth * 0.30f;

    GuiLabel((Rectangle){ panel.x + margin, *startY, labelWidth, 20 }, label);

    float displayVal = (data == 4) ? (float)Degrees(*targetData) : (float)(*targetData);
    
    float fData = displayVal;
    int iData = (int)displayVal;

    float sliderX = panel.x + margin + labelWidth + padding;
    GuiSlider((Rectangle){ sliderX, *startY, sliderWidth, 20 }, NULL, NULL, &fData, minVal, maxVal);

    float boxX = sliderX + sliderWidth + padding;
    if (GuiValueBox((Rectangle){ boxX, *startY, valueBoxWidth, 20 }, NULL, &iData, (int)minVal, (int)maxVal, *editMode)) {
        *editMode = !(*editMode);
    }

    if (fData != displayVal) {
        *targetData = (data == 4) ? Radians((double)fData) : (double)fData;
        
        pendulum->points = Cords(pendulum->data, pendulum->state, pendulum->stable);
        for (int i = 0; i < maxHistory; i++) {
            pendulum->history[i].x = pendulum->points.p2.x - pendulum->stable.x;
            pendulum->history[i].y = pendulum->points.p2.y - pendulum->stable.y;
        }
    } else if (iData != (int)displayVal) {
        *targetData = (data == 4) ? Radians((double)iData) : (double)iData;
        
        pendulum->points = Cords(pendulum->data, pendulum->state, pendulum->stable);
        for (int i = 0; i < maxHistory; i++) {
            pendulum->history[i].x = pendulum->points.p2.x - pendulum->stable.x;
            pendulum->history[i].y = pendulum->points.p2.y - pendulum->stable.y;
        }
    }

    *startY += panel.height * 0.06f; 
}