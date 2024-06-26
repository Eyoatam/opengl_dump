#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 aTex;

// out vec4 color;
out vec2 TexCoord;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    // color = vec4(aColor, 1.0f);
    gl_Position =  projection * view * model * vec4(aPos, 1.0f);
    TexCoord = aTex;
}
