#version 330 core

out vec4 FragColor;

in vec4 ourColor;
in vec3 vertPos;

uniform float time;
uniform vec2 resolution;

float random(vec2 uv) {
    return fract(sin(dot(uv.xy, vec2(12.9898, 78.233))) * 43758.5453123);
}

void main()
{
    FragColor = ourColor * abs(sin(time));
}
