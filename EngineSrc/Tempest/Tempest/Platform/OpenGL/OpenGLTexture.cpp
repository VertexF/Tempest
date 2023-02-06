#include "PreComp.h"
#include "OpenGLTexture.h"

namespace Tempest 
{
    OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height, uint32_t channels)
        : _width(width), _height(height), _imageData(nullptr)
    {
        TEMPEST_PROFILE_FUNCTION();

        switch (channels)
        {
        case 1:
            _internalFormat = GL_ALPHA8;
            _dataFormat = GL_ALPHA;
            break;

        case 3:
            _internalFormat = GL_RGB8;
            _dataFormat = GL_RGB;
            break;

        case 4:
            _internalFormat = GL_RGBA8;
            _dataFormat = GL_RGBA;
            break;
        default:
            TEMPEST_ERROR("Channel type not supported. Please select a textures with RGBA = 4, RGB = 3, or ALPHA = 1 channel.");
            _internalFormat = 0;
            _dataFormat = 0;
            break;
        }

        glCreateTextures(GL_TEXTURE_2D, 1, &_textureID);
        glTextureStorage2D(_textureID, 1, _internalFormat, _width, _height);

        //This might be a problem for text rendering.
        glTextureParameteri(_textureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(_textureID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTextureParameteri(_textureID, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(_textureID, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }

    OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
        : _width(width), _height(height), _imageData(nullptr)
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
        _path(path), _imageData(nullptr)
    {
        TEMPEST_PROFILE_FUNCTION();
        int width, height, channels;
        stbi_set_flip_vertically_on_load(1);
        {
            TEMPEST_PROFILE_SCOPE("OpenGLTexture2D::OpenGLTexture2D(const std::string&) - stbi_load");
            _imageData = stbi_load(path.c_str(), &width, &height, &channels, 0);
        }

        TEMPEST_CORE_ASSERT(_imageData != nullptr, "Image could not be found or loaded!");

        _width = width;
        _height = height;

        GLenum internalFormat = 0;
        GLenum dataFormat = 0;
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

        glTextureSubImage2D(_textureID, 0, 0, 0, _width, _height, _dataFormat, GL_UNSIGNED_BYTE, _imageData);

        stbi_image_free(_imageData);
    }

    OpenGLTexture2D::~OpenGLTexture2D() 
    {
        TEMPEST_PROFILE_FUNCTION();
        glDeleteTextures(1, &_textureID);
    }

    uint32_t OpenGLTexture2D::getRendererID() const
    {
        return _textureID;
    }

    void OpenGLTexture2D::setData(void* data, uint32_t size) 
    {
        switch (_dataFormat)
        {
        case GL_ALPHA:
            TEMPEST_CORE_ASSERT(size == _width * _height, "The buffer has to be the entire size of the texture.");
            break;

        case GL_RGB:
        {
            uint32_t bpp = 3;
            TEMPEST_CORE_ASSERT(size == _width * _height * bpp, "The buffer has to be the entire size of the texture.");
        }
            break;

        case GL_RGBA:
        {
            uint32_t bpp = 4;
            TEMPEST_CORE_ASSERT(size == _width * _height * bpp, "The buffer has to be the entire size of the texture.");
        }
            break;
        }

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