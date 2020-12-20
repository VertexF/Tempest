#type vertex
#version 330 core

layout(location = 0) in vec3 position;

uniform mat4 uViewProjectmatrix;
uniform mat4 uModelMatrix;

void main()
{
    gl_Position = uViewProjectmatrix * uModelMatrix * vec4(position, 1.0);
}

#type fragment
#version 330 core

layout(location = 0) out vec4 colour;

uniform vec4 uColour;

void main()
{
    colour = uColour;
}