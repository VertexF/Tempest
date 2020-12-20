#include "PreComp.h"
#include "Shader.h"

#include "Tempest/Renderer/Renderer.h"
#include "Tempest/Platform/OpenGL/OpenGLShader.h"

namespace Tempest 
{
    ref<Shader> Shader::create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
    {
        switch (Renderer::getAPI())
        {
        case RendererAPI::API::NONE:
            TEMPEST_CORE_ASSERT(false, "Renderer Type None is not supported!");
            return nullptr;
            break;
        case RendererAPI::API::OPENGL:
            return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
            break;
        }

        TEMPEST_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    ref<Shader> Shader::create(const std::string& path)
    {
        switch (Renderer::getAPI())
        {
        case RendererAPI::API::NONE:
            TEMPEST_CORE_ASSERT(false, "Renderer Type None is not supported!");
            return nullptr;
            break;
        case RendererAPI::API::OPENGL:
            return std::make_shared<OpenGLShader>(path);
            break;
        }

        TEMPEST_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    void ShaderLibrary::add(const ref<Shader>& shader) 
    {
        auto& name = shader->getName();
        if (exists(name) == true)
        {
            TEMPEST_CORE_ASSERT(false, "Shader name already exists.");
            assert(0);
        }
        _shaders[name] = shader;
    }

    void ShaderLibrary::add(const std::string& name, const ref<Shader>& shader)
    {
        if (exists(name) == true)
        {
            TEMPEST_CORE_ASSERT(false, "Shader name already exists.");
            assert(0);
        }
        _shaders[name] = shader;
    }

    ref<Shader> ShaderLibrary::load(const std::string& filepath) 
    {
        auto shader = Shader::create(filepath);
        add(shader);
        return shader;
    }

    ref<Shader> ShaderLibrary::load(const std::string& name, const std::string& filepath) 
    {
        auto shader = Shader::create(filepath);
        add(name, shader);
        return shader;
    }

    ref<Shader> ShaderLibrary::get(const std::string& name) const 
    {
        if (exists(name) == false)
        {
            TEMPEST_ERROR("Shader name doesn't exists.");
            assert(0);
        }

        return _shaders.at(name);
    }
}