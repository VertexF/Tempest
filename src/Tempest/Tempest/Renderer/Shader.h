#ifndef SHADER_HDR
#define SHADER_HDR

#include "PreComp.h"

namespace Tempest
{
    class Shader 
    {
    public:
        Shader(const std::string &vertexSrc, const std::string& fragmentSrc);
        ~Shader();

        void bind();
        void unbind();

    private:
        uint32_t _rendererID;
    };
}

#endif // !SHADER_HDR
