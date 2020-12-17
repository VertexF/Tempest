#ifndef SHADER_HDR
#define SHADER_HDR

#include "PreComp.h"

#include "../Core.h"

namespace Tempest
{
    class Shader 
    {
    public:
        virtual ~Shader() = default;

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        static ref<Shader> create(const std::string& vertexSrc, const std::string& fragmentSrc);
        static ref<Shader> create(const std::string& path);
    };
}

#endif // !SHADER_HDR
