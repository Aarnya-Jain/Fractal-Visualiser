// Base Grammar Used :
/*
    S -> FB
    F -> FF
    B -> [lFB][rFB] | FB
*/

Vector2 DrawF(Vector2 start,float length,float angle,float thickness,float wind,float baseThickness) {

  float t = thickness/baseThickness;
  float sway = (1.0f - t);
  float windOffset = wind*sway;

  float x_mid = start.x + sinf(angle+windOffset)*length;
  float y_mid = start.y - cosf(angle+windOffset)*length;
  Vector2 mid = {x_mid,y_mid};

  float x_end = mid.x + sinf(angle+windOffset)*length;
  float y_end = mid.y - cosf(angle+windOffset)*length;
  Vector2 end = {x_end,y_end};

  DrawLineEx(start,mid,thickness,RAYWHITE);
  DrawLineEx(mid,end,thickness,RAYWHITE);
  return end;
}

Vector2 DrawFColor(Vector2 start,float length,float angle,float thickness,float wind,float baseThickness,float pallete) {

  float t = thickness/baseThickness;
  float sway = (1.0f - t);
  float windOffset = wind*sway;

  float x_mid = start.x + sinf(angle+windOffset)*length;
  float y_mid = start.y - cosf(angle+windOffset)*length;
  Vector2 mid = {x_mid,y_mid};

  float x_end = mid.x + sinf(angle+windOffset)*length;
  float y_end = mid.y - cosf(angle+windOffset)*length;
  Vector2 end = {x_end,y_end};

  float gamma = 1.2f;
  t = powf(t, gamma);

  float contrast = 1.3f;
  t = contrast * (t - 0.5f) + 0.5f;
  if (t < 0) t = 0;
  if (t > 1) t = 1;

  float R = 0.5f + 0.5f*cosf(6.2831f*(t + pallete));
  float G = 0.5f + 0.5f*cosf(6.2831f*(t + pallete + 0.33f));
  float B = 0.5f + 0.5f*cosf(6.2831f*(t + pallete + 0.67f));

  Color color = {
    (unsigned char)(255*R),
    (unsigned char)(255*G),
    (unsigned char)(255*B),
    255
  };

  DrawLineEx(start,mid,thickness,color);
  DrawLineEx(mid,end,thickness,color);
  return end;
}

void DrawB(Vector2 start,float length,float angle,float thickness,float ratio,float branch_angle_l,float branch_angle_r,float wind,float baseThickness,float branchProb) {
  if(length < 1) return;

  float new_length = length*ratio;
  float new_thickness = thickness*ratio;

  float r = (float)rand() / RAND_MAX;

  if(r <= branchProb) {
    // lFB
    float new_angle_l = angle + branch_angle_l;
    Vector2 leftEnd = DrawF(start,length,new_angle_l,thickness,wind,baseThickness);
    DrawB(leftEnd,new_length,new_angle_l,new_thickness,ratio,branch_angle_l,branch_angle_r,wind,baseThickness,branchProb);

    // rFB
    float new_angle_r = angle - branch_angle_r;
    Vector2 RightEnd = DrawF(start,length,new_angle_r,thickness,wind,baseThickness);
    DrawB(RightEnd,new_length,new_angle_r,new_thickness,ratio,branch_angle_l,branch_angle_r,wind,baseThickness,branchProb);
  } else{
    Vector2 end = DrawF(start,length,angle,thickness,wind,baseThickness);
    DrawB(end,new_length,angle,new_thickness,ratio,branch_angle_l,branch_angle_r,wind,baseThickness,branchProb);
  }

}

void DrawBColor(Vector2 start,float length,float angle,float thickness,float ratio,float branch_angle_l,float branch_angle_r,float wind,float baseThickness,float branchProb,float pallete) {
  if(length < 1) return;

  float new_length = length*ratio;
  float new_thickness = thickness*ratio;

  float r = (float)rand() / RAND_MAX;

  if(r <= branchProb) {
    // lFB
    float new_angle_l = angle + branch_angle_l;
    Vector2 leftEnd = DrawFColor(start,length,new_angle_l,thickness,wind,baseThickness,pallete);
    DrawBColor(leftEnd,new_length,new_angle_l,new_thickness,ratio,branch_angle_l,branch_angle_r,wind,baseThickness,branchProb,pallete);

    // rFB
    float new_angle_r = angle - branch_angle_r;
    Vector2 RightEnd = DrawFColor(start,length,new_angle_r,thickness,wind,baseThickness,pallete);
    DrawBColor(RightEnd,new_length,new_angle_r,new_thickness,ratio,branch_angle_l,branch_angle_r,wind,baseThickness,branchProb,pallete);
  } else{
    Vector2 end = DrawFColor(start,length,angle,thickness,wind,baseThickness,pallete);
    DrawBColor(end,new_length,angle,new_thickness,ratio,branch_angle_l,branch_angle_r,wind,baseThickness,branchProb,pallete);
  }

}

