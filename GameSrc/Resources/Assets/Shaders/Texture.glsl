#type vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 colour;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in float tilingFactor;
layout(location = 4) in int texIndex;

uniform mat4 uViewProjectmatrix;

out vec2 _texCoord;
out vec4 _colour;
out float _tilingFactor;
flat out int _texIndex;

void main()
{
    _colour = colour;
    _texCoord = texCoord;
    _texIndex = texIndex;
    _tilingFactor = tilingFactor;
    gl_Position = uViewProjectmatrix * vec4(position, 1.0);
}

#type fragment
#version 330 core

layout(location = 0) out vec4 colour;

in vec2 _texCoord;
in vec4 _colour;
in float _tilingFactor;
flat in int _texIndex;

uniform sampler2D uTexture[32];

void main()
{
    colour = texture(uTexture[_texIndex], _texCoord * _tilingFactor) * _colour;
}