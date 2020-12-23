#include "PreComp.h"
#include "OpenGLShader.h"

#include "Tempest/Core/Core.h"

#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <filesystem>

namespace 
{
    GLenum shaderTypeFromString(const std::string& type) 
    {
        if (type == "vertex")
        {
            return GL_VERTEX_SHADER;
        }
        else if (type == "fragment" || type == "pixel")
        {
            return GL_FRAGMENT_SHADER;
        }

        TEMPEST_CORE_ASSERT(false, "Unknown shader type");

        return 0;
    }
}

namespace Tempest
{
    OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc) :
        _name(name)
    {
        TEMPEST_PROFILE_FUNCTION();
        std::unordered_map<GLenum, std::string> shaderSources;
        shaderSources[GL_VERTEX_SHADER] = vertexSrc;
        shaderSources[GL_FRAGMENT_SHADER] = fragmentSrc;
        compile(shaderSources);
    }

    OpenGLShader::OpenGLShader(const std::string& filepath)
    {
        TEMPEST_PROFILE_FUNCTION();
        std::filesystem::path path = filepath;
        _name = path.stem().string(); // Returns the file's name stripped of the extension.

        std::string shaderCode = readFile(filepath);
        auto shaderSources = preProcess(shaderCode);
        compile(shaderSources);
    }

    OpenGLShader::~OpenGLShader()
    {
        TEMPEST_PROFILE_FUNCTION();
        glDeleteProgram(_rendererID);
    }

    std::string OpenGLShader::readFile(const std::string& path)
    {
        TEMPEST_PROFILE_FUNCTION();
        std::string result;
        std::ifstream in(path, std::ios::in | std::ios::binary);
        if (in.is_open())
        {
            in.seekg(0, std::ios::end);
            size_t size = in.tellg();

            if (size != -1)
            {
                result.resize(size);
                in.seekg(0, std::ios::beg);
                in.read(&result[0], size);
            }
            else
            {
                TEMPEST_ERROR("Could read data from: {0}", path);
            }
        }
        else
        {
            TEMPEST_ERROR("Could not open file: {0}", path);
        }

        return result;
    }

    std::unordered_map<GLenum, std::string> OpenGLShader::preProcess(const std::string& shaderSource)
    {
        TEMPEST_PROFILE_FUNCTION();

        std::unordered_map<GLenum, std::string> shaderSources;

        const char* typeToken = "#type";
        size_t typeTokenLength = strlen(typeToken);
        size_t pos = shaderSource.find(typeToken, 0);

        while (pos != std::string::npos)
        {
            size_t eol = shaderSource.find_first_of("\r\n", pos); //End of shader type declaration line
            TEMPEST_CORE_ASSERT(eol != std::string::npos, "Syntax error");

            size_t begin = pos + typeTokenLength + 1; //Start of shader type name (after "#type " keyword)
            std::string type = shaderSource.substr(begin, eol - begin);
            TEMPEST_CORE_ASSERT(shaderTypeFromString(type) != 0, "Invalid shader type specified");

            size_t nextLinePos = shaderSource.find_first_not_of("\r\n", eol); //Start of shader code after shader type declaration line
            TEMPEST_CORE_ASSERT(nextLinePos != std::string::npos, "Syntax error");

            pos = shaderSource.find(typeToken, nextLinePos); //Start of next shader type declaration line

            shaderSources[shaderTypeFromString(type)] = (pos == std::string::npos) ? shaderSource.substr(nextLinePos) : shaderSource.substr(nextLinePos, pos - nextLinePos);
        }

        return shaderSources;
    }

    void OpenGLShader::compile(const std::unordered_map<GLenum, std::string>& shaderSources)
    {
        TEMPEST_PROFILE_FUNCTION();

        _rendererID = glCreateProgram();
        std::array<GLenum, 2> glShaderIDs;
        int shaderIDIndex = 0;
        for (auto& keyValue : shaderSources)
        {
            GLenum shaderType = keyValue.first;
            const std::string& shaderSource = keyValue.second;

            // Create an empty vertex shader handle
            unsigned int shader = glCreateShader(shaderType);

            // Send the vertex shader source code to GL

            // Note that std::string's .c_str is NULL character terminated.
            const char* source = shaderSource.c_str();
            glShaderSource(shader, 1, &source, 0);

            // Compile the vertex shader
            glCompileShader(shader);

            int isCompiled = 0;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
            if (isCompiled == GL_FALSE)
            {
                int maxLength = 0;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

                // The maxLength includes the NULL character
                std::vector<GLchar> infoLog(maxLength);
                glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

                // We don't need the shader anymore.
                glDeleteShader(shader);

                TEMPEST_CORE_ASSERT(false, "Shader compliation error: {0}", infoLog.data());
                break;
            }

            glAttachShader(_rendererID, shader);
            glShaderIDs[shaderIDIndex++] = shader;
        }

        // Link our program
        glLinkProgram(_rendererID);

        // Note the different functions here: glGetProgram* instead of glGetShader*.
        GLint isLinked = 0;
        glGetProgramiv(_rendererID, GL_LINK_STATUS, &isLinked);
        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(_rendererID, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            if (maxLength != 0)
            {
                glGetProgramInfoLog(_rendererID, maxLength, &maxLength, &infoLog[0]);
                TEMPEST_CORE_ASSERT(false, "Shader linker error: {0}", infoLog.data());
            }
            else
            {
                TEMPEST_CORE_ASSERT(false, "Shader linker error: No error message reported.");
            }

            // We don't need the program anymore.
            glDeleteProgram(_rendererID);

            for (auto id : glShaderIDs)
            {
                glDeleteShader(id);
            }

            assert(0);
            return;
        }
        // Always detach shaders after a successful link.
        for (auto id : glShaderIDs)
        {
            glDetachShader(_rendererID, id);
            glDeleteShader(id);
        }
    }

    void OpenGLShader::bind() const
    {
        TEMPEST_PROFILE_FUNCTION();

        glUseProgram(_rendererID);
    }

    void OpenGLShader::unbind() const
    {
        TEMPEST_PROFILE_FUNCTION();

        glUseProgram(0);
    }

    void OpenGLShader::setInt(const std::string& name, int value)
    {
        TEMPEST_PROFILE_FUNCTION();
        setIntUniform(name, value);
    }

    void OpenGLShader::setMatrix4(const std::string& name, const glm::mat4x4& value)
    {
        TEMPEST_PROFILE_FUNCTION();
        setMatrix4Uniform(name, value);
    }

    void OpenGLShader::setVec4(const std::string& name, const glm::vec4& value)
    {
        TEMPEST_PROFILE_FUNCTION();
        setVec4Uniform(name, value);
    }

    void OpenGLShader::setVec3(const std::string& name, const glm::vec3& value)
    {
        TEMPEST_PROFILE_FUNCTION();
        setVec3Uniform(name, value);
    }

    void OpenGLShader::setVec2(const std::string& name, const glm::vec2& value) 
    {
        TEMPEST_PROFILE_FUNCTION();
        setVec2Uniform(name, value);
    }

    void OpenGLShader::setMatrix4Uniform(const std::string& name, const glm::mat4x4& matrix)
    {
        int uniformLocation = glGetUniformLocation(_rendererID, name.c_str());
        glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void OpenGLShader::setMatrix3Uniform(const std::string& name, const glm::mat3x3& matrix) 
    {
        int uniformLocation = glGetUniformLocation(_rendererID, name.c_str());
        glUniformMatrix3fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void OpenGLShader::setIntUniform(const std::string& name, int value)
    {
        int uniformLocation = glGetUniformLocation(_rendererID, name.c_str());
        //TEMPEST_CORE_ASSERT(uniformLocation != -1, "Could not find uniform.");
        glUniform1i(uniformLocation, value);

    }

    void OpenGLShader::setVec1Uniform(const std::string& name, const glm::vec1& vector)
    {
        int uniformLocation = glGetUniformLocation(_rendererID, name.c_str());
        glUniform1f(uniformLocation, vector.x);
    }

    void OpenGLShader::setVec2Uniform(const std::string& name, const glm::vec2& vector)
    {
        int uniformLocation = glGetUniformLocation(_rendererID, name.c_str());
        glUniform2f(uniformLocation, vector.x, vector.y);
    }

    void OpenGLShader::setVec3Uniform(const std::string& name, const glm::vec3& vector)
    {
        int uniformLocation = glGetUniformLocation(_rendererID, name.c_str());
        TEMPEST_CORE_ASSERT(uniformLocation != -1, "Could not find uniform.");
        glUniform3f(uniformLocation, vector.x, vector.y, vector.z);
    }

    void OpenGLShader::setVec4Uniform(const std::string& name, const glm::vec4& vector)
    {
        int uniformLocation = glGetUniformLocation(_rendererID, name.c_str());
        glUniform4f(uniformLocation, vector.x, vector.y, vector.z, vector.w);
    }
}