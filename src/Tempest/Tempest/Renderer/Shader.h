#ifndef SHADER_HDR
#define SHADER_HDR

#include "PreComp.h"

#include <glm/glm.hpp>

namespace Tempest
{
    class Shader 
    {
    public:
        Shader(const std::string &vertexSrc, const std::string& fragmentSrc);
        ~Shader();

        void bind();
        void unbind();

        void setMatrix4Uniform(const std::string &name, const glm::mat4x4& matrix);
    private:
        uint32_t _rendererID;
    };
}

#endif // !SHADER_HDR
