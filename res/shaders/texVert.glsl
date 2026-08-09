#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 uv;

layout (location = 3) in vec4 iaModel0;
layout (location = 4) in vec4 iaModel1;
layout (location = 5) in vec4 iaModel2;
layout (location = 6) in vec4 iaModel3;

layout (location = 7) in vec4 iaTexUv;
layout (location = 8) in vec4 iaColor;

uniform float time;
uniform mat4 view;
uniform mat4 projection;

out vec2 texCoord;
out vec4 ourColor;

void main()
{
   mat4 model = mat4(iaModel0, iaModel1, iaModel2, iaModel3);
   gl_Position = projection * model * vec4(aPos, 1.0);

   texCoord = mix(iaTexUv.xy, iaTexUv.zw, uv);
   ourColor = iaColor;
};