void Draw(Vector2 start,float length,float angle,float thickness,float ratio,float branch_angle_l,float branch_angle_r,float wind,float baseThickness,float branchProb) {

  Vector2 end = DrawF(start,length,angle,thickness,wind,baseThickness);

  float new_length = length*ratio;
  float new_thickness = thickness*ratio;
  DrawB(end,new_length,angle,new_thickness,ratio,branch_angle_l,branch_angle_r,wind,baseThickness,branchProb);
}

void DrawColor(Vector2 start,float length,float angle,float thickness,float ratio,float branch_angle_l,float branch_angle_r,float wind,float baseThickness,float branchProb,float pallete) {

  Vector2 end = DrawFColor(start,length,angle,thickness,wind,baseThickness,pallete);

  float new_length = length*ratio;
  float new_thickness = thickness*ratio;
  DrawBColor(end,new_length,angle,new_thickness,ratio,branch_angle_l,branch_angle_r,wind,baseThickness,branchProb,pallete);
}

int DrawLSys(int l,int w,int h,float *length,float *thickness,float *ratio,float *pallete,float * angleDegL,float * angleDegR,float *branchProbability,bool *wind,bool *color,bool *symmetric){
  GuiCheckBox(
      (Rectangle){120,l+=10,15,15},
      "Symmetry",
      symmetric
  );

  GuiLabel((Rectangle){120, l+=20, 200, 20}, "L - Sys Parameters");

  GuiSliderBar(
      (Rectangle){60, l+=20, 200, 20},
      "Length", TextFormat("%.1f", *length),
      length, 50.0f, 500.0f
  );

  GuiSliderBar(
      (Rectangle){60, l+=30, 200, 20},
      "Thickness", TextFormat("%.1f", *thickness),
      thickness, 1.0f, 50.0f
  );

  GuiSliderBar(
      (Rectangle){60, l+=30, 200, 20},
      "Ratio", TextFormat("%.2f", *ratio),
      ratio, 0.5f, 0.75f
  );

  if(*symmetric) {
    GuiSliderBar(
        (Rectangle){60, l+=30, 200, 20},
        "Angle", TextFormat("%.1f", *angleDegL),
        angleDegL, 0.0f, 180.0f
    );

    *angleDegR = *angleDegL;
  }

  else{
    GuiSliderBar(
        (Rectangle){60, l+=30, 200, 20},
        "L - Angle", TextFormat("%.1f", *angleDegL),
        angleDegL, 0.0f, 180.0f
    );

    GuiSliderBar(
        (Rectangle){60, l+=30, 200, 20},
        "R - Angle", TextFormat("%.1f", *angleDegR),
        angleDegR, 0.0f, 180.0f
    );
  }

  GuiSliderBar(
      (Rectangle){60, l+=30, 200, 20},
      "Branch %",
      TextFormat("%.0f%%", *branchProbability * 100),
      branchProbability,
      0.0f, 1.0f
  );

  GuiToggle(
        (Rectangle){60,l+=30,200,20},
        "Wind",
        wind
  );

  GuiToggle(
        (Rectangle){60,l+=30,200,20},
        "Color Gradient",
        color
  );

  if(*color){
    GuiSliderBar(
        (Rectangle){60, l+=30, 200, 20},
        "Pallete", TextFormat("%.1f", *pallete),
        pallete, 0.0f, 1.0f
    );
  }

  float time = GetTime();

  float windStrength = 0.15f;
  float windSpeed = 1.5f;

  float windValue = 0.0f;
  if(*wind){
      windValue = sinf(time * windSpeed) * windStrength;
  }

  Vector2 start = {w/2,h-20};
  srand(42);
  if(*color){
    DrawColor(start,*length,0,*thickness,*ratio,(*angleDegL)*DEG2RAD,(*angleDegR)*DEG2RAD,windValue,*thickness,*branchProbability,*pallete);
  } else {
    Draw(start,*length,0,*thickness,*ratio,(*angleDegL)*DEG2RAD,(*angleDegR)*DEG2RAD,windValue,*thickness,*branchProbability);
  }

  return l;
}