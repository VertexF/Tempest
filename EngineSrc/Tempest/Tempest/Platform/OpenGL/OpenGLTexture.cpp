#include "PreComp.h"
#include "OpenGLTexture.h"

#include <gl/glew.h>
#include <stb_image.h>

namespace Tempest 
{
    OpenGLTexture2D::OpenGLTexture2D(const std::string& path) :
        _path(path)
    {
        int width, height, channels;
        stbi_set_flip_vertically_on_load(1);
        stbi_uc *imageData = stbi_load(path.c_str(), &width, &height, &channels, 0);
        if (imageData == nullptr) 
        {
            TEMPEST_ERROR("Image could not be found or loaded!");
            assert(imageData != nullptr);
        }

        _width = width;
        _height = height;

        glCreateTextures(GL_TEXTURE_2D, 1, &_textureID);
        glTextureStorage2D(_textureID, 1, GL_RGB8, _width, _height);

        glTextureParameteri(_textureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(_textureID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTextureSubImage2D(_textureID, 0, 0, 0, _width, _height, GL_RGB, GL_UNSIGNED_BYTE, imageData);

        stbi_image_free(imageData);
    }

    OpenGLTexture2D::~OpenGLTexture2D() 
    {
        glDeleteTextures(1, &_textureID);
    }

    void OpenGLTexture2D::bind(uint32_t slot) const 
    {
        glBindTextureUnit(slot, _textureID);
    }
}