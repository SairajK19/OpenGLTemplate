#version 330 core

out vec4 FragColor;

in vec2 texCoord;
in vec4 ourColor;

uniform float time;
uniform sampler2D ourTexture;

void main()
{
    vec4 texColor = texture(ourTexture, texCoord);
    FragColor = texColor.rgba * ourColor;
}
