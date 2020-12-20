#include "PreComp.h"
#include "RendererCommands.h"

#include "Tempest/Platform/OpenGL/OpenGLRendererAPI.h"

namespace Tempest 
{
    RendererAPI* RendererCommands::_rendererAPI = new OpenGLRendererAPI;
}