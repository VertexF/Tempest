#type vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;

uniform mat4 uViewProjectmatrix;
uniform mat4 uModelMatrix;

out vec2 _texCoord;
out vec2 _screenPos;

void main()
{
    _texCoord = texCoord;
    gl_Position = uViewProjectmatrix * uModelMatrix * vec4(position, 1.0);
    _screenPos = gl_Position.xy;
}

#type fragment
#version 330 core

layout(location = 0) out vec4 colour;

in vec2 _texCoord;
in vec2 _screenPos;

uniform vec4 uColour;
uniform float uTileFactor;
uniform sampler2D uTexture;

void main()
{
    float dist = 1.0f - distance(_screenPos * 0.8f, vec2(0.0f));
    dist = clamp(dist, 0.0f, 1.0f);
    dist = sqrt(dist);
    colour = texture(uTexture, _texCoord * uTileFactor) * uColour * dist;
}