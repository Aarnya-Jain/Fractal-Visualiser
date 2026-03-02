#version 330

out vec4 finalColor;

uniform vec2 resolution;
uniform vec2 c;
uniform float scale;
uniform float maxIteration;
uniform float pallete;
uniform int color;

void main()
{
    float zx = (gl_FragCoord.x / resolution.x) * 2.0 - 1.0;
    float zy = (gl_FragCoord.y / resolution.y) * 2.0 - 1.0;

    float aspect = resolution.x / resolution.y;
    zx *= aspect;

    zx *= scale;
    zy *= scale;

    int i = 0;

    while (zx*zx + zy*zy < 4.0 && i < int(maxIteration)) {
        float xtemp = zx*zx - zy*zy + c.x;
        zy = 2.0*zx*zy + c.y;
        zx = xtemp;
        i++;
    }

    if (i == int(maxIteration)) {
        finalColor = vec4(0.0,0.0,0.0,1.0);
    } else {
        if(color != 0){
            float mag = zx*zx + zy*zy;
            mag = max(mag, 1.0001);

            float smoothIter = float(i) - log2(log2(mag));
            float t = smoothIter / maxIteration;

            t = clamp(t, 0.0, 1.0);

            vec3 color = vec3(
                0.5 + 0.5*cos(6.2831*(t + pallete + 0.0)),
                0.5 + 0.5*cos(6.2831*(t + pallete + 0.33)),
                0.5 + 0.5*cos(6.2831*(t + pallete + 0.67))
            );

            finalColor = vec4(color, 1.0);

        } else {
            finalColor = vec4(1.0,1.0,1.0,1.0);
        }
    }

}