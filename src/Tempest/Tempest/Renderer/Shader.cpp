#include "PreComp.h"
#include "Shader.h"

#define GLEW_STATIC 1
#include <gl/glew.h>

namespace Tempest 
{
    Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc) 
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

    Shader::~Shader()
    {
        glDeleteProgram(_rendererID);
    }

    void Shader::bind() 
    {
        glUseProgram(_rendererID);
    }

    void Shader::unbind() 
    {
        glUseProgram(0);
    }
}