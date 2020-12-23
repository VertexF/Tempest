#include "PreComp.h"
#include "OpenGLTexture.h"


#include <stb_image.h>

namespace Tempest 
{
    OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
        : _width(width), _height(height)
    {
        TEMPEST_PROFILE_FUNCTION();
        _internalFormat = GL_RGBA8;
        _dataFormat = GL_RGBA;

        glCreateTextures(GL_TEXTURE_2D, 1, &_textureID);
        glTextureStorage2D(_textureID, 1, _internalFormat, _width, _height);

        glTextureParameteri(_textureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(_textureID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTextureParameteri(_textureID, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(_textureID, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }

    OpenGLTexture2D::OpenGLTexture2D(const std::string& path) :
        _path(path)
    {
        TEMPEST_PROFILE_FUNCTION();
        int width, height, channels;
        stbi_set_flip_vertically_on_load(1);
        stbi_uc* imageData;
        {
            TEMPEST_PROFILE_SCOPE("OpenGLTexture2D::OpenGLTexture2D(const std::string&) - stbi_load");
            imageData = stbi_load(path.c_str(), &width, &height, &channels, 0);
        }
        if (imageData == nullptr) 
        {
            TEMPEST_ERROR("Image could not be found or loaded!");
            assert(imageData != nullptr);
        }

        _width = width;
        _height = height;

        GLenum internalFormat, dataFormat = 0;
        if (channels == 4) 
        {
            internalFormat = GL_RGBA8;
            dataFormat = GL_RGBA;
        }
        else if (channels == 3) 
        {
            internalFormat = GL_RGB8;
            dataFormat = GL_RGB;
        }

        _internalFormat = internalFormat;
        _dataFormat = dataFormat;

        glCreateTextures(GL_TEXTURE_2D, 1, &_textureID);
        glTextureStorage2D(_textureID, 1, _internalFormat, _width, _height);

        glTextureParameteri(_textureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(_textureID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTextureParameteri(_textureID, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(_textureID, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTextureSubImage2D(_textureID, 0, 0, 0, _width, _height, _dataFormat, GL_UNSIGNED_BYTE, imageData);

        stbi_image_free(imageData);
    }

    OpenGLTexture2D::~OpenGLTexture2D() 
    {
        TEMPEST_PROFILE_FUNCTION();
        glDeleteTextures(1, &_textureID);
    }

    void OpenGLTexture2D::setData(void* data, uint32_t size) 
    {
        TEMPEST_PROFILE_FUNCTION();
        uint32_t bpp = _dataFormat == GL_RGBA ? 4 : 3;
        TEMPEST_CORE_ASSERT(size == _width * _height * bpp, "The buffer has to be the entire size of the texture.");
        glTextureSubImage2D(_textureID, 0, 0, 0, _width, _height, _dataFormat, GL_UNSIGNED_BYTE, data);
    }

    void OpenGLTexture2D::bind(uint32_t slot) const 
    {
        TEMPEST_PROFILE_FUNCTION();
        glBindTextureUnit(slot, _textureID);
    }

    void OpenGLTexture2D::unbind(uint32_t slot) const
    {
        TEMPEST_PROFILE_FUNCTION();
        glBindTextureUnit(slot, 0);
    }
}