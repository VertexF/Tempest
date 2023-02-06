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
    //colour = texture(uTexture[_texIndex], _texCoord * _tilingFactor) * _colour;
    vec4 texColour = _colour;
    switch(_texIndex)
    {
        case 0: texColour *= texture(uTexture[_texIndex], _texCoord * _tilingFactor); break;
        case 1: texColour *= texture(uTexture[_texIndex], _texCoord * _tilingFactor); break;
        case 2: texColour *= texture(uTexture[_texIndex], _texCoord * _tilingFactor); break;
        case 3: texColour *= texture(uTexture[_texIndex], _texCoord * _tilingFactor); break;
        case 4: texColour *= texture(uTexture[_texIndex], _texCoord * _tilingFactor); break;
        case 5: texColour *= texture(uTexture[_texIndex], _texCoord * _tilingFactor); break;
        case 6: texColour *= texture(uTexture[_texIndex], _texCoord * _tilingFactor); break;
        case 7: texColour *= texture(uTexture[_texIndex], _texCoord * _tilingFactor); break;
        case 8: texColour *= texture(uTexture[_texIndex], _texCoord * _tilingFactor); break;
        case 9: texColour *= texture(uTexture[_texIndex], _texCoord * _tilingFactor); break;
        case 10: texColour *= texture(uTexture[_texIndex], _texCoord * _tilingFactor); break;
        case 11: texColour *= texture(uTexture[_texIndex], _texCoord * _tilingFactor); break;
        case 12: texColour *= texture(uTexture[_texIndex], _texCoord * _tilingFactor); break;
        case 13: texColour *= texture(uTexture[_texIndex], _texCoord * _tilingFactor); break;
        case 14: texColour *= texture(uTexture[_texIndex], _texCoord * _tilingFactor); break;
        case 15: texColour *= texture(uTexture[_texIndex], _texCoord * _tilingFactor); break;
        case 16: texColour *= texture(uTexture[_texIndex], _texCoord * _tilingFactor); break;
        case 17: texColour *= texture(uTexture[_texIndex], _texCoord * _tilingFactor); break;
        case 18: texColour *= texture(uTexture[_texIndex], _texCoord * _tilingFactor); break;
        case 19: texColour *= texture(uTexture[_texIndex], _texCoord * _tilingFactor); break;
        case 21: texColour *= texture(uTexture[_texIndex], _texCoord * _tilingFactor); break;
        case 22: texColour *= texture(uTexture[_texIndex], _texCoord * _tilingFactor); break;
        case 23: texColour *= texture(uTexture[_texIndex], _texCoord * _tilingFactor); break;
        case 24: texColour *= texture(uTexture[_texIndex], _texCoord * _tilingFactor); break;
        case 25: texColour *= texture(uTexture[_texIndex], _texCoord * _tilingFactor); break;
        case 26: texColour *= texture(uTexture[_texIndex], _texCoord * _tilingFactor); break;
        case 27: texColour *= texture(uTexture[_texIndex], _texCoord * _tilingFactor); break;
        case 28: texColour *= texture(uTexture[_texIndex], _texCoord * _tilingFactor); break;
        case 29: texColour *= texture(uTexture[_texIndex], _texCoord * _tilingFactor); break;
        case 30: texColour *= texture(uTexture[_texIndex], _texCoord * _tilingFactor); break;
        case 31: texColour *= texture(uTexture[_texIndex], _texCoord * _tilingFactor); break;
    }

    colour = texColour;
}