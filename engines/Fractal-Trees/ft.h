// Base Grammar :
/*
    F → F[+F][-F]
*/

void DrawBranch(Vector2 start,float length,float angle,float thickness,float ratio,float branch_angle_l,float branch_angle_r,float wind,float baseThickness) {
  if(length < 1) return;

  // wind logic
  float t = thickness/baseThickness;
  float sway = (1.0f - t);
  float windOffset = wind*sway;

  float x_end = start.x + sinf(angle+windOffset)*length;
  float y_end = start.y - cosf(angle+windOffset)*length;
  Vector2 end = {x_end,y_end};

  float new_length = length*ratio;
  float new_thickness = thickness*ratio;
  float new_angle_l = angle + branch_angle_l;
  float new_angle_r = angle - branch_angle_r;
  DrawLineEx(start,end,thickness,RAYWHITE);
  DrawBranch(end,new_length,new_angle_l,new_thickness,ratio,branch_angle_l,branch_angle_r,wind,baseThickness);
  DrawBranch(end,new_length,new_angle_r,new_thickness,ratio,branch_angle_l,branch_angle_r,wind,baseThickness);
}

void DrawBranchColor(Vector2 start,float length,float angle,float thickness,float ratio,float branch_angle_l,float branch_angle_r,float wind,float baseThickness,float pallete) {
  if(length < 1) return;

  // wind logic
  float t = thickness/baseThickness;
  float sway = (1.0f - t);
  float windOffset = wind*sway;

  float x_end = start.x + sinf(angle+windOffset)*length;
  float y_end = start.y - cosf(angle+windOffset)*length;
  Vector2 end = {x_end,y_end};

  float new_length = length*ratio;
  float new_thickness = thickness*ratio;
  float new_angle_l = angle + branch_angle_l;
  float new_angle_r = angle - branch_angle_r;

  // coloring
  float gamma = 1.2f;
  t = powf(t, gamma);

  float contrast = 1.3f;
  t = contrast * (t - 0.5f) + 0.5f;
  if (t < 0) t = 0;
  if (t > 1) t = 1;

  float R = 0.5f + 0.5f*cosf(6.2831f*(t + pallete));
  float G = 0.5f + 0.5f*cosf(6.2831f*(t + pallete + 0.33f));
  float B = 0.5f + 0.5f*cosf(6.2831f*(t + pallete + 0.67f));

  Color branchColor = {
    (unsigned char)(255*R),
    (unsigned char)(255*G),
    (unsigned char)(255*B),
    255
  };

  DrawLineEx(start,end,thickness,branchColor);
  DrawBranchColor(end,new_length,new_angle_l,new_thickness,ratio,branch_angle_l,branch_angle_r,wind,baseThickness,pallete);
  DrawBranchColor(end,new_length,new_angle_r,new_thickness,ratio,branch_angle_l,branch_angle_r,wind,baseThickness,pallete);
}

int DrawTree(int l,int w,int h,float *length,float *thickness,float *ratio,float *pallete,float *angleDegL,float *angleDegR,bool *symmetric,bool *wind,bool *color) {

  float time = GetTime();

  float windStrength = 0.15f;
  float windSpeed = 1.5f;

  float windValue = 0.0f;
  if(*wind){
      windValue = sinf(time * windSpeed) * windStrength;
  }

  Vector2 start = {w/2,h-20};
  if(*color){
    DrawBranchColor(start,*length,0,*thickness,*ratio,(*angleDegL)*DEG2RAD,(*angleDegR)*DEG2RAD,windValue,*thickness,*pallete);
  } else{
    DrawBranch(start,*length,0,*thickness,*ratio,(*angleDegL)*DEG2RAD,(*angleDegR)*DEG2RAD,windValue,*thickness);
  }

  GuiCheckBox(
      (Rectangle){120,l+=10,15,15},
      "Symmetry",
      symmetric
  );

  GuiLabel((Rectangle){120, l+=20, 200, 20}, "Tree Parameters");

  GuiSliderBar(
      (Rectangle){60, l+=30, 200, 20},
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

    angleDegR = angleDegL;
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

  if(*color) {
    GuiSliderBar(
      (Rectangle){60, l+=30, 200, 20},
      "Pallete", TextFormat("%.1f", *pallete),
      pallete, 0.0f, 1.0f
    );
  }



  return l;
}