#pragma once

#include <Common.h>

typedef struct ShaderProgramSource
{
    char* vertexShader;
    char* fragmentShader;
    char* geometryShader;
} ShaderProgramSource;

namespace Umbra2D {

class Shader
{
	unsigned int id;
public:

    void bind();
    void unbind();

    unsigned int getUniformID(const std::string& name);
    void setMat4(const std::string& name, const glm::mat4* mat, size_t how_many = 1);
    void setVec4(const std::string& name, glm::vec4 vec);
    void setVec2(const std::string& name, const glm::vec2 value);
    void setVec3(const std::string& name, const glm::vec3 vec);
    void setBool(const std::string& name, bool value);
    void setInt(const std::string& name, int value);
    void setFloat(const std::string& name, const float value);

    void setTexture(const std::string& name, int value, int textureUnit);

    Shader(std::string filepath_v, std::string filepath_f, std::string filepath_g = "");
    ~Shader();

private:
    // reads the shaders from the files and returns a ShaderProgramSource struct
    static ShaderProgramSource ParseShader(std::string filepath_v, std::string filepath_f, std::string filepath_g);
    
    /* compiles the shader
    - type: GL_VERTEX_SHADER/GL_FRAGMENT_SHADER/GL_GEOMETRY_SHADER
    - source: char array containing the source code of the shader
    */
    unsigned int CompileShader(unsigned int type, const char* source);
    // Links the shaders together and returns the internal id of the group
    unsigned int CreateShader(const char* vertexShader, const char* fragmentShader, const char* geometryShader);

};

}
