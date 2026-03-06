void DrawLeaf(Vector2 screenStart, float scale, int maxt)
{
    Vector2 p = { 0.0f, 0.0f };
    for (int i = 0; i < maxt; i++)
    {
        float xn, yn;
        float x = p.x;
        float y = p.y;
        float r = GetRandomValue(0, 10000) / 10000.0f;

        if (r < 0.01f) {
            xn = 0.0f;
            yn = 0.16f * y;
        }
        else if (r < 0.86f) {
            xn = 0.85f * x + 0.04f * y;
            yn = -0.04f * x + 0.85f * y + 1.6f;
        }
        else if (r < 0.93f) {
            xn = 0.20f * x - 0.26f * y;
            yn = 0.23f * x + 0.22f * y + 1.6f;
        }
        else {
            xn = -0.15f * x + 0.28f * y;
            yn = 0.26f * x + 0.24f * y + 0.44f;
        }

        // leaf space => screen space
        Vector2 screen = {
            screenStart.x + xn  * scale,
            screenStart.y - yn * scale
        };

        DrawPixelV(screen, RAYWHITE);
        p.x = xn;
        p.y = yn;
    }
}

void DrawLeafColor(Vector2 screenStart, float scale, int maxt,float pallete)
{
    Vector2 p = { 0.0f, 0.0f };
    for (int i = 0; i < maxt; i++)
    {
        float xn, yn;
        float x = p.x;
        float y = p.y;
        float r = GetRandomValue(0, 10000) / 10000.0f;

        if (r < 0.01f) {
            xn = 0.0f;
            yn = 0.16f * y;
        }
        else if (r < 0.86f) {
            xn = 0.85f * x + 0.04f * y;
            yn = -0.04f * x + 0.85f * y + 1.6f;
        }
        else if (r < 0.93f) {
            xn = 0.20f * x - 0.26f * y;
            yn = 0.23f * x + 0.22f * y + 1.6f;
        }
        else {
            xn = -0.15f * x + 0.28f * y;
            yn = 0.26f * x +
             0.24f * y + 0.44f;
        }

        // leaf space => screen space
        Vector2 screen = {
            screenStart.x + xn  * scale,
            screenStart.y - yn * scale
        };

        float t = yn / 10.0f;
        t = fmaxf(0.0f, fminf(1.0f, t));

        float R = 0.5f + 0.5f*cosf(6.2831f*(t + pallete));
        float G = 0.5f + 0.5f*cosf(6.2831f*(t + pallete + 0.33f));
        float B = 0.5f + 0.5f*cosf(6.2831f*(t + pallete + 0.67f));

        Color leafColor = {
            (unsigned char)(255*R),
            (unsigned char)(255*G),
            (unsigned char)(255*B),
            255
        };

        DrawPixelV(screen, leafColor);

        DrawPixelV(screen, leafColor);
        p.x = xn;
        p.y = yn;
    }
}

int DrawFern(int l,int w,int h,float *t,float *scale,float *pallete,bool *color) {
    Vector2 start = {w/2,h-20};

    if(*color){
        DrawLeafColor(start,*scale,*t,*pallete);
    } else {
        DrawLeaf(start,*scale,*t);
    }


    GuiLabel((Rectangle){120,l+=30, 200, 20}, "Fern Parameters");

    GuiSliderBar(
        (Rectangle){60, l+=30, 200, 20},
        "Iterations", TextFormat("%.2f", *t),
        t, 100.0f, 50000.0f
    );

    GuiSliderBar(
        (Rectangle){60, l+=30, 200, 20},
        "Scale", TextFormat("%.2f", *scale),
        scale, 10.0f, 200.0f
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