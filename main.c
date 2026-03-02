#define RAYGUI_IMPLEMENTATION
#include "./engines/raygui.h"
#include <raylib.h>
#include <math.h>
#include <stdio.h>

#include "./engines/Fractal-Trees/ft.h"
#include "./engines/Barnsley-Fern/barnsley.h"
#include "./engines/L-System-Trees/L-system.h"
#include "./engines/Julia-Set/Julia.h"

#define WIDTH 950
#define HEIGHT 650

typedef enum {
    FRACTAL_TREE,
    FRACTAL_BARNSLEY,
    FRACTAL_LSYSTEM,
    FRACTAL_JULIA
} FractalMode;


int main(int argc,char *argv[]) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(WIDTH, HEIGHT, "Fractals Visualiser");

    GuiSetStyle(DEFAULT, BACKGROUND_COLOR, 0x181818FF);
    GuiSetStyle(DEFAULT, BASE_COLOR_NORMAL, 0x2A2A2AFF);
    GuiSetStyle(DEFAULT, BASE_COLOR_FOCUSED, 0x3A3A3AFF);
    GuiSetStyle(DEFAULT, BASE_COLOR_PRESSED, 0x505050FF);
    GuiSetStyle(DEFAULT, BORDER_COLOR_NORMAL, 0x808080FF);
    GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, 0xE0E0E0FF);

    GuiSetStyle(SLIDER, SLIDER_WIDTH, 8);
    GuiSetStyle(SLIDER, BORDER_WIDTH, 1);

    // Tree params
    float length = 250.0f;
    float thickness = 20.0f;
    float ratio = 0.7f;

    // Fern params
    float t = 7000.0f;
    float scale = 50.0f;

    // angles
    bool symmetric = false;
    float angleDegL = 20.0f;
    float angleDegR = 20.0f;

    // pallete
    bool color = false;
    float pallete = 0.0f;

    // wind toggle
    bool wind = false;

    // L - sys randomness
    float branchProbability = 0.7f;

    // Julia's shaders
    Shader juliaShader = LoadShader(0, "./engines/Julia-Set/julia.fs");

    int resLoc = GetShaderLocation(juliaShader, "resolution");
    int cLoc = GetShaderLocation(juliaShader, "c");
    int scaleLoc = GetShaderLocation(juliaShader, "scale");
    int iterLoc = GetShaderLocation(juliaShader, "maxIteration");
    int palLoc = GetShaderLocation(juliaShader, "pallete");
    int colorLoc = GetShaderLocation(juliaShader, "color");

    // Julia params
    float maxit = 200.0f;
    float scalej = 1.0f;
    float cx = -0.7f;
    float cy = 0.27015f;

    // dropdown params
    int curr_index = FRACTAL_TREE;
    bool fractalEdit = false;
    const char * fractalList = "Tree;Fern;L-System;Julia Set";

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {

        int w = GetScreenWidth();
        int h = GetScreenHeight();
        BeginDrawing();
            ClearBackground(BLACK);

            FractalMode curr = (FractalMode)curr_index;

            int l = 0;

            switch (curr)
            {
              case FRACTAL_TREE:
                l = DrawTree(l,w,h,&length,&thickness,&ratio,&pallete,&angleDegL,&angleDegR,&symmetric,&wind,&color);
                break;
              case FRACTAL_BARNSLEY:
                l = DrawFern(l,w,h,&t,&scale,&pallete,&color);
                break;
              case FRACTAL_LSYSTEM:
                l = DrawLSys(l,w,h,&length,&thickness,&ratio,&pallete,&angleDegL,&angleDegR,&branchProbability,&wind,&color,&symmetric);
                break;
              case FRACTAL_JULIA:
                l = DrawJulia(l,w,h,&cx,&cy,&maxit,&scalej,&pallete,&juliaShader,&resLoc,&cLoc,&scaleLoc,&iterLoc,&palLoc,&colorLoc,&color);
                break;
            }

            if(GuiDropdownBox(
                  (Rectangle){60,l+=30,200,20},
                  fractalList,
                  &curr_index,
                  fractalEdit
              )){
                fractalEdit = !fractalEdit;
            }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}