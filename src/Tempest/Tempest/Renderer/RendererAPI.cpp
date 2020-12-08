#include "PreComp.h"
#include "RendererAPI.h"

#include "../Platform/OpenGL/OpenGLRendererAPI.h"

namespace Tempest 
{
    RendererAPI::API RendererAPI::_API = RendererAPI::API::OPENGL;
}