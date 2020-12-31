#ifndef SHADER_HDR
#define SHADER_HDR

#include "PreComp.h"

#include <glm/glm.hpp>

#include "Tempest/Core/Core.h"

namespace Tempest
{
    class Shader
    {
    public:
        virtual ~Shader() = default;

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        virtual void setInt(const std::string& name, int value) = 0;
        virtual void setIntArray(const std::string& name, uint32_t count, int* values) = 0;
        virtual void setMatrix4(const std::string& name, const glm::mat4x4& value) = 0;
        virtual void setVec4(const std::string& name, const glm::vec4& value) = 0;
        virtual void setVec3(const std::string& name, const glm::vec3& value) = 0;
        virtual void setVec2(const std::string& name, const glm::vec2& value) = 0;
        virtual void setFloat(const std::string& name, float value) = 0;

        virtual const std::string& getName() const = 0;

        static ref<Shader> create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
        static ref<Shader> create(const std::string& filepath);
    };

    class ShaderLibrary 
    {
    public:
        void add(const ref<Shader>& shader);
        void add(const std::string& name, const ref<Shader>& shader);

        ref<Shader> load(const std::string& filepath);
        ref<Shader> load(const std::string& name, const std::string& filepath);

        ref<Shader> get(const std::string& name) const;
        bool exists(const std::string& name) const { return _shaders.find(name) != _shaders.end(); }
    private:
        std::unordered_map<std::string, ref<Shader>> _shaders;
    };
}

#endif // !SHADER_HDR
