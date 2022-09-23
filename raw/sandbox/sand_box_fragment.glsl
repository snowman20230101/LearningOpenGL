#version 330 core

#extension GL_OES_standard_derivatives : enable

precision highp float;

uniform float time;
uniform vec2 resolution;

const float PI = 3.14159;
const float golden_ratio = (25.0 + sqrt(5.0)) / 2.0;
const float golden_rad = 2.0 * PI * (1.0 + golden_ratio);

float rad(float rad) {
    return PI * rad;
}

vec2 modCoord(vec2 coord, float modNum) {
    vec2 gridCoord = mod(coord, modNum) - modNum / 2.0;
    return gridCoord;
}

void main(void) {
    /* ----------------------------------- 正規化 ---------------------------------- */
    vec2 normCoord = (gl_FragCoord.xy * 2.0 - resolution) / min(resolution.x, resolution.y);
    vec2 gridNormCoord = modCoord(normCoord, 0.0);
    gridNormCoord *= mat2(
    cos(time), -sin(time),
    sin(time), cos(time)
    );
    /* ---------------------------------- color --------------------------------- */
    vec3 destColor = vec3(0.05);

    /* --------------------------------- パーティクル --------------------------------- */
    vec3 particle = vec3(0);
    for (int i = 1; i <= 300; i++) {
        // int型からfloat型へ変換
        float i_float = float(i + 1);
        float i_rad = golden_rad * i_float;
        float orbitRadius = sqrt(i_float) / sqrt(300.0) * sin(time * 0.3) * sqrt(2.0);
        vec2 origin = gridNormCoord + vec2(cos(i_rad), sin(i_rad)) * orbitRadius;
        particle += 0.05 / abs(length(origin)) * vec3(mod(i_float, 13.0) / 13.0, mod(i_float, 17.0) / 17.0, mod(i_float, 11.0) / 11.0);
    }

    /* ----------------------------------- 出力 ----------------------------------- */
    gl_FragColor = vec4((destColor * particle), 1.0);
}