#type vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 inColour;

uniform mat4 uViewProjectmatrix;
uniform mat4 uModelMatrix;

out vec3 _position;
out vec4 _colour;

void main()
{
    _colour = inColour;
    _position = position;
    gl_Position = uViewProjectmatrix * uModelMatrix * vec4(_position, 1.0);
}

#type fragment
#version 330 core

layout(location = 0) out vec4 colour;
in vec3 _position;
in vec4 _colour;

void main()
{
    colour = vec4(_position * 0.5 + 0.5, 1.0);
    colour = _colour;
}