#include "PreComp.h"
#include "OpenGLShader.h"

#include <gl/glew.h>
#include <glm/gtc/type_ptr.hpp>

namespace Tempest
{
    OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc)
    {
        // Create an empty vertex shader handle
        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

        // Send the vertex shader source code to GL
        // Note that std::string's .c_str is NULL character terminated.
        const char* source = vertexSrc.c_str();
        glShaderSource(vertexShader, 1, &source, 0);

        // Compile the vertex shader
        glCompileShader(vertexShader);

        int isCompiled = 0;
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            int maxLength = 0;
            glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

            // We don't need the shader anymore.
            glDeleteShader(vertexShader);

            TEMPEST_ERROR("Vertex shader compliation error: {0}", infoLog.data());
            return;
        }

        // Create an empty fragment shader handle
        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        // Send the fragment shader source code to GL
        // Note that std::string's .c_str is NULL character terminated.
        source = fragmentSrc.c_str();
        glShaderSource(fragmentShader, 1, &source, 0);

        // Compile the fragment shader
        glCompileShader(fragmentShader);

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<char> infoLog(maxLength);
            glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

            // We don't need the shader anymore.
            glDeleteShader(fragmentShader);
            // Either of them. Don't leak shaders.
            glDeleteShader(vertexShader);

            TEMPEST_ERROR("Fragment shader compliation error: {0}", infoLog.data());
            return;
        }

        // Vertex and fragment shaders are successfully compiled.
        // Now time to link them together into a program.
        // Get a program object.
        _rendererID = glCreateProgram();

        // Attach our shaders to our program
        glAttachShader(_rendererID, vertexShader);
        glAttachShader(_rendererID, fragmentShader);

        // Link our program
        glLinkProgram(_rendererID);

        // Note the different functions here: glGetProgram* instead of glGetShader*.
        int isLinked = 0;
        glGetProgramiv(_rendererID, GL_LINK_STATUS, (int*)&isLinked);
        if (isLinked == GL_FALSE)
        {
            int maxLength = 0;
            glGetProgramiv(_rendererID, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(_rendererID, maxLength, &maxLength, &infoLog[0]);

            // We don't need the program anymore.
            glDeleteProgram(_rendererID);
            // Don't leak shaders either.
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);

            TEMPEST_ERROR("Linking shader error: {0}", infoLog.data());
            return;
        }

        // Always detach shaders after a successful link.
        glDetachShader(_rendererID, vertexShader);
        glDetachShader(_rendererID, fragmentShader);
    }

    OpenGLShader::~OpenGLShader()
    {
        glDeleteProgram(_rendererID);
    }

    void OpenGLShader::bind() const
    {
        glUseProgram(_rendererID);
    }

    void OpenGLShader::unbind() const
    {
        glUseProgram(0);
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
        if (uniformLocation != -1)
        {
            glUniform3f(uniformLocation, vector.x, vector.y, vector.z);
        }
        else 
        {
            TEMPEST_ERROR("Could not find uniform.");
        }
    }

    void OpenGLShader::setVec4Uniform(const std::string& name, const glm::vec4& vector)
    {
        int uniformLocation = glGetUniformLocation(_rendererID, name.c_str());
        glUniform4f(uniformLocation, vector.x, vector.y, vector.z, vector.w);
    }
}