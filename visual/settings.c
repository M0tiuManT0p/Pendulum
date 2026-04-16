#include "lib.h"

Rectangle PointsToRect(Points p) {
    Rectangle rect;
    rect.x = p.p1.x;
    rect.y = p.p1.y;
    rect.width = p.p2.x - p.p1.x;
    rect.height = p.p2.y - p.p1.y;
    
    return rect;
}

bool DrawButton(int number) {
    int sw = GetScreenWidth();

    float iconScale = (float)sw / 600.0f;
    if (iconScale < 1.0f) iconScale = 1.0f; 
    GuiSetIconScale(iconScale);

    float actualBtnSize = 16.0f * iconScale; 
    float margin = 20.0f;

    Rectangle btnRect = { 
        (float)sw - actualBtnSize - margin,
        margin,
        actualBtnSize,
        actualBtnSize
    };

    bool pressed = GuiLabelButton(btnRect, GuiIconText(number, ""));

    GuiSetIconScale(1);
    
    return pressed;
}

bool DrawResetButton(void) {
    int sw = GetScreenWidth();

    float iconScale = (float)sw / 600.0f;
    if (iconScale < 1.0f) iconScale = 1.0f; 
    GuiSetIconScale(iconScale);

    float actualBtnSize = 16.0f * iconScale; 
    float margin = 20.0f;
    float spacing = 10.0f; 

    Rectangle btnRect = { 
        (float)sw - (actualBtnSize * 2) - margin - spacing,
        margin,
        actualBtnSize,
        actualBtnSize
    };

    bool pressed = GuiLabelButton(btnRect, GuiIconText(75, ""));

    GuiSetIconScale(1);
    
    return pressed;
}

void KeyCheck(Pendulum *p, bool *isPaused, bool *showAftermark, bool *showSettings) {
    if (IsKeyPressed(KEY_F11)) {
        ToggleFullscreen();
    }

    if (IsKeyPressed(KEY_ESCAPE)) {
        CloseWindow();
    }

    if (IsKeyPressed(KEY_P)) {
        *isPaused = !(*isPaused);
    }

    if (IsKeyPressed(KEY_A)) {
        *showAftermark = !(*showAftermark);
    }

    if (IsKeyPressed(KEY_S)) {
        *showSettings = !(*showSettings);
    }
    
    if (IsKeyPressed(KEY_R)) {
        ResetPendulum(p);
    }
}

bool SettingsWindow(Pendulum *pendulum, bool *isPaused, bool *showAftermark, bool *isDarkTheme) {
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

    Color panelColor = *isDarkTheme ? GetColor(0x2c2c2ccc) : GetColor(0xc8c8c8cc);
    DrawRectangleRec(windowRect, panelColor);

    bool pressed = DrawButton(113);

    if (GuiCheckBox((Rectangle){ windowRect.x + margin, currentY, 20, 20 }, "Pause Simulation", isPaused)) {
    }
    
    if (GuiCheckBox((Rectangle){ windowRect.x + (windowRect.width / 2), currentY, 20, 20 }, "Trace", showAftermark)) {
    }
    
    currentY += 40;

    float btnWidth = (windowRect.width - (margin * 3)) / 2.0f;
    if (GuiButton((Rectangle){ windowRect.x + margin, currentY, btnWidth, 20 }, "Pretzel")) {
        ApplyPreset(pendulum, 1);
    }
    if (GuiButton((Rectangle){ windowRect.x + margin * 2 + btnWidth, currentY, btnWidth, 20 }, "Small Angle")) {
        ApplyPreset(pendulum, 2);
    }
    currentY += 25;
    if (GuiButton((Rectangle){ windowRect.x + margin, currentY, btnWidth, 20 }, "In-Phase")) {
        ApplyPreset(pendulum, 3);
    }
    if (GuiButton((Rectangle){ windowRect.x + margin * 2 + btnWidth, currentY, btnWidth, 20 }, "Anti-Phase")) {
        ApplyPreset(pendulum, 4);
    }
    currentY += 35;

    SliderAndLabel(pendulum, windowRect, &currentY, &editL1, true, 0, 10.0f, 300.0f);
    SliderAndLabel(pendulum, windowRect, &currentY, &editL2, false, 0, 10.0f, 300.0f);
    SliderAndLabel(pendulum, windowRect, &currentY, &editM1, true, 1, 1.0f, 300.0f);
    SliderAndLabel(pendulum, windowRect, &currentY, &editM2, false, 1, 1.0f, 300.0f);
    SliderAndLabel(pendulum, windowRect, &currentY, &editG, false, 2, 0.0f, 100.0f);
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

    int textMin = *editMode ? -99999 : (int)minVal;
    int textMax = *editMode ? 99999 : (int)maxVal;

    if (GuiValueBox((Rectangle){ boxX, *startY, valueBoxWidth, 20 }, NULL, &iData, textMin, textMax, *editMode)) {
        *editMode = !(*editMode);
    }

    if (fData != displayVal) {
        *targetData = (data == 4) ? Radians((double)fData) : (double)fData;
        
        Cords(pendulum);
        for (int i = 0; i < maxHistory; i++) {
            pendulum->history[i].x = pendulum->points.p2.x - pendulum->stable.x;
            pendulum->history[i].y = pendulum->points.p2.y - pendulum->stable.y;
        }
    } else if (iData != (int)displayVal) {

        if (iData >= (int)minVal && iData <= (int)maxVal) {
            *targetData = (data == 4) ? Radians((double)iData) : (double)iData;
            
            Cords(pendulum);
            for (int i = 0; i < maxHistory; i++) {
                pendulum->history[i].x = pendulum->points.p2.x - pendulum->stable.x;
                pendulum->history[i].y = pendulum->points.p2.y - pendulum->stable.y;
            }
        }
    }

    *startY += panel.height * 0.06f; 
}

bool DrawThemeButton(void) {
    int sw = GetScreenWidth();

    float iconScale = (float)sw / 600.0f;
    if (iconScale < 1.0f) iconScale = 1.0f; 
    GuiSetIconScale(iconScale);

    float actualBtnSize = 16.0f * iconScale; 
    float margin = 20.0f;

    Rectangle btnRect = { 
        margin,
        margin,
        actualBtnSize,
        actualBtnSize
    };

    bool pressed = GuiLabelButton(btnRect, GuiIconText(223, ""));

    GuiSetIconScale(1);
    
    return pressed;
}