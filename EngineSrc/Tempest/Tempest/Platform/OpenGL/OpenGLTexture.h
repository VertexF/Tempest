#ifndef OPENGL_TEXTURE_HDR
#define OPENGL_TEXTURE_HDR

#include "PreComp.h"
#include "Tempest/Renderer/Texture.h"

#include <gl/glew.h>

namespace Tempest 
{
    class OpenGLTexture2D : public Texture2D
    {
    public:
        OpenGLTexture2D(uint32_t width, uint32_t height);
        OpenGLTexture2D(const std::string &path);
        virtual ~OpenGLTexture2D();

        virtual uint32_t getWidth() const override { return _width; }
        virtual uint32_t getHeight() const override { return _height; }

        virtual void setData(void* data, uint32_t size) override;

        virtual void bind(uint32_t slot = 0) const override;
        virtual void unbind(uint32_t slot = 0) const override;

        virtual bool operator==(const Texture& rhsTexture) const override { return _textureID == dynamic_cast<const OpenGLTexture2D&>(rhsTexture)._textureID; }
    private:
        std::string _path;

        uint32_t _width;
        uint32_t _height;

        uint32_t _textureID;

        GLenum _internalFormat;
        GLenum _dataFormat;
    };
}

#endif //! OPENGL_TEXTURE_HDR
