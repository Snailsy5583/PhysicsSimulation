#version 330 core

layout (location=0) in vec3 vertPos;
uniform vec3 pos;

void main()
{
    gl_Position = vec4(vertPos + pos, 1);
}