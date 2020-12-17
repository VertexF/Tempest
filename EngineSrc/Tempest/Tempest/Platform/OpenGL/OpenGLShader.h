#ifndef OPENGL_SHADER_HDR
#define OPENGL_SHADER_HDR

#include "../Renderer/Shader.h"

#include "PreComp.h"

#include <gl/glew.h>
#include <glm/glm.hpp>

namespace Tempest
{
    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
        OpenGLShader(const std::string& filepath);
        virtual ~OpenGLShader();

        virtual void bind() const override;
        virtual void unbind() const override;

        virtual const std::string& getName() const override { return _name; }

        void setMatrix4Uniform(const std::string& name, const glm::mat4x4& matrix);
        void setMatrix3Uniform(const std::string& name, const glm::mat3x3& matrix);

        void setIntUniform(const std::string& name, int value);

        void setVec1Uniform(const std::string& name, const glm::vec1& vector);
        void setVec2Uniform(const std::string& name, const glm::vec2& vector);
        void setVec3Uniform(const std::string& name, const glm::vec3& vector);
        void setVec4Uniform(const std::string& name, const glm::vec4& vector);
    private:
        std::string readFile(const std::string& path);
        std::unordered_map<GLenum, std::string> preProcess(const std::string& shaderSource);
        void compile(const std::unordered_map<GLenum, std::string> &shaderSources);
    private:
        uint32_t _rendererID;
        std::string _name;
    };
}

#endif // !OPENGL_SHADER_HDR
