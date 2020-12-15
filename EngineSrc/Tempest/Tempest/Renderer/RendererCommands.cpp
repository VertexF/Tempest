#include "PreComp.h"
#include "RendererCommands.h"

#include "../Platform/OpenGL/OpenGLRendererAPI.h"

namespace Tempest 
{
    RendererAPI* RendererCommands::_rendererAPI = new OpenGLRendererAPI;
}