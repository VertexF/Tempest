#include "OpenGLFramebuffer.h"

#include <GL/glew.h>

namespace 
{
    uint32_t MAX_FRAME_BUFFER_SIZE = 8192;
}

namespace Tempest 
{
    OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpec& spec) : _framebufferSpec(spec)
    {
        invalidate();
    }

    OpenGLFramebuffer::~OpenGLFramebuffer() 
    {
        glDeleteFramebuffers(1, &_rendererID);
        glDeleteTextures(1, &_colourAttachment);
        glDeleteTextures(1, &_depthAttachment);
    }

    void OpenGLFramebuffer::bind() 
    {
        glBindFramebuffer(GL_FRAMEBUFFER, _rendererID);
        glViewport(0, 0, _framebufferSpec.width, _framebufferSpec.height);
    }

    void OpenGLFramebuffer::unbind() 
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    const FramebufferSpec OpenGLFramebuffer::getFramebufferSpec() const
    {
        return _framebufferSpec;
    }

    void OpenGLFramebuffer::resize(uint32_t width, uint32_t height)
    {
        if (width == 0 || height == 0 || width > MAX_FRAME_BUFFER_SIZE || height > MAX_FRAME_BUFFER_SIZE)
        {
            TEMPEST_WARN("Attempt to resize window to size {0} by {1}", width, height);
            return;
        }

        _framebufferSpec.width = width;
        _framebufferSpec.height = height;

        invalidate();
    }

    uint32_t OpenGLFramebuffer::getColourAttachmentRendererID() const
    {
        return _colourAttachment;
    }

    void OpenGLFramebuffer::invalidate()
    {
        if (_rendererID)
        {
            glDeleteFramebuffers(1, &_rendererID);
            glDeleteTextures(1, &_colourAttachment);
            glDeleteTextures(1, &_depthAttachment);
        }

        glCreateFramebuffers(1, &_rendererID);
        glBindFramebuffer(GL_FRAMEBUFFER, _rendererID);

        glCreateTextures(GL_TEXTURE_2D, 1, &_colourAttachment);
        glBindTexture(GL_TEXTURE_2D, _colourAttachment);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _framebufferSpec.width, _framebufferSpec.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _colourAttachment, 0);

        glCreateTextures(GL_TEXTURE_2D, 1, &_depthAttachment);
        glBindTexture(GL_TEXTURE_2D, _depthAttachment);
        glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, _framebufferSpec.width, _framebufferSpec.height);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, _depthAttachment, 0);

        TEMPEST_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer incomplete!");

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
}