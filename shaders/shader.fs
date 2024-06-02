#version 330 core

out vec4 FragColor;
// uniform vec3 color;
// in vec4 color;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
// uniform int mix_amount;

void main()
{
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.4);
    
} 
