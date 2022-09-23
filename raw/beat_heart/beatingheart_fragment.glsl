#version 330 core
precision highp float;
layout(location = 0) out vec4 outColor;
uniform float u_time;
uniform vec2 u_screenSize;
uniform sampler2D s_TextureMap;

void main() {
    vec2 fragCoord = gl_FragCoord.xy;
    vec2 p = (2.0 * fragCoord - u_screenSize.xy) / min(u_screenSize.y, u_screenSize.x);

    vec2 uv = fragCoord / u_screenSize;
    vec3 bcol = vec3(1.0, 0.8, 0.8) * (1.0 - 0.38 * length(p));

    // background color
    float tt = u_time;
    float ss = pow(tt, .2) * 0.5 + 0.5;
    ss = 1.0 + ss * 0.5 * sin(tt * 6.2831 * 3.0 + p.y * 0.5) * exp(-tt * 4.0);
    p *= vec2(0.5, 1.5) + ss * vec2(0.5, -0.5);

    // shape
    #if 0
    p *= 0.8;
    p.y = -0.1 - p.y * 1.2 + abs(p.x) * (1.0 - abs(p.x));
    float r = length(p);
    float d = 0.5;
    #else
    p.y -= 0.25;
    float a = atan(p.x, p.y) / 3.141592653;
    float r = length(p);
    float h = abs(a);
    float d = (13.0 * h - 22.0 * h * h + 10.0 * h * h * h) / (6.0 - 5.0 * h);
    #endif

    // color
    float s = 0.75 + 0.75 * p.x;
    s *= 1.0 - 0.4 * r;
    s = 0.3 + 0.7 * s;
    s *= 0.5 + 0.5 * pow(1.0 - clamp(r / d, 0.0, 1.0), 0.1);
    vec3 hcol = vec3(1.0, 0.5 * r, 0.3) * s;
    vec3 col = mix(bcol, hcol, smoothstep(-0.06, 0.06, d - r));

    outColor = vec4(col, 1.0);
}