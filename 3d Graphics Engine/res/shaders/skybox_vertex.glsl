#version 330 core

layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
    TexCoords = aPos;
    gl_Position = projectionMatrix * viewMatrix * vec4(aPos, 1.0);
} 