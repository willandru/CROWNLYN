#version 330 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoord;

uniform vec4 uRect;

out vec2 TexCoord;

void main()
{
    vec2 pos = uRect.xy + aPos * uRect.zw;

    gl_Position = vec4(
        pos * 2.0 - 1.0,
        0.0,
        1.0
    );

    TexCoord = aTexCoord;
}