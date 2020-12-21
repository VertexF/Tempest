#type vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;

uniform mat4 uViewProjectmatrix;
uniform mat4 uModelMatrix;

out vec2 _texCoord;

void main()
{
    _texCoord = texCoord;
    gl_Position = uViewProjectmatrix * uModelMatrix * vec4(position, 1.0);
}

#type fragment
#version 330 core

layout(location = 0) out vec4 colour;

in vec2 _texCoord;

uniform vec4 uColour;
uniform sampler2D uTexture;

void main()
{
    colour = texture(uTexture, _texCoord) * uColour;
}