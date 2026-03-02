int DrawJulia(int l,int w,int h,float *cx,float *cy,float *maxit,float *scale,float *pallete,Shader *juliaShader,int *resLoc,int *cLoc,int *scaleLoc,int *iterLoc,int *palLoc,int *colorLoc,bool *color) {
    Vector2 start = {0,0};
    Vector2 end = {(float)w,(float)h};
    Vector2 c = {*cx,*cy};

    SetShaderValue(*juliaShader, *resLoc, &end, SHADER_UNIFORM_VEC2);

    SetShaderValue(*juliaShader, *cLoc, &c, SHADER_UNIFORM_VEC2);

    SetShaderValue(*juliaShader, *scaleLoc, scale, SHADER_UNIFORM_FLOAT);

    SetShaderValue(*juliaShader, *iterLoc, maxit, SHADER_UNIFORM_FLOAT);

    SetShaderValue(*juliaShader, *palLoc, pallete, SHADER_UNIFORM_FLOAT);

    int cfl = *color ? 1 : 0;
    SetShaderValue(*juliaShader, *colorLoc, &cfl, SHADER_UNIFORM_INT);

    BeginShaderMode(*juliaShader);
    DrawRectangle(0, 0, w, h, WHITE);
    EndShaderMode();

    GuiLabel((Rectangle){120,l+=30, 200, 20}, "Julia Parameters");

    GuiSliderBar(
        (Rectangle){60, l+=30, 200, 20},
        "Iterations", TextFormat("%.2f", *maxit),
        maxit, 100.0f, 500.0f
    );

    GuiSliderBar(
        (Rectangle){60, l+=30, 200, 20},
        "Scale", TextFormat("%.2f", *scale),
        scale, 0.0001f, 4.0f
    );

    GuiSliderBar(
        (Rectangle){60, l+=30, 200, 20},
        "c-x", TextFormat("%.2f", *cx),
        cx, -1.5f, 1.5f
    );

    GuiSliderBar(
        (Rectangle){60, l+=30, 200, 20},
        "c-y", TextFormat("%.2f", *cy),
        cy, -1.5f, 1.5f
    );

    GuiToggle(
        (Rectangle){60,l+=30,200,20},
        "Color Gradient",
        color
    );

    if(*color) {
        GuiSliderBar(
        (Rectangle){60, l+=30, 200, 20},
        "Pallete", TextFormat("%.1f", *pallete),
        pallete, 0.0f, 1.0f
        );
    }

    return l;
}