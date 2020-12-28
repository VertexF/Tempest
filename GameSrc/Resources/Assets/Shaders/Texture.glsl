#type vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 colour;
layout(location = 2) in vec2 texCoord;

uniform mat4 uViewProjectmatrix;

out vec2 _texCoord;
out vec4 _colour;

void main()
{
    _colour = colour;
    _texCoord = texCoord;
    gl_Position = uViewProjectmatrix * vec4(position, 1.0);
}

#type fragment
#version 330 core

layout(location = 0) out vec4 colour;

in vec2 _texCoord;
in vec4 _colour;

uniform float uTileFactor;
uniform sampler2D uTexture;

void main()
{
    //colour = texture(uTexture, _texCoord * uTileFactor) * _colour;

    colour = _colour;
